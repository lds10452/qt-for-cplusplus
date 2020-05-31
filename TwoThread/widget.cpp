#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    myT=new MyThread;
    thread=new QThread(this);
    myT->moveToThread(thread);
    connect(myT,&MyThread::mySignal,this,&Widget::dealSignal);
    qDebug()<<"主线程号为"<<QThread:: currentThread();
    connect(this,&Widget::startThread,myT,&MyThread::myTimeOut);
    connect(this,&Widget::destroyed,this,&Widget::dealClose);
}

void Widget::dealSignal()
{
    static int i=0;
    i++;
    ui->lcdNumber->display(i);
}
void Widget::dealClose()
{
//    if(thread->isRunning()==false)
//    {
//    return;
//    }
//     myT->setFlag(true);
    on_pushButtonStop_clicked();
    delete myT;
}
Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonStart_clicked()
{
    if(thread->isRunning()==true)
    {
    return;
    }
    myT->setFlag(false);
    thread->start();
    emit startThread();
}

void Widget::on_pushButtonStop_clicked()
{
    if(thread->isRunning()==false)
    {
    return;
    }
     myT->setFlag(true);
     thread->quit();
     thread->wait();
}
