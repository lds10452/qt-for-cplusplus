#include "udpwidget.h"
#include "ui_udpwidget.h"
#include<QHostAddress>
UdpWidget::UdpWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::UdpWidget)
{
    ui->setupUi(this);
    udpSocket=new QUdpSocket(this);
    //udpSocket->bind(8888);
    udpSocket->bind(QHostAddress::AnyIPv4,8888);
    udpSocket->joinMulticastGroup(QHostAddress("224.0.0.2"));
    //udpSocket->leaveMulticastGroup();
    setWindowTitle("8888");
    connect(udpSocket,&QUdpSocket::readyRead,this,&UdpWidget::dealMsg);
}

UdpWidget::~UdpWidget()
{
    delete ui;
}
void UdpWidget::dealMsg()
{
    char buff[1024]={0};
    QHostAddress ip;
    quint16 port;
    quint16 len= udpSocket->readDatagram(buff,sizeof(buff),&ip,&port);
    if(len>0)
    {
        QString str=QString("[%1:%2]%3").arg(ip.toString()).arg(port).arg(buff);
        ui->textEdit->setText(str);
    }

}

void UdpWidget::on_pushButtondSend_clicked()
{
    QString ip=ui->lineEditIp->text();
    quint16 port=ui->lineEditPort->text().toInt();
    QString str=ui->textEdit->toPlainText();
    udpSocket->writeDatagram(str.toUtf8(),QHostAddress(ip),port);
}
