#include "tcpcliwidget.h"
#include "ui_tcpcliwidget.h"
#include<QHostAddress>
TcpCliWidget::TcpCliWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpCliWidget)
{
    ui->setupUi(this);
    tcpSocket=NULL;
    tcpSocket=new QTcpSocket(this);
    setWindowTitle("客户端");
    connect(tcpSocket,&QTcpSocket::connected,
        [=]()
        {
           ui->textEditRead->setText("成功和服务器连接");
        }
        );
    connect(tcpSocket,&QTcpSocket::readyRead,
            [=]()
            {
//                if(tcpSocket==NULL)
//                {
//                tcpSocket=new QTcpSocket(this);
//                }
                QByteArray array=tcpSocket->readAll();
                ui->textEditRead->append(array);
            }
            );

}

TcpCliWidget::~TcpCliWidget()
{
    delete ui;
}

void TcpCliWidget::on_pushButtoncon_clicked()
{
//    if(tcpSocket==NULL)
//    {
//    tcpSocket=new QTcpSocket(this);
//    }
    QString ip=ui->lineEditIp->text();
    quint16 port=ui->lineEditPort->text().toUInt();
    tcpSocket->connectToHost(QHostAddress(ip),port);
}

void TcpCliWidget::on_pushButtonSend_clicked()
{
//    if(tcpSocket==NULL)
//    {
//        return;
//    }
    QString str=ui->textEditWrite->toPlainText();
    tcpSocket->write(str.toUtf8().data());
}

void TcpCliWidget::on_pushButtonClose_clicked()
{
//    if(tcpSocket==NULL)
//    {
//        return;
//    }
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
//    tcpSocket=NULL;
}
