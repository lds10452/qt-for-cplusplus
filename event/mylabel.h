#ifndef MYLABEL_H
#define MYLABEL_H

#include<QLabel>
class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = nullptr);

protected:
    void mousePressEvent(QMouseEvent *ev);
    void mouseMoveEvent(QMouseEvent *ev);
    void mouseReleaseEvent(QMouseEvent *ev);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
signals:

public slots:
};

#endif // MYLABEL_H
