#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myTimer=new QTimer(this);
    connect(myTimer,&QTimer::timeout,this,&Widget::dealTimeOut);
    thread=new MyThread(this);
    connect(thread,&MyThread::isDone,this,&Widget::dealDone);
    connect(this,&Widget::destroyed,this,&Widget::stopThread);
}
void Widget::stopThread()
{
    thread->quit();
    thread->wait();
}
Widget::~Widget()
{
    delete ui;
}
void Widget::dealTimeOut()
{
    static int i=0;
    i++;
    ui->lcdNumber->display(i);
}
void Widget::on_pushButtonStart_clicked()
{
    if(myTimer->isActive()==false)
    {
        myTimer->start(100);
    }
    thread->start();
}
void Widget::dealDone()
{
    qDebug()<<"it is over";
    myTimer->stop();
}
