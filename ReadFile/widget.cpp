#include "widget.h"
#include "ui_widget.h"
#include<QFile>
#include<QFileDialog>
#include<QByteArray>
#include<QFileInfo>
#include<QDebug>
#include<QDateTime>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_btnread_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,"打开文件","../","TXT(*.txt);;SOURCE(*.h,*.c)");
    if(path.isEmpty()==false)
    {
        QFile file(path);
        bool isOk=file.open(QIODevice::ReadOnly);
        if(isOk==true)
        {
//          QByteArray array= file.readAll();
//          ui->textEdit->setText(array);
            QByteArray array;
            if(file.atEnd()==false)
            {
                array+=file.readAll();
                ui->textEdit->setText(array);
            }
        }
    file.close();
    QFileInfo info(path);
    qDebug()<<"文件名字为："<<info.fileName();
    qDebug()<<"文件大小为："<<info.size();
    qDebug()<<"文件后缀为："<<info.suffix();
    qDebug()<<"文件创建时间为:"<<info.created().toString("yyyy-MM-dd hh:mm:ss");
    }

}

void Widget::on_btnwrite_clicked()
{
    QString path= QFileDialog::getSaveFileName(this,"保存文件","../","TXT(*.txt)");
    if(path.isEmpty()==false)
    {
        QFile file;
        file.setFileName(path);
        bool isOk=file.open(QIODevice::WriteOnly);
        if(isOk==true)
        {
            QString str=ui->textEdit->toPlainText();
            //file.write(str.toUtf8());
            //file.write(str.toStdString().data());
            file.write(str.toLocal8Bit());
        }
        file.close();
    }
}
