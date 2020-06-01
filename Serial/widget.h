#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
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
    void on_OpenSerialButton_clicked();
    void ReadData();
    void on_SendButton_clicked();

private:
    Ui::Widget *ui;
    QSerialPort *serial;
};

#endif // WIDGET_H
