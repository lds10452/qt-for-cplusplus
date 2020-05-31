#ifndef TCPFILEWIDGET_H
#define TCPFILEWIDGET_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
#include<QFile>
#include<QFileDialog>
#include<QTimer>
namespace Ui {
class TcpFileWidget;
}

class TcpFileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TcpFileWidget(QWidget *parent = 0);
    ~TcpFileWidget();

private slots:
    void on_pushButtonFile_clicked();

    void on_pushButtonSend_clicked();
    void sendData();
private:
    Ui::TcpFileWidget *ui;
    QTcpServer *tcpServer;
    QTcpSocket *tcpSocket;
    QFile file;
    QString fileName;
    quint16 fileSize;
    quint16 sendSize;
    QTimer timer;

};

#endif // TCPFILEWIDGET_H
