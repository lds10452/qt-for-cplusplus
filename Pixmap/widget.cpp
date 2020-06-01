#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QPixmap>
#include<QImage>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QImage image(400,300,QImage::Format_ARGB32);
    QPainter p;
    p.begin(&image);
    p.drawImage(30,40,QImage(":/new/prefix1/Delphi.jpg"));
    for(int i=0;i<=50;i++)
    {
        for(int j=0;j<=40;j++)
        {
            image.setPixel(QPoint(i,j),qRgb(40,222,31));//qRgb(40,222,31)
        }
    }
    p.end();
    image.save("./image.png");
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
    QPixmap pixmap(400,300);
    QPainter p(&pixmap);
    //p.fillRect(0,0,400,300,QBrush(Qt::white));
    pixmap.fill(Qt::blue);
    p.drawPixmap(0,20,80,80,QPixmap(":/new/prefix1/Delphi.jpg"));
    pixmap.save("./pixmap.png");

}
