#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QPen>
#include<QBrush>
#include<QBitmap>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    x=0;
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
    //QPainter p(this);
    QPainter p;
    p.begin(this);
    //p.drawPixmap(0,0,width(),height(),QPixmap(":/new/prefix1/tubiao/网站截图.png"));
    //p.drawPixmap(rect(),QPixmap(":/new/prefix1/tubiao/网站截图.png"));
    QPen pen;
    pen.setWidth(4);
    //pen.setColor(Qt::red);
    pen.setColor(QColor(33,34,43));
    pen.setStyle(Qt::DashLine);
    p.setPen(pen);

    p.drawLine(250,50,250,250);
    p.drawLine(250,50,50,50);

    QBrush brush;
    brush.setColor(Qt::blue);
    brush.setStyle(Qt::Dense3Pattern);
    p.setBrush(brush);

    p.drawRect(10,10,30,200);

//    pen.setColor(Qt::red);
//    pen.setStyle(Qt::DashLine);
//    p.setPen(pen);

    p.drawEllipse(QPoint(250,250),100,50);

    p.drawPixmap(x,120,80,80,QPixmap(":/new/prefix1/tubiao/Delphi.jpg"));

    p.drawPixmap(100,120,QBitmap(":/new/prefix1/tubiao/Delphi.jpg"));
    QBitmap bitmap;
    bitmap.load(":/new/prefix1/tubiao/Delphi.jpg");
    p.drawPixmap(250,10,bitmap);
    p.end();
}

void Widget::on_pushButton_clicked()
{
    x+=20;
    if(x>width())
    {
        x=0;
    }
    update();
}
