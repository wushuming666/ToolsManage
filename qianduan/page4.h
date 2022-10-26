#ifndef PAGE4_H
#define PAGE4_H

#include "page2.h"
#include <QWidget>
#include <QUdpSocket>
#include <QLabel>
#include <QPushButton>
#include <QString>
#include <QFile>

class Page4 : public QWidget
{
    Q_OBJECT
public:
    explicit Page4(QWidget *parent = nullptr);
    ~Page4();
    QString filename, Name, Fac;
private:
    //接收数据
    QUdpSocket *udpSocket;
    QLabel *videoLabel;
    QPushButton *pushButton;
    QImage saveImage;
private slots:
    //图像更新
    void videoUpdate();
    //保存图片
    void savePicture();
};

#endif // PAGE4_H
