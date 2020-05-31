#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTimer>
#include"mythread.h"
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void dealTimeOut();
private slots:
    void on_pushButtonStart_clicked();
    void dealDone();
    void stopThread();
signals:

private:
    Ui::Widget *ui;
    QTimer *myTimer;
    MyThread *thread;
};

#endif // WIDGET_H
