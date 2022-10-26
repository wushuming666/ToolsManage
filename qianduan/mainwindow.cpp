#include "mainwindow.h"
#include <QList>
#include <QFont>
#include <QDebug>
#include "page1.h"
#include "page2.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QWidget *MainWidget = new QWidget(this);
    this->setGeometry(0,0,800,480);

    sqlDatabase = QSqlDatabase::addDatabase("QSQLITE");
    sqlDatabase.setDatabaseName("tools.db");
    if (!sqlDatabase.open())
        qDebug()<<"连接数据库错误"<<sqlDatabase.lastError()<<endl;
    else
        qDebug()<<"连接数据库成功"<<endl;
    QSqlQuery query(sqlDatabase);
    /* 使用指令式创建表 */
    query.exec("create table tools (id vchar(30) primary key, name vchar(30), "
               "factory vchar(30), photo text)");

    for(int i = 0; i < 3; i++) page[i] = new QWidget();
    stackedWidget = new QStackedWidget();
    listWidget = new QListWidget();
    hBoxLayout = new QHBoxLayout();
    QFont *font = new QFont();
    font->setPointSize(30);
    QList <QString>strListWidgetList;
    strListWidgetList<<"总览"<<"新增";
    for (int i = 0; i < 2; i++){
        /* listWidget插入项 */
        listWidget->insertItem(
                    i,
                    strListWidgetList[i]
                    );
    }
    listWidget->setFont(*font);

    Page1 *page1;
    Page2 *page2;
    QWidget *tmp1 = new QWidget();
    QWidget *tmp2 = new QWidget();
    for(int i = 0; i < 2; i++) {
        switch(i) {
        case 0:
            page1 = new Page1();
            tmp1 = page1->getPage1();
            stackedWidget->addWidget(tmp1);
            break;
        case 1:
            page2 = new Page2();
            tmp2 = page2->getpage2();
            stackedWidget->addWidget(tmp2);
            break;
        default:
            break;
        }
    }

    listWidget->setMaximumWidth(100);
    hBoxLayout->addWidget(listWidget);
    hBoxLayout->addWidget(stackedWidget);
    MainWidget->setLayout(hBoxLayout);
    this->setCentralWidget(MainWidget);

    connect(listWidget, SIGNAL(currentRowChanged(int)),
            stackedWidget, SLOT(setCurrentIndex(int)));
}

MainWindow::~MainWindow()
{
    sqlDatabase.close();
}
