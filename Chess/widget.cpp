#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
#include<QPen>
#include<QMouseEvent>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    chessX=-1;
    chessY=-1;
}

Widget::~Widget()
{
    delete ui;
}

void Widget::paintEvent(QPaintEvent *)
{
    gridW=width()/10;
    gridH=height()/10;
    startX=gridW;
    startY=gridH;
    QPainter p(this);
    p.drawPixmap(rect(),QPixmap(":/new/prefix1/Image/bk.jpg"));
    QPen pen;
    pen.setWidth(4);
    p.setPen(pen);

    for(int i=0;i<=8;i++)
    {
        p.drawLine(i*gridW+startX,startY,i*gridW+startX,startY+8*gridH);
        p.drawLine(startX,startY+i*gridH,8*gridW+startX,startY+i*gridH);
    }
    if(chessX!=-1&&chessY!=-1)
    {
        p.drawPixmap(startX+gridW* chessX,startY+gridH* chessY,gridW,gridH,QPixmap(":/new/prefix1/Image/face.png"));
    }
}

void Widget::mousePressEvent(QMouseEvent *e)
{
    int x=e->x();
    int y=e->y();
    if(x>=startX&&x<=(startX+8*gridW)&&y<=(startY+8*gridH)&&y>=startY)
    {
        chessX=(x-startX)/gridW;
        chessY=(y-startY)/gridH;
        update();
    }

}
