#include "widget.h"
#include "ui_widget.h"
#include<QBuffer>
#include<QDebug>
#include<QDataStream>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QByteArray array;
    QBuffer menFile(&array);
    menFile.open(QIODevice::WriteOnly);
    menFile.write("11111111111111");
    menFile.write("333333333");
    menFile.close();
    qDebug()<<menFile.buffer();
    qDebug()<<"array"<<array;

    QBuffer write;
    write.open(QIODevice::WriteOnly);
    QDataStream stream(&write);
    stream<<QString("主要看气质")<<234;
    write.close();
    qDebug()<<write.buffer();

    write.open(QIODevice::ReadOnly);
    QDataStream in(&write);
    QString str;
    int a;
    in>>str>>a;
    write.close();
    qDebug()<<str.toUtf8().data()<<a;

}

Widget::~Widget()
{
    delete ui;
}
