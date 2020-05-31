#include "tcpserwidget.h"
#include "ui_tcpserwidget.h"

TcpSerWidget::TcpSerWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TcpSerWidget)
{
    ui->setupUi(this);
    tcpSocket=NULL;
    tcpServer=new QTcpServer(this);
    tcpServer->listen(QHostAddress::Any,8888);
    setWindowTitle("服务器(8888)");
    connect(tcpServer,&QTcpServer::newConnection,
            [=]()
            {
            tcpSocket=tcpServer->nextPendingConnection();
            QString ip=tcpSocket->peerAddress().toString();
            quint16 port=tcpSocket->peerPort();
            QString temp=QString("恭喜你与[%1:%2]成功连接").arg(ip).arg(port);
            ui->textEditRead->setText(temp);

            connect(tcpSocket,&QTcpSocket::readyRead,
                    [=]()
                    {
                    QByteArray array=tcpSocket->readAll();
                    ui->textEditRead->append(array);
                    }
                    );
            }
            );
}

TcpSerWidget::~TcpSerWidget()
{
    delete ui;
}

void TcpSerWidget::on_pushButtonSend_clicked()
{
    if(tcpSocket==NULL)
    {
        return;
    }
    QString str=ui->textEditWrite->toPlainText();
    tcpSocket->write(str.toUtf8().data());
}

void TcpSerWidget::on_pushButtonClose_clicked()
{
    if(tcpSocket==NULL)
    {
        return;
    }
    tcpSocket->disconnectFromHost();
    tcpSocket->close();
    tcpSocket=NULL;
}
