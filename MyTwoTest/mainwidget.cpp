#include "mainwidget.h"
#include <QDebug>
MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
{
    b1.setText("^_^");
    b1.setParent(this);
    b1.move(100,100);

    b2=new QPushButton(this);
    b2->setText("abc");

    connect(&b1,&QPushButton::pressed,this,&MainWidget::close);
    connect(b2,&QPushButton::released,this,&MainWidget::mySlot);
    connect(b2,&QPushButton::released,&b1,&QPushButton::hide);
    setWindowTitle("boss");

    b3.setParent(this);
    b3.setText("切换到子窗口");
    b3.move(50,50);

    //w.show();
    connect(&b3,&QPushButton::released,this,&MainWidget::changeWin);
//    void (SubWidget::*funSignal)()=&SubWidget::mySignal;
//    connect(&subWin,funSignal,this,&MainWidget::dealSub);
//    void (SubWidget::*testSignal)(int,QString)=&SubWidget::mySignal;
//    connect(&subWin,testSignal,this,&MainWidget::dealSlot);
    connect(&subWin,SIGNAL(mySignal()),this,SLOT(dealSub()));
    connect(&subWin,SIGNAL(mySignal(int,QString)),this,SLOT(dealSlot(int,QString)));

    QPushButton *b4=new QPushButton(this);
    b4->setText("lambda表达式");
    b4->move(150,150);
    int a=10,b=100;
    connect(b4,&QPushButton::clicked,
            [=](bool ischek) mutable//不加mutable值以只读方式传递，否则变量传递方式变为可读写
            {
            b4->setText("123");
            qDebug()<<a<<b<<ischek<<"11111";
            a=11;
            qDebug()<<a;
            }
            );

    resize(400,400);

}

void MainWidget::dealSlot(int a,QString str)
{
    qDebug()<<a<<str;
}
void MainWidget::mySlot()
{
    b2->setText("123");

}

void MainWidget::changeWin()
{
    subWin.show();
    hide();
}

void MainWidget::dealSub()
{
    show();
    subWin.hide();
}
MainWidget::~MainWidget()
{

}
