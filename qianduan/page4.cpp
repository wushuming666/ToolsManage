#include "page4.h"
#include "page2.h"
#include <QDebug>
#include <QString>
#include <QCoreApplication>
#include <QTime>
#include <QDateTime>

Page4::Page4(QWidget *parent) : QWidget(parent)
{
    udpSocket = new QUdpSocket(parent);
    //绑定端口
    QHostAddress tmp;
    tmp.setAddress("192.168.10.99");
    udpSocket->bind(tmp, 8888);

    videoLabel = new QLabel(this);
    videoLabel->resize(640, 480);
    videoLabel->setText("未获取到图像数据");
    videoLabel->setAlignment(Qt::AlignCenter);
    pushButton = new QPushButton(this);
    pushButton->setGeometry(700, 200, 50, 50);
    pushButton->setText("拍照");
    connect(udpSocket, SIGNAL(readyRead()), this,SLOT(videoUpdate()));
    connect(pushButton, SIGNAL(clicked(bool)), this, SLOT(savePicture()));
    this->setGeometry(0, 0, 800, 480);
}

Page4::~Page4()
{

}

void Page4::videoUpdate()
{
    QByteArray datagram;

    /* 数据大小重置 */
    datagram.resize(udpSocket->pendingDatagramSize());

    /* 数据存放到datagram中 */
    udpSocket->readDatagram(datagram.data(), datagram.size());

    QByteArray decryptedByte;
    decryptedByte = QByteArray::fromBase64(datagram.data());

    QImage image;
    image.loadFromData(decryptedByte);
    saveImage = image;
    /* 显示图像 */
    videoLabel->setPixmap(QPixmap::fromImage(image));
}
void Page4::savePicture()
{
    QDateTime current_date_time =QDateTime::currentDateTime();
    QString current_date =current_date_time.toString("yyyy.MM.dd_hh:mm:ss.zzz_ddd");
    QString filename = "/home/wu/ToolsPhotos/" + current_date + ".png";
    saveImage.save(filename, "PNG", -1);
    qDebug() << "保存成功\n" << filename;
    QFile file("/home/wu/tools.txt");
    file.open(QIODevice::ReadWrite | QIODevice::Text);
    qDebug() << "page4 " << current_date;
    file.write(current_date.toUtf8());
    file.close();
    udpSocket->close();
}
