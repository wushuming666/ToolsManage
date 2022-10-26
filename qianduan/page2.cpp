//提交等函数全放到page2里面
#include "page2.h"
#include <QSqlDatabase>
#include <QApplication>
#include <QImage>

Page2::Page2(QWidget *parent) : QWidget(parent)
{
    MainWidget = new QWidget(parent);
    for (int i = 0; i < 3; i ++) {
        pushButton[i] = new QPushButton(parent);
        info[i] = new QLabel(parent);
        lineEdit[i] = new QLineEdit(parent);
        hBoxLayout[i] = new QHBoxLayout(parent);
        vBoxLayout[i] = new QVBoxLayout(parent);
    }
    hBoxLayout[3] = new QHBoxLayout(parent);
    for (int i = 0; i < 6; i ++)
        hWidget[i] = new QWidget(parent);

    info[0]->setText("名称");
    info[1]->setText("生产厂家");
    info[2]->setText("待删除的编号");
    pushButton[2]->setText("确定删除");

    hBoxLayout[0]->addWidget(info[0]);
    hBoxLayout[0]->addWidget(lineEdit[0]);
    hWidget[0]->setLayout(hBoxLayout[0]);

    hBoxLayout[1]->addWidget(info[1]);
    hBoxLayout[1]->addWidget(lineEdit[1]);
    hWidget[1]->setLayout(hBoxLayout[1]);

    hBoxLayout[3]->addWidget(info[2]);
    hBoxLayout[3]->addWidget(lineEdit[2]);
    hBoxLayout[3]->addWidget(pushButton[2]);
    hWidget[5]->setLayout(hBoxLayout[3]);

    vBoxLayout[0]->addWidget(hWidget[0]);
    vBoxLayout[0]->addWidget(hWidget[1]);
    vBoxLayout[0]->addWidget(hWidget[5]);

    pushButton[0]->setText("添加照片");
    pushButton[1]->setText("确定添加");
    vBoxLayout[1]->addWidget(pushButton[0]);
    vBoxLayout[1]->addWidget(pushButton[1]);

    //不能两次setLayout
    hWidget[2]->setLayout(vBoxLayout[0]);
    hWidget[3]->setLayout(vBoxLayout[1]);

    hBoxLayout[2]->addWidget(hWidget[2]);
    hBoxLayout[2]->addWidget(hWidget[3]);

    hWidget[4]->setLayout(hBoxLayout[2]);

    connect(pushButton[0], SIGNAL(clicked()), this,
            SLOT(button1Clicked()));
    connect(pushButton[1], SIGNAL(clicked()), this,
            SLOT(button2Clicked()));
    connect(pushButton[2], SIGNAL(clicked()), this,
            SLOT(deleteClicked()));
}

QWidget* Page2::getpage2()
{
    return hWidget[4];
}

void Page2::button1Clicked()
{
    Page4 *page4 = new Page4();
    page4->show();
}

void Page2::button2Clicked()
{
    QString name = lineEdit[0]->text();
    QString factory = lineEdit[1]->text();
    lineEdit[0]->clear();
    lineEdit[1]->clear();
    /*从文本读出id*/
    QFile file("/home/wu/tools.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QString id = in.readLine();
    qDebug() << "page2 id " + id ;
    QString filename = "/home/wu/ToolsPhotos/" + id + ".png";
    qDebug() << "page2 " << filename;
    /* 数据库连接类 */
    QSqlDatabase sqlDatabase;
    QSqlQuery query(sqlDatabase);
    query.exec(tr("insert into tools values('%1','%2','%3','%4')")
               .arg(id).arg(name).arg(factory).arg(filename));
    qDebug() << "page2 " << id << ' ' << name << ' ' << factory << ' ' << filename;
}

void Page2::deleteClicked()
{
    QString str = lineEdit[2]->text();
    lineEdit[2]->clear();
    /* 数据库连接类 */
    QSqlDatabase sqlDatabase;
    QSqlQuery query(sqlDatabase);
    query.exec(tr("DELETE from tools where id = '%1'").arg(str));
}
