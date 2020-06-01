#include "widget.h"
#include "ui_widget.h"
#include<QFile>
#include<QDataStream>
#include<QDebug>
#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    writeData();
    readData();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::writeData()
{
    QFile file("./text.txt");
    bool isOk= file.open(QIODevice::WriteOnly);
    if(true==isOk)
    {
       QDataStream stream(&file);
       stream<<QString("主要看气质")<<244;
       file.close();
    }


}
void Widget::readData()
{
    QFile file("./text.txt");
    bool isOk= file.open(QIODevice::ReadOnly);
    if(true==isOk)
    {
        QDataStream stream(&file);
        QString str;
        int i;
        stream>>str>>i;
        cout<<str<<i;
        file.close();
    }
}
