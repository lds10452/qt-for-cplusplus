#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QPicture>
#include<QImage>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QPicture picture;
    QPainter p;
    p.begin(&picture);
    p.drawPixmap(0,0,QPixmap(":/new/prefix1/Delphi.jpg"));
    p.drawLine(30,30,100,200);
    p.end();
    picture.save("./picture.png");
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
#if 0
    QPicture pic;
    pic.load("./picture.png");
    QPainter lp;
    lp.begin(this);
    lp.drawPicture(0,90,pic);
    lp.end();
#endif
    QPainter p(this);
    QPixmap pixmap;
    pixmap.load(":/new/prefix1/Delphi.jpg");
    QImage tempimage=pixmap.toImage();
    p.drawImage(0,50,tempimage);

    QImage image;
    image.load(":/new/prefix1/Delphi.jpg");
    QPixmap temppixmap=QPixmap::fromImage(image);
    p.drawPixmap(200,0,temppixmap);

}
