#ifndef TCPCLIWIDGET_H
#define TCPCLIWIDGET_H

#include <QWidget>
#include<QTcpSocket>
namespace Ui {
class TcpCliWidget;
}

class TcpCliWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TcpCliWidget(QWidget *parent = 0);
    ~TcpCliWidget();

private slots:
    void on_pushButtoncon_clicked();

    void on_pushButtonSend_clicked();

    void on_pushButtonClose_clicked();

private:
    Ui::TcpCliWidget *ui;
    QTcpSocket *tcpSocket;
};

#endif // TCPCLIWIDGET_H
