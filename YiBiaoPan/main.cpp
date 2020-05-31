#include "yibiao.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    yiBiao w;
    w.show();

    return a.exec();
}
