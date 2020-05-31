#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QSqlDatabase>
#include<QSqlError>
#include<QMessageBox>
#include<QSqlQueryModel>
#include<QSqlQuery>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    on_actionCar_triggered();
    connectDb();
    initData();
    DomXml::createXML("../demo.xml");
//    QStringList list;
//    list<<"二汽神龙"<<"毕加索"<<"39"<<"1"<<"39";
//    DomXml::appendXML("../demo.xml",list);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionCar_triggered()
{
    ui->stackedWidget->setCurrentWidget(ui->car);
    ui->label->setText("车辆管理");
}

void MainWindow::on_actionCalc_triggered()
{
   ui->stackedWidget->setCurrentWidget(ui->calc);
   ui->label->setText("销售统计");
}
void MainWindow::connectDb()
{
    QSqlDatabase db=QSqlDatabase::addDatabase("QMYSQL");
    db.setDatabaseName("car");
    db.setHostName("127.0.0.1");
    db.setUserName("root");
    db.setPassword("123456");
    if(!db.open())
    {
        QMessageBox::warning(this,"打开数据库失败",db.lastError().text());
        return;
    }
}
void MainWindow::initData()
{
    QSqlQueryModel *queryModel=new QSqlQueryModel(this);
    queryModel->setQuery("select name from factory");
    ui->comboBoxFactory->setModel(queryModel);

    ui->labelLast->setText("0");
    ui->lineEditTotal->setEnabled(false);
}

void MainWindow::on_comboBoxFactory_currentIndexChanged(const QString &arg1)
{
    if(arg1=="请选择厂家")
    {
        ui->comboBoxBrand->clear();
        ui->spinBox->setValue(0);
        ui->labelLast->setText("0");
        ui->lineEditTotal->clear();
        ui->lineEditPrice->clear();
        ui->spinBox->setEnabled(false);
        ui->pushButtonSure->setEnabled(false);
    }
    else
    {
        ui->comboBoxBrand->clear();
        QSqlQuery query;
        QString sql=QString("select name from brand where factory='%1'").arg(arg1);
        query.exec(sql);
        while (query.next()) {
            QString name=query.value(0).toString();
            ui->comboBoxBrand->addItem(name);
        }
        ui->spinBox->setEnabled(true);
    }
}

void MainWindow::on_comboBoxBrand_currentIndexChanged(const QString &arg1)
{
    QSqlQuery query;
    QString sql=QString("select price,last from brand where factory='%1'and name='%2'")
            .arg(ui->comboBoxFactory->currentText())
            .arg(arg1);
    query.exec(sql);
    while (query.next()) {
    int price=query.value("price").toInt();
    int last=query.value("last").toInt();
    ui->lineEditPrice->setText(QString::number(price));
    ui->labelLast->setText(QString::number(last));
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    if(arg1==0)
    {
        ui->pushButtonSure->setEnabled(false);
    }
    else
    {
        ui->pushButtonSure->setEnabled(true);
    }
    QSqlQuery query;
    QString sql=QString("select last from brand where factory='%1'and name='%2'")
            .arg(ui->comboBoxFactory->currentText())
            .arg(ui->comboBoxBrand->currentText());
    query.exec(sql);
    int last;
    while (query.next()) {
        last=query.value("last").toInt();
    }
    if(arg1>last)
    {
        ui->spinBox->setValue(last);
        return;
    }
    int temp=last-arg1;
    ui->labelLast->setText(QString::number(temp));

    int price=ui->lineEditPrice->text().toInt();
    int sum=price*arg1;
    ui->lineEditTotal->setText(QString::number(sum));
}

void MainWindow::on_pushButtonCancel_clicked()
{
    ui->comboBoxFactory->setCurrentIndex(0);
}

void MainWindow::on_pushButtonSure_clicked()
{
    int num=ui->spinBox->value();
    int last=ui->labelLast->text().toInt();
    QSqlQuery query;
    QString str=QString("select sell from brand where factory='%1'and name='%2'")
            .arg(ui->comboBoxFactory->currentText())
            .arg(ui->comboBoxBrand->currentText());
    query.exec(str);
    int sell;
    while (query.next()) {
        sell=query.value("sell").toInt();
    }
    sell+=num;
    str=QString("update brand set sell=%1,last=%2 where factory='%3'and name='%4'")
            .arg(sell)
            .arg(last)
            .arg(ui->comboBoxFactory->currentText())
            .arg(ui->comboBoxBrand->currentText());
    query.exec(str);
    QStringList list;
    list << ui->comboBoxFactory->currentText()
         << ui->comboBoxBrand->currentText()
         << ui->lineEditPrice->text()
         << QString::number(num)
         << ui->lineEditTotal->text();
    DomXml::appendXML("../demo.xml", list);
    QStringList fList;
    QStringList bList;
    QStringList pList;
    QStringList nList;
    QStringList tList;
    DomXml::readXML("../demo.xml",fList, bList, pList, nList, tList);
    for(int i = 0; i < fList.size(); i++)
    {
        QString str = QString("%1:%2:卖出了%3,单价：%4, 总价: %5")
                .arg(fList.at(i))
                .arg(bList.at(i))
                .arg(nList.at(i))
                .arg(pList.at(i))
                .arg(tList.at(i));
        ui->textEdit->append(str);
        qDebug() << str;
    }
    ui->pushButtonSure->setEnabled(false);
    on_pushButtonCancel_clicked();
}
