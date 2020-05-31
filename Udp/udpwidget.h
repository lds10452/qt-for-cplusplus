#ifndef UDPWIDGET_H
#define UDPWIDGET_H

#include <QWidget>
#include<QUdpSocket>
namespace Ui {
class UdpWidget;
}

class UdpWidget : public QWidget
{
    Q_OBJECT

public:
    explicit UdpWidget(QWidget *parent = 0);
    ~UdpWidget();
    void dealMsg();

private slots:
    void on_pushButtondSend_clicked();

private:
    Ui::UdpWidget *ui;
    QUdpSocket *udpSocket;
};

#endif // UDPWIDGET_H
