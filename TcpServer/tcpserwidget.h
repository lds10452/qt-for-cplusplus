#ifndef TCPSERWIDGET_H
#define TCPSERWIDGET_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
namespace Ui {
class TcpSerWidget;
}

class TcpSerWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TcpSerWidget(QWidget *parent = 0);
    ~TcpSerWidget();

private slots:
    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::TcpSerWidget *ui;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
};

#endif // TCPSERWIDGET_H
