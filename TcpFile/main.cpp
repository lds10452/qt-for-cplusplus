#include "tcpfilewidget.h"
#include <QApplication>
#include"tcpclientwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    TcpFileWidget w;
    w.show();
    tcpClientWidget w1;
    w1.show();
    return a.exec();
}
