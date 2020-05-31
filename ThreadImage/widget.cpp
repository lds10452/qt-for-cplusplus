#include "widget.h"
#include "ui_widget.h"
#include<QPainter>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myT=new MyThread;
    thread=new QThread(this);
    myT->moveToThread(thread);
    thread->start();
    connect(ui->pushButton,&QPushButton::clicked,myT,&MyThread::drawImage);
    connect(myT,&MyThread::updateImage,this,&Widget::setImage);
    connect(this,&Widget::destroyed,this,&Widget::dealClose);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawImage(0,0,image);
}

void Widget::setImage(QImage temp)
{
    image=temp;
    update();
}
void Widget::dealClose()
{
    thread->quit();
    thread->wait();
    delete myT;
}
