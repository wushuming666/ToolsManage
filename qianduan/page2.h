/*新增界面 需要连上数据库*/
#ifndef PAGE2_H
#define PAGE2_H

#include "page4.h"
#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QMainWindow>
#include <QDateTime>
#include <QSqlError>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QFile>

class Page2 : public QWidget
{
    Q_OBJECT
public:
    explicit Page2(QWidget *parent = nullptr);
    QWidget* getpage2();
private:
    QWidget *MainWidget, *hWidget[6];
    QLabel *info[3];
    QLineEdit *lineEdit[3];
    QHBoxLayout *hBoxLayout[4];
    QVBoxLayout *vBoxLayout[3];
    QPushButton *pushButton[3];
private slots:
    void button1Clicked();
    void button2Clicked();
    void deleteClicked();
};

#endif // PAGE2_H
