#include "mylabel.h"
#include<QMouseEvent>
MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
setMouseTracking(true);
}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    int i=ev->x();
    int j=ev->y();
    if(ev->button()==Qt::LeftButton)
    {
        QString text=QString("<center><h1>Left Mouse Press:(%1,%2)</h1></center>").arg(i).arg(j);
        setText(text);
    }else if(ev->button()==Qt::MidButton)
    {
        QString text=QString("<center><h1>Mid Mouse Press:(%1,%2)</h1></center>").arg(i).arg(j);
        setText(text);
    }else if(ev->button()==Qt::RightButton)
    {
        QString text=QString("<center><h1>Right Mouse Press:(%1,%2)</h1></center>").arg(i).arg(j);
        setText(text);
    }

    //QString text=QString("<center><h1>Mouse Press:(%1,%2)</h1></center>").arg(i).arg(j);
    //setText(text);
}
void MyLabel::mouseMoveEvent(QMouseEvent *ev)
{
    QString text=QString("<center><h1>Mouse Move:(%1,%2)</h1></center>").arg(ev->x()).arg(ev->y());
    //setText(text);
}
void MyLabel::mouseReleaseEvent(QMouseEvent *ev)
{
    QString text=QString("<center><h1>Mouse Release:(%1,%2)</h1></center>").arg(ev->x()).arg(ev->y());
    setText(text);
}
void MyLabel::enterEvent(QEvent *event)
{
    QString text=QString("<center><h1>Mouse Enter</h1></center>");
    setText(text);
}
void MyLabel::leaveEvent(QEvent *event)
{
   // QString text=QString("<center><h1>Mouse Leave</h1></center>");
    setText(QString("<center><h1>Mouse Leave</h1></center>"));
}
