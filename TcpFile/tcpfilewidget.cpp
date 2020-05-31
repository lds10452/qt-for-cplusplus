#include "tcpfilewidget.h"
#include "ui_tcpfilewidget.h"
#include<QHostAddress>
#include<QDebug>
#include <QFileInfo>
TcpFileWidget::TcpFileWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpFileWidget)
{
    ui->setupUi(this);
    ui->pushButtonSend->setEnabled(false);
    ui->pushButtonFile->setEnabled(false);
    tcpServer=new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,8800);
    setWindowTitle("服务器端口为：8800");
    connect(tcpServer,&QTcpServer::newConnection,
            [=]()
            {
                tcpSocket=tcpServer->nextPendingConnection();
                QString ip=tcpSocket->peerAddress().toString();
                quint16 port=tcpSocket->peerPort();
                QString str=QString("[%1:%2]成功连接").arg(ip).arg(port);
                ui->textEdit->setText(str);
                ui->pushButtonFile->setEnabled(true);
                connect(tcpSocket,&QTcpSocket::readyRead,
                        [=]()
                        {
                            QByteArray buf=tcpSocket->readAll();
                            if(QString(buf)=="file done")
                            {
                                ui->textEdit->append("文件发送完毕");
                                file.close();
                                tcpSocket->disconnectFromHost();
                                tcpSocket->close();
                            }
                        });
            });
    connect(&timer,&QTimer::timeout,
            [=]()
            {
               timer.stop();
               sendData();
            });
}

TcpFileWidget::~TcpFileWidget()
{
    delete ui;
}

void TcpFileWidget::on_pushButtonFile_clicked()
{
    QString filePath=QFileDialog::getOpenFileName(this,"打开文件","../");
    if(false==filePath.isEmpty())
    {
        fileName.clear();
        fileSize=0;
        QFileInfo info(filePath);
        fileName=info.fileName();
        fileSize=info.size();
        sendSize=0;
        file.setFileName(filePath);
        bool isOk=file.open(QIODevice::ReadOnly);
        if(false==isOk)
        {
           qDebug()<<"打开文件出错";
        }
        ui->textEdit->append(filePath);
        ui->pushButtonSend->setEnabled(true);
        ui->pushButtonFile->setEnabled(false);

    }
    else
    {
        qDebug()<<"选择文件路径出错";
    }

}

void TcpFileWidget::on_pushButtonSend_clicked()
{
    ui->pushButtonSend->setEnabled(false);
    QString head=QString("%1##%2").arg(fileName).arg(fileSize);
    quint16 len= tcpSocket->write(head.toUtf8());
    if(len>0)
    {
    timer.start(20);
    }
    else {
        qDebug()<<"头部信息发送失败";
        file.close();
        ui->pushButtonFile->setEnabled(true);
        ui->pushButtonSend->setEnabled(false);
    }

}
void TcpFileWidget::sendData()
{
    ui->textEdit->append("正在发送文件……");
    quint16 len=0;
    do
    {
        char buf[4*1024]={0};
        len=0;
        len=file.read(buf,sizeof(buf));
        tcpSocket->write(buf,len);
        sendSize+=len;

    }while(len>0);
//    if(sendSize==fileSize)
//    {
//        ui->textEdit->append("文件发送完毕");
//        file.close();
//        tcpSocket->disconnectFromHost();
//        tcpSocket->close();
//    }
}
