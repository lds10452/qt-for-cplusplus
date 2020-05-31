#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTime>
#include<QTimer>
#include<QMediaPlayer>
#include"countthread.h"
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
    void clock();
    void btnEnable(bool isUsed);
    void secShow();
    void dealCount();
    void dealDestroyed();
private slots:
    void on_pushButtonSure_clicked();

    void on_pushButtonStop_clicked();

    void on_radioButton1_clicked();

    void on_radioButton2_clicked();

    void on_radioButton3_clicked();

    void on_pushButtonClear_clicked();

    void on_btnSecStart_2_clicked();

    void on_btnSecStop_clicked();

    void on_btnSecClear_clicked();

    void on_btnCdownStart_clicked();
    void on_btnCdownStop_clicked();

    void on_btnCdownClear_clicked();

signals:
    void countSignal();
private:
    Ui::Widget *ui;
    QTime temp;
    QTimer *myTimer;
    QTimer *secTimer;
    //QTimer *countTimer;
    QMediaPlayer *player=new QMediaPlayer(this);
    int sec=0;
    int hour=0;
    int min=0;
    int cSec;
    int cMin;
    int cHour;
    countThread *cntThread;
    QThread *myThread;
};

#endif // WIDGET_H
