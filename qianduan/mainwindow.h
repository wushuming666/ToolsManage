#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QSqlDatabase>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    /* 数据库连接类 */
    QSqlDatabase sqlDatabase;
private:
    /*堆栈窗口*/
    QStackedWidget *stackedWidget;
    /*三个子界面*/
    QWidget *page[3];
    /*左侧的选择栏*/
    QListWidget *listWidget;
    QHBoxLayout *hBoxLayout;
};

#endif // MAINWINDOW_H
