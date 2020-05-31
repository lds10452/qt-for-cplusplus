#include "widget.h"
#include "ui_widget.h"
#include<QTime>
#include<QMessageBox>
#include<QTimerEvent>
#include<QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->pageSet);
    overMovie.setFileName(":/new/prefix1/Image/over.gif");
    ui->labelOver->setMovie(&overMovie);
    ui->labelOver->setScaledContents(true);

    winMovie.setFileName(":/new/prefix1/Image/win.gif");
    ui->labelWin->setMovie(&winMovie);
    ui->labelWin->setScaledContents(true);

    connect(ui->pushButton_0,&QPushButton::clicked,this,&Widget::dealNum);
    connect(ui->pushButton_1,&QPushButton::clicked,this,&Widget::dealNum);
    connect(ui->pushButton_2,&QPushButton::clicked,this,&Widget::dealNum);
    connect(ui->pushButton_3,&QPushButton::clicked,this,&Widget::dealNum);
    connect(ui->pushButton_4,&QPushButton::clicked,this,&Widget::dealNum);
    connect(ui->pushButton_5,&QPushButton::clicked,this,&Widget::dealNum);
    connect(ui->pushButton_6,&QPushButton::clicked,this,&Widget::dealNum);
    connect(ui->pushButton_7,&QPushButton::clicked,this,&Widget::dealNum);
    connect(ui->pushButton_8,&QPushButton::clicked,this,&Widget::dealNum);
    connect(ui->pushButton_9,&QPushButton::clicked,this,&Widget::dealNum);
}
Widget::~Widget()
{
    delete ui;
}

void Widget::dealNum()
{
    QObject *mySend=sender();
    QPushButton *p=(QPushButton *)mySend;
    if(p!=NULL)
    {
        QString numStr=p->text();
        resultStr+=numStr;
        if(resultStr.size()==1&&resultStr=="0")
        {
            resultStr.clear();
        }
        if(resultStr.size()<=4)
        {
            ui->textEdit->setText(resultStr);
            if(resultStr.size()==4)
            {
                if(resultStr>randStr)
                {
                    ui->textEdit->append("数字大了点");
                }
                else if(resultStr<randStr)
                {
                    ui->textEdit->append("数字小了点");
                }
                else {
                    ui->textEdit->append("恭喜你猜对了");
                    killTimer(gameTimerId);
                    QMessageBox::information(this,"win","恭喜你猜对了！");
                    winMovie.start();
                    ui->stackedWidget->setCurrentWidget(ui->pageWin);
                    winTimerId=startTimer(5000);
                }
                resultStr.clear();
            }
        }
    }
}

void Widget::on_pushButtonStart_clicked()
{
    gameTime=ui->comboBox->currentText().toInt();
    ui->stackedWidget->setCurrentWidget(ui->pageGame);
    ui->progressBar->setValue(gameTime);
    int num;
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
            while ((num=qrand()%10000)<1000) ;
    randStr=QString::number(num);
    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(gameTime);
    ui->progressBar->setValue(gameTime);
    gameTimerId=0;
    gameTimerId=startTimer(1000);
    resultStr.clear();
    ui->textEdit->clear();
}

void Widget::timerEvent(QTimerEvent *event)
{
    if(event->timerId()==gameTimerId)
    {
       gameTime--;
       ui->progressBar->setValue(gameTime);
       if(gameTime==0)
       {
           killTimer(gameTimerId);
           QMessageBox::information(this,"失败","时间到了啊");
           overMovie.start();
           ui->stackedWidget->setCurrentWidget(ui->pageOver);
           overTimerId=0;
           overTimerId=startTimer(2000);
           qDebug()<<overTimerId;
       }
    }
    else if(event->timerId()==overTimerId)
    {
    qDebug()<<overTimerId;
    overMovie.stop();
    killTimer(overTimerId);
    ui->stackedWidget->setCurrentWidget(ui->pageSet);
    qDebug()<<overTimerId;
    }
    else if(event->timerId()==winTimerId)
    {
        winMovie.stop();
        killTimer(winTimerId);
        ui->stackedWidget->setCurrentWidget(ui->pageSet);
    }

}

void Widget::on_pushButtonQuit_clicked()
{
    close();
}

void Widget::on_pushButton_chop_clicked()
{
    if(resultStr.size()==1)
    {
        resultStr.clear();
        ui->textEdit->clear();
    }
    else
    {
        resultStr.chop(1);
        ui->textEdit->setText(resultStr);
    }
}

void Widget::on_pushButton_tip_clicked()
{
    resultStr.clear();
    QString str="随机数为:"+randStr;
    ui->textEdit->setText(str);
}
