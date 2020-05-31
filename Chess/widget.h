#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
protected:
    //重写绘图事件
    void paintEvent(QPaintEvent *);
    //重写鼠标按下事件
    void mousePressEvent(QMouseEvent *e);

private:
    int gridW;  //棋盘水平方向一个格子的宽度
    int gridH;  //棋盘水平方向一个格子的高度
    int startX; //棋盘起点x坐标
    int startY; //棋盘起点y坐标

    int chessX, chessY; //棋盘下标

    Ui::Widget *ui;
};

#endif // WIDGET_H
