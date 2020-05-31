#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    timer=new QTimer(this);
    connect(timer,&QTimer::timeout,
            [=]()
            {
                static int i=0;
                i++;
                ui->lcdNumber->display(i);
            });
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonstartstop_clicked()
{
    if(timer->isActive()==false)
    {
    timer->start(1000);
    }
}

void Widget::on_pushButton_2_clicked()
{
    if(timer->isActive()==true)
    {
        timer->stop();
    }
}
