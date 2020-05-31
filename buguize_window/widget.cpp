#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QMouseEvent>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    setWindowFlags(Qt::FramelessWindowHint|windowFlags());
    setAttribute(Qt::WA_TranslucentBackground);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
   QPixmap pixmap;
   pixmap.load(":/new/prefix1/Delphi.jpg");
   QPainter p(this);
   p.drawPixmap(0,0,pixmap);
}
void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons()&Qt::LeftButton)
    {
        move(event->globalPos()-p);
    }
}
void Widget::mousePressEvent(QMouseEvent *event)
{
    if(event->button()==Qt::RightButton)
    {
        close();
    }
    else if(event->button()==Qt::LeftButton)
    {
        p=event->globalPos()-this->frameGeometry().topLeft();
    }
}
