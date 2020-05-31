#include "mywidget.h"
#include "ui_mywidget.h"
#include<QDebug>
#include<QKeyEvent>
#include<QMessageBox>
MyWidget::MyWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    timerId=startTimer(1000);
    timerId_1=startTimer(500);
    connect(ui->pushButton,&MyButton::clicked,
           [=]()
            {
            qDebug()<<"按钮被按下";
            }
            );
    ui->label_2->installEventFilter(this);
    ui->label_2->setTabletTracking(true);
}

MyWidget::~MyWidget()
{
    delete ui;
}
void MyWidget::keyPressEvent(QKeyEvent *event)
{
    qDebug()<<(char)(event->key());
    if(event->key()==Qt::Key_A)
    {
        qDebug()<<"Qt::Key_A";
    }
}
void MyWidget::timerEvent(QTimerEvent *event)
{
    if(timerId==event->timerId())
    {
    static int s=0;
    s++;
    ui->label->setText(QString("<center><h1>Timer Out:%1</h1></center>").arg(s));
    if(5==s)
    {
        killTimer(timerId);
    }
    }else if(timerId_1==event->timerId())
    {
        static int s=0;
        s++;
        ui->label_2->setText(QString("<center><h1>Timer Out:%1</h1></center>").arg(s));

    }
}
void MyWidget::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"+++++++";
}
void MyWidget::closeEvent(QCloseEvent *event)
{
    int ret=QMessageBox::question(this,"close","确定关闭吗");
    if(ret==QMessageBox::Yes)
    {
        event->accept();
    }else
    {
        event->ignore();
    }
}
bool MyWidget::event(QEvent *event)
{
    if(event->type()==QEvent::Timer)
    {
        QTimerEvent *env=static_cast<QTimerEvent *>(event);
        timerEvent(env);
        return true;
    }else if(event->type()==QEvent::KeyPress)
    {
        QKeyEvent *env=static_cast<QKeyEvent *>(event);
        if(env->key()==Qt::Key_B)
        {
            return QWidget::event(event);
        }
        return true;
    }else
    {
        return QWidget::event(event);
        //return false;
    }
}
bool MyWidget::eventFilter(QObject *watched, QEvent *event)
{
    if(watched==ui->label_2)
    {
        QMouseEvent *env=static_cast<QMouseEvent *>(event);
        if(event->type()==QEvent::MouseMove)
        {
            ui->label_2->setText(QString("Mouse move:(%1,%2)").arg(env->x()).arg(env->y()));
            return true;
        }
        if(event->type()==QEvent::MouseButtonPress)
        {
            ui->label_2->setText(QString("Mouse press:(%1,%2)").arg(env->x()).arg(env->y()));
            return true;
        }
        if(event->type()==QEvent::MouseButtonRelease)
        {
            ui->label_2->setText(QString("Mouse release:(%1,%2)").arg(env->x()).arg(env->y()));
            return true;
        }
        else
        {
            return QWidget::eventFilter(watched,event);
        }
    }
    else
    {
        return QWidget::eventFilter(watched,event);
    }
}
