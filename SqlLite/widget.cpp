#include "widget.h"
#include "ui_widget.h"
#include<QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlQuery>
#include<QVariantList>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    qDebug()<<QSqlDatabase::drivers();
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("../info.db");
    if(!db.open())
    {
        QMessageBox::warning(this,"打开失败",db.lastError().text());
        return;
    }
    QSqlQuery query;
    query.exec("create table student(id int primary key,name varchar(255),age int,score int);");
    query.prepare("insert into student (name,age,score)values(?,?,?)");
    QVariantList nameList;
    nameList<<"xiaoming"<<"xiaolong"<<"xiaojiang";
    QVariantList ageList;
    ageList<<32<<42<<42;
    QVariantList scoreList;
    scoreList<<53<<54<<65;
    query.addBindValue(nameList);
    query.addBindValue(ageList);
    query.addBindValue(scoreList);
    query.execBatch();

    query.exec("select * from student");
    while (query.next())
    {
        qDebug()<<query.value(0).toInt()
               <<query.value(1).toString()
              <<query.value(2).toInt()
             <<query.value(3).toInt();
    }
}

Widget::~Widget()
{
    delete ui;

}
