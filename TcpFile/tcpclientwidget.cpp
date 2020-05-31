#include "tcpclientwidget.h"
#include "ui_tcpclientwidget.h"
#include<QMessageBox>
#include<QHostAddress>
#include<QDebug>
tcpClientWidget::tcpClientWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::tcpClientWidget)
{
    ui->setupUi(this);
    tcpSocket=new QTcpSocket(this);
    isStart=true;
    ui->progressBar->setValue(0); //当前值
    setWindowTitle("客户端");
    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]()
            {
                QByteArray buf=tcpSocket->readAll();
                if(isStart==true)
                {
                    isStart=false;
                    fileName=QString( buf).section("##",0,0);
                    fileSize=QString(buf).section("##",1,1).toInt();
                    recvSize=0;
                    file.setFileName(fileName);
                    bool isOk=file.open(QIODevice::WriteOnly);
                    if(false==isOk)
                    {
                        qDebug()<<"打开文件出错";
                        tcpSocket->disconnectFromHost(); //断开连接
                        tcpSocket->close(); //关闭套接字
                        return;
                    }
                    QString str=QString("接受的文件:[%1:%2kb]").arg(fileName).arg(fileSize/1024);
                    QMessageBox::information(this,"文件信息",str);
                    ui->progressBar->setMinimum(0);
                    ui->progressBar->setMaximum(fileSize/1024);
                    ui->progressBar->setValue(0);
                }else
                {
                   qint64 len= file.write(buf);
                   if(len>0)
                   {
                     recvSize+=len;
                     qDebug()<<len;
                   }
                   ui->progressBar->setValue(recvSize/1024);
                   if(recvSize==fileSize)
                   {
                       tcpSocket->write("file done");
                       QMessageBox::information(this,"接收完成","文件接收完成");
                       file.close();
                       tcpSocket->disconnectFromHost();
                       tcpSocket->close();
                   }
                }
            });
}

tcpClientWidget::~tcpClientWidget()
{
    delete ui;
}

void tcpClientWidget::on_pushButton_clicked()
{
    QString ip=ui->lineEditIP->text();
    quint16 port=ui->lineEditPort->text().toInt();
    tcpSocket->connectToHost(QHostAddress(ip),port);
    isStart=true;
    ui->progressBar->setValue(0);
}
