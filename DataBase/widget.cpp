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
    QSqlDatabase db= QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("info");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    if(!db.open())
    {
        QMessageBox::warning(this,"打开失败",db.lastError().text());
        return;
    }
    QSqlQuery query;
    query.exec("create table clothes(id int primary key auto_increment, name varchar(255), cost int, profit int,sale int,total int);");
    //query.exec("insert into clothes(id ,name ,cost, profit,sale,total) values(1,'mike',18,59);");
    query.prepare("insert into clothes(name, cost,profit,sale,total) values(?, ?, ?,?,?)");
    //给字段设置内容 list
    QVariantList nameList;
    nameList << "阿迪达斯" << "耐克" << "花花公子"<<"李宁"<<"安踏";
    QVariantList costList;
    costList << 220 << 260 << 330<<319<<543<<422;
    QVariantList profitList;
    profitList << 159 << 169 << 279<<54<<335<<227;
    QVariantList saleList;
    saleList<<400<<234<<523<<642<<624;
    QVariantList totalList;
    totalList<<159*400<<169*234<<279*523<<54*642<<227*624;
    //给字段绑定相应的值 按顺序绑定
    query.addBindValue(nameList);
    query.addBindValue(costList);
    query.addBindValue(profitList);
    query.addBindValue(saleList);
    query.addBindValue(totalList);
    //执行预处理命令
    query.execBatch();

//        query.prepare("insert into student(name, age, score) values(:name, :age, :score)");
//        //给字段设置内容 list
//        QVariantList nameList;
//        nameList << "xiaoa" << "xiaob" << "xiaoc";
//        QVariantList ageList;
//        ageList << 33 << 44 << 55;
//        QVariantList scoreList;
//        scoreList << 89 << 90 << 99;
//        //给字段绑定
//        query.bindValue(":name", nameList);
//        query.bindValue(":score", scoreList);
//        query.bindValue(":age", ageList);

//        //执行预处理命令
//        query.execBatch();
//    query.exec("select * from clothes where name ='xiaoa'");
//    while(query.next())
//    {
//        qDebug()<<query.value(0).toInt()
//                <<query.value(1).toString()
//                <<query.value("age").toInt()
//               <<query.value("score").toInt();
//    }
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonDelete_clicked()
{
    QString str=ui->lineEdit->text();
    QString sql=QString("delete from clothes where name='%1'").arg(str);
    QSqlDatabase::database().transaction();
    QSqlQuery query;
    query.exec(sql);
}

void Widget::on_pushButtonSure_clicked()
{
    QSqlDatabase::database().commit();
}

void Widget::on_pushButtonCanCel_clicked()
{
    QSqlDatabase::database().rollback();
}
