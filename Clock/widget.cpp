#include "widget.h"
#include "ui_widget.h"
#include<QDebug>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->tabWidget->setCurrentWidget(ui->tabClock);
    btnEnable(false);
    ui->labelShow->setVisible(false);
    //ui->pushButtonClear->setEnabled(false);
    myTimer=new QTimer(this);
    secTimer=new QTimer(this);
    //player=new QMediaPlayer(this);
    ui->lcdNumber->setDigitCount(8);
    connect(myTimer,&QTimer::timeout,this,&Widget::clock);

    ui->btnSecClear->setEnabled(false);
    ui->btnSecStop->setEnabled(false);
    connect(secTimer,&QTimer::timeout,this,&Widget::secShow);

    ui->labelWaring->setVisible(false);
    ui->labelFinish->setVisible(false);
    cntThread=new countThread;
    myThread=new QThread(this);
    cntThread->moveToThread(myThread);
    cntThread->setFlag(false);
    connect(this,&Widget::countSignal,cntThread,&countThread::timeOut);
    connect(cntThread,&countThread::sendSignal,this,&Widget::dealCount);
    connect(this,&Widget::destroyed,this,&Widget::dealDestroyed);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::clock()
{
    if(temp.hour()==QTime::currentTime().hour()&&temp.minute()==QTime::currentTime().minute())
    {
        player->play();
        myTimer->setSingleShot(true);
        ui->labelShow->setVisible(true);
        //qDebug()<< myTimer->timerId();
    }
}

void Widget::btnEnable(bool isUsed)
{
    ui->labelShow->setEnabled(isUsed);
    ui->pushButtonSure->setEnabled(isUsed);
    ui->pushButtonStop->setEnabled(isUsed);
}

void Widget::secShow()
{

    sec++;
    if(sec>59)
    {
        sec=0;
        min++;
        if(min>59)
        {
            min=0;
            hour++;
            if(hour>23)
            {
                hour=0;
            }
        }
    }
    QString secStr=QString("%1:%2:%3").arg(hour).arg(min).arg(sec);
    ui->lcdNumber->display(secStr);
}

void Widget::dealCount()
{

    if(cSec==0&&(cMin!=0||cHour!=0))
    {
      cSec=59;
      if(cMin==0&&cHour!=0)
      {
          cMin=59;
          cHour--;
      }
      else
      {
        cMin--;
      }
    }
    else
    {
        if(cSec!=0)
           cSec--;
        if(cSec==0&&cMin==0&&cHour==0)
        {
            ui->labelFinish->setVisible(true);
            cntThread->setFlag(false);
            myThread->quit();
            myThread->wait();
        }
    }
    QString hourStr=QString::number(cHour);
    QString minStr=QString::number(cMin);
    QString secStr= QString::number(cSec);
    ui->lineEditHour->setText(hourStr);
    ui->lineEditMin->setText(minStr);
    ui->lineEditSec->setText(secStr);
    //qDebug()<<secStr;
}

void Widget::dealDestroyed()
{
    cntThread->setFlag(false);
    myThread->quit();
    myThread->wait();
}

void Widget::on_pushButtonSure_clicked()
{
    myTimer->start(500);
    temp=ui->timeEdit->time();
    btnEnable(false);
}

void Widget::on_pushButtonStop_clicked()
{
    static int t=0;
    t++;
    if(t==2)
    {
        t=0;
    }
    if(t%2==1)
    {
        player->play();
    }else {
        player->stop();
    }
}

void Widget::on_radioButton1_clicked()
{
    player->setVolume(30);
    player->setMedia(QUrl::fromLocalFile("D:\\QT\\Qtziliao\\shipin\\苏运莹-野子.mp3"));
    ui->labelSong->setText("Apink .mp3");
    btnEnable(true);
}

void Widget::on_radioButton2_clicked()
{
    player->setVolume(30);
    player->setMedia(QUrl::fromLocalFile("D:\\QT\\Qtziliao\\shipin\\星语星愿.mp3"));
    ui->labelSong->setText("星语星愿.mp3");
    btnEnable(true);
}

void Widget::on_radioButton3_clicked()
{
    player->setVolume(50);
    player->setMedia(QUrl::fromLocalFile("D:\\QT\\Qtziliao\\shipin\\月光下的凤尾竹 .mp3"));
    ui->labelSong->setText("月光下的凤尾竹 .mp3");
    btnEnable(true);
}

void Widget::on_pushButtonClear_clicked()
{
    myTimer->setSingleShot(false);
    player->stop();
    //btnEnable(false);
    //qDebug()<< myTimer->timerId();
}



void Widget::on_btnSecStart_2_clicked()
{
    secTimer->start(1000);
    ui->btnSecClear->setEnabled(true);
    ui->btnSecStop->setEnabled(true);
}

void Widget::on_btnSecStop_clicked()
{
    secTimer->stop();
}

void Widget::on_btnSecClear_clicked()
{
    secTimer->stop();
    sec=0;
    min=0;
    hour=0;
    ui->lcdNumber->display("0:0:0");
}

void Widget::on_btnCdownStart_clicked()
{
    cHour=ui->lineEditHour->text().toInt();
    cMin=ui->lineEditMin->text().toInt();
    cSec=ui->lineEditSec->text().toInt();
    if(cHour>23||cMin>59||cSec>59)
    {
        ui->labelWaring->setVisible(true);
    }
    else
    {
        ui->labelWaring->setVisible(false);
        cntThread->setFlag(true);
        myThread->start();
        emit countSignal();
    }
}

void Widget::on_btnCdownStop_clicked()
{
    cntThread->setFlag(false);
}

void Widget::on_btnCdownClear_clicked()
{
    ui->lineEditHour->setText("0");
    ui->lineEditMin->setText("0");
    ui->lineEditSec->setText("0");
    cntThread->setFlag(false);
    myThread->quit();
    myThread->wait();
}
