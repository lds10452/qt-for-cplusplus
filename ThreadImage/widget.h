#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QImage>
#include<QThread>
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
    void paintEvent(QPaintEvent *);
private slots:
    void setImage(QImage );
    void dealClose();
private:
    Ui::Widget *ui;
    QImage image;
    QThread *thread;
    MyThread *myT;
};

#endif // WIDGET_H
