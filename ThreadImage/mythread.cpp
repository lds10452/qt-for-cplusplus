#include "mythread.h"
#include<QPainter>
#include<QPen>
MyThread::MyThread(QObject *parent) : QObject(parent)
{

}
void MyThread::drawImage()
{
    QImage image(300,300,QImage::Format_ARGB32);
    QPainter p(&image);

    QPen pen;
    pen.setWidth(4);
    p.setPen(pen);
    QBrush brush;
    brush.setColor(Qt::blue);
    brush.setStyle(Qt::CrossPattern);
    p.setBrush(brush);    QPoint a[5]=
    {
        QPoint(qrand()%300,qrand()%300),
        QPoint(qrand()%300,qrand()%300),
        QPoint(qrand()%300,qrand()%300),
        QPoint(qrand()%300,qrand()%300),
        QPoint(qrand()%300,qrand()%300)
    };
    p.drawPolygon(a,5);

    emit updateImage(image);
}
