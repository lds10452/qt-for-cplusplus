#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include"mythread.h"
#include<QThread>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
signals:
    void startThread();
private slots:
    void on_pushButtonStart_clicked();
    void dealSignal();
    void on_pushButtonStop_clicked();
    void dealClose();
private:
    Ui::Widget *ui;
    MyThread *myT;
    QThread *thread;
};

#endif // WIDGET_H
