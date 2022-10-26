/*查找界面*/
#ifndef PAGE3_H
#define PAGE3_H

#include <QWidget>
#include <QLineEdit>
#include <QTableView>

class Page3 : public QWidget
{
    Q_OBJECT
public:
    explicit Page3(QWidget *parent = nullptr);
    ~Page3();
    QWidget* getPage3();
private:
    QLineEdit *lineEdit;


private slots:
};

#endif // PAGE3_H
