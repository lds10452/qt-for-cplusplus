#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QCompleter>
#include<QStringList>
#include<QMovie>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QStringList list;
    list<<"hello"<<"how arE you"<<"Hehe";

    QCompleter *com=new QCompleter(list,this);
    com->setCaseSensitivity(Qt::CaseInsensitive);

    ui->lineEdit->setCompleter(com);

    ui->labelText->setText("^_^");

    ui->labelImage->setPixmap(QPixmap("://tubiao/okbutton.png"));
    ui->labelImage->setScaledContents(true);

    QMovie *movie=new QMovie("://tubiao/kk.gif");
    ui->labelGif->setMovie(movie);
    movie->start();
    ui->labelGif->setScaledContents(true);

    ui->labelUrl->setText("<h1><a href=\"https://www.baidu.com\">百度一下</a></h1>");
    ui->labelUrl->setOpenExternalLinks(true);

    ui->lcdNumber->display(123);

    ui->progressBar->setMinimum(0);
    ui->progressBar->setMaximum(200);
    ui->progressBar->setValue(100);
}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_pushButton_clicked()
{
    static int i=0;
    ui->stackedWidget->setCurrentIndex(++i%4);
}
