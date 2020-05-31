#include "widget.h"
#include "ui_widget.h"
#include<QFile>
#include<QTextStream>
#include<QFileDialog>
#include<QDebug>
#define cout qDebug()<<"["<<__FILE__<<":"<<__LINE__<<"]"
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    writeData();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::writeData()
{
    QFile p;
    p.setFileName("./demo.txt");
    bool isOk=p.open(QIODevice::WriteOnly);
    if(true==isOk)
    {
    QTextStream stream(&p);
    stream.setCodec("GB18030");
    stream<<QString("主要看气质")<<332;
    p.close();
    }
}

void Widget::on_pushButton_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,"读文件","../","TXT(*.txt)");
    if(false==path.isEmpty())
    {
        QFile file;
        file.setFileName(path);
        bool isOk=file.open(QIODevice::ReadOnly);
        if(true==isOk)
        {
            QTextStream stream(&file);
            stream.setCodec("GB18030");
            QString str= stream.readAll();
            ui->textEdit->setText(str);
            file.close();
        }
    }
}
