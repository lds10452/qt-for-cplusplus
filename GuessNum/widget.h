#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QMovie>
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
    void dealNum();
private slots:
    void on_pushButtonStart_clicked();
    void on_pushButtonQuit_clicked();

    void on_pushButton_chop_clicked();

    void on_pushButton_tip_clicked();

protected:
    void timerEvent(QTimerEvent *event);
private:
    Ui::Widget *ui;
    int gameTime;       //游戏时间
    QString randStr;    //随机数
    int gameTimerId;    //游戏时间定时器ID
    int overTimerId;    //失败动画定时器ID
    int winTimerId;     //成功动画定时器ID
    QString resultStr;  //结果数

    QMovie overMovie;   //失败动画
    QMovie winMovie;    //胜利动画
};

#endif // WIDGET_H
