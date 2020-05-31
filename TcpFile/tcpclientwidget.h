#ifndef TCPCLIENTWIDGET_H
#define TCPCLIENTWIDGET_H

#include <QWidget>
#include<QTcpSocket>
#include<QFile>
namespace Ui {
class tcpClientWidget;
}

class tcpClientWidget : public QWidget
{
    Q_OBJECT

public:
    explicit tcpClientWidget(QWidget *parent = 0);
    ~tcpClientWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::tcpClientWidget *ui;
    QTcpSocket *tcpSocket;
    QFile file;
    QString fileName;
    quint16 fileSize;
    quint16 recvSize;
        bool isStart;
};

#endif // TCPCLIENTWIDGET_H
