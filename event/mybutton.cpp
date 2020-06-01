#include "mybutton.h"
#include<QMouseEvent>
#include<QDebug>
MyButton::MyButton(QWidget *parent) : QPushButton(parent)
{

}
void MyButton::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        qDebug()<<"左键被按下";//不会往下传
        e->ignore();//传给父组件
    }else
    {
    QPushButton::mousePressEvent(e);//继续往下传
    }

}
