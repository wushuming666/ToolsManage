#include "page1.h"
#include <QDebug>
#include <QHeaderView>
#include <QSqlError>
#include <QApplication>
#include <QSqlRecord>
Page1::Page1(QWidget *parent) : QWidget(parent)
{
    /* QSqlQueryModel适合用于查询数据，不能修改数据 */
    sqlQueryModel = new QSqlQueryModel(this);
    sqlQueryModel->setQuery("select * from tools order by name ASC");
    if (sqlQueryModel->lastError().isValid())
        qDebug()<<"选择数据失败！"<<endl;
    sqlQueryModel->setHeaderData(0, Qt::Horizontal, "编号");
    sqlQueryModel->setHeaderData(1, Qt::Horizontal, "名称");
    sqlQueryModel->setHeaderData(2, Qt::Horizontal, "生产厂家");
    sqlQueryModel->setHeaderData(3, Qt::Horizontal, "图片路径");

    tableView = new QTableView();
    tableView->setModel(sqlQueryModel);
    tableView->hideColumn(0);
    tableView->hideColumn(3);
    /* 设置显示平均分列 */
    tableView->horizontalHeader()
            ->setSectionResizeMode(QHeaderView::Stretch);

    mainWidget = new QWidget();
    bottomWidget = new QWidget();
    gridWidget = new QWidget();
    photoWidget = new QWidget();
    imageLabel = new QLabel();

    /* 设置照片属性 */
    imageLabel->setScaledContents(true);
    imageLabel->setMaximumSize(200, 200);

    vBoxLayout = new QVBoxLayout();
    hBoxLayout[0] = new QHBoxLayout();
    hBoxLayout[1] = new QHBoxLayout();
    gridLayout = new QGridLayout();

    for (int i = 0; i < 4; i++) {
        label[i] = new QLabel();
        lineEdit[i] = new QLineEdit();
    }

    bottomWidget->setMinimumHeight(this->height() / 2 - 30);
    gridWidget->setMaximumWidth(this->width() / 2 - 30);

    /* 垂直布局 */
    vBoxLayout->addWidget(tableView);
    vBoxLayout->addWidget(bottomWidget);

    mainWidget->setLayout(vBoxLayout);

    /* 水平布局 */
    hBoxLayout[0]->addWidget(gridWidget);
    hBoxLayout[0]->addWidget(photoWidget);
    bottomWidget->setLayout(hBoxLayout[0]);

    QStringList list;
    list<< "编号：" << "名称："<<"生产厂家：" << "路径：";

    /* 网格布局 */
    for (int i = 0; i < 4; i++) {
        gridLayout->addWidget(label[i], i, 0);
        label[i]->setText(list[i]);
        switch (i) {
        case 0:
            gridLayout->addWidget(lineEdit[0], i, 1);
            break;
        case 1:
            gridLayout->addWidget(lineEdit[1], i, 1);
            break;
        case 2:
            gridLayout->addWidget(lineEdit[2], i, 1);
            break;
        case 3:
            gridLayout->addWidget(lineEdit[3], i, 1);
            break;
        default:
            break;
        }
    }

    gridWidget->setLayout(gridLayout);
    hBoxLayout[1]->addWidget(imageLabel);
    photoWidget->setLayout(hBoxLayout[1]);

    itemSelectionModel = new QItemSelectionModel(sqlQueryModel);
    tableView->setSelectionModel(itemSelectionModel);

    /* 信号槽连接，表示表中行数据变化时，触发槽函数 */
    connect(itemSelectionModel,
            SIGNAL(currentRowChanged(QModelIndex, QModelIndex)),
            this,
            SLOT(on_currentRowChanged(QModelIndex, QModelIndex)));

    dataWidgetMapper = new QDataWidgetMapper(this);
    /* 设置为自动提交 */
    dataWidgetMapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    dataWidgetMapper->setModel(sqlQueryModel);
    /* 创建数据映射，将前面的数据库内容映射到控件上 */
    dataWidgetMapper->addMapping(lineEdit[0], 0);
    dataWidgetMapper->addMapping(lineEdit[1], 1);
    dataWidgetMapper->addMapping(lineEdit[2], 2);
    dataWidgetMapper->addMapping(lineEdit[3], 3);
}

Page1::~Page1()
{

}

void Page1::on_currentRowChanged(const QModelIndex &current,
                                      const QModelIndex &previous)
{
    Q_UNUSED(previous)
    /* 更新数据映射行号，初始化时映射到第0行 */
    dataWidgetMapper->setCurrentModelIndex(current);
    /* 获取当前行号 */
    int row =  itemSelectionModel->currentIndex().row();
    qDebug() << "page1 " << row;
    /* 获取当前模型记录 */
    QSqlRecord record = sqlQueryModel->record(row);
    /* 获取id信息 */
//    QString id = record.value("id").toString();
    QString id = record.value("id").toString();
    qDebug() << "page1 " << id;
    QSqlQuery query;
    /* 使用bindValue绑定prepare里语句的值，需要使用":"，":"是占位符 */
    query.prepare("select photo from tools where id = :id");
    query.bindValue(":id", id);
    query.exec();
    /* 返回到选择的第一条记录，因为id是唯一的，也只有一条记录 */
    query.first();

    /* 获取字段为photo的值，也就是存储照片的路径 */
    QVariant temp = query.value("photo");
    if (!temp.isValid()) {
        qDebug()<<"数据无效！"<<endl;
        return;
    }

    /* 清空图片显示 */
    imageLabel->clear();

    QImage image(temp.toString());

    if (image.isNull()) {
        qDebug()<<"未找到"<<temp.toString()<<endl;
        return;
    }

    /* 显示照片 */
    imageLabel->setPixmap(QPixmap::fromImage(image));
}

QWidget* Page1::getPage1()
{
    return mainWidget;
}
