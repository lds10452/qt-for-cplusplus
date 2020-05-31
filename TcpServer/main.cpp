#include "tcpserwidget.h"
#include <QApplication>
#include"tcpcliwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpSerWidget w;
    w.show();

    TcpCliWidget client;
    client.show();

    return a.exec();
}
