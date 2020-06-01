#include "mywidget.h"
#include "ui_mywidget.h"

myWidget::myWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::myWidget)
{
    ui->setupUi(this);
    setStyleSheet("QLabel{color:rgb(2,6,244);background-color:red}");
    ui->label->setStyleSheet("QLabel{color:rgb(44,43,255);background-color:rgb(210,43,241)"
                             ";border-image:url(:/new/prefix1/tubiao/网站截图.png)}");//background-color
    ui->pushButton->setStyleSheet("QPushButton{border-image:url(:/new/prefix1/tubiao/网站截图.png)}"
                                  "QPushButton:hover{border-image:url(:/new/prefix1/tubiao/配色方案.png)}"
                                  "QPushButton:pressed{border-image:url(:/new/prefix1/tubiao/2-背景.png)}");
                                    //border:4px outset red;
}

myWidget::~myWidget()
{
    delete ui;
}
