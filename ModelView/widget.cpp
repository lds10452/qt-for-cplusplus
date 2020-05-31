#include "widget.h"
#include "ui_widget.h"
#include<QSqlDatabase>
#include<QDebug>
#include<QMessageBox>
#include<QSqlError>
#include<QSqlRecord>
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
    model=new QSqlTableModel(this);
    model->setTable("clothes");
    ui->tableView->setModel(model);
    model->select();
    model->setHeaderData(0,Qt::Horizontal,"序号");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    //ui->tableView->setEditTriggers(QAbstractItemView::NoEditTriggers);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButtonAdd_clicked()
{
    QSqlRecord record=model->record();
    int row=model->rowCount();
    model->insertRecord(row,record);
}

void Widget::on_pushButtonSure_clicked()
{
    model->submitAll();
}

void Widget::on_pushButtonCanel_clicked()
{
    model->revertAll();
    model->submitAll();
}

void Widget::on_pushButtonDel_clicked()
{
    QItemSelectionModel *sModel=ui->tableView->selectionModel();
    QModelIndexList list=sModel->selectedRows();
    for(int i=0;i<list.size();i++)
    {
        model->removeRow(list.at(i).row());
    }
}

void Widget::on_pushButtonSelcet_clicked()
{
    QString name1=ui->lineEdit->text();
    QString str=QString("name = '%1'").arg(name1);
    model->setFilter(str);
    model->select();
}
