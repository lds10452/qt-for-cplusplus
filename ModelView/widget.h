#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QSqlTableModel>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButtonAdd_clicked();

    void on_pushButtonSure_clicked();

    void on_pushButtonCanel_clicked();

    void on_pushButtonDel_clicked();

    void on_pushButtonSelcet_clicked();

private:
    Ui::Widget *ui;
    QSqlTableModel *model;
};

#endif // WIDGET_H
