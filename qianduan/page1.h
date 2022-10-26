//主键：录入的时间
//时间 名称 生产厂家 照片路径
/*数据库的显示表格 直接抄数据库2*/
#ifndef PAGE1_H
#define PAGE1_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QLabel>
#include <QSqlTableModel>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QTableView>
#include <QComboBox>
#include <QLineEdit>
#include <QDataWidgetMapper>
#include <QSqlQueryModel>
#include <QItemSelectionModel>
#include <QSpinBox>

class Page1 : public QWidget
{
    Q_OBJECT
public:
    explicit Page1(QWidget *parent = nullptr);
    ~Page1();
private:
    /* 用于查询数据 */
    QSqlQueryModel *sqlQueryModel;
    /* 数据映射 */
    QDataWidgetMapper *dataWidgetMapper;
    /* 选择模型 */
    QItemSelectionModel * itemSelectionModel;
    /* 水平布局 */
    QHBoxLayout *hBoxLayout[2];
    /* 垂直布局 */
    QVBoxLayout *vBoxLayout;
    /* 网格布局 */
    QGridLayout *gridLayout;
    /* 用于显示的表格*/
    QTableView *tableView;
    /* 主Widget */
    QWidget *mainWidget;
    /* 底部容器 */
    QWidget *bottomWidget;
    /* 底部网格布局容器 */
    QWidget *gridWidget;
    /* 照片容器 */
    QWidget *photoWidget;
    /* Label，用于显示照片 */
    QLabel *imageLabel;
    /* Label,底部显示文本 */
    QLabel *label[4];
    /* 单行输入框  */
    QLineEdit *lineEdit[4];
public:
    QWidget* getPage1();

private slots:
    /* 表格当前行变化执行的槽函数 */
    void on_currentRowChanged(const QModelIndex&, const QModelIndex&);
};

#endif // PAGE1_H
