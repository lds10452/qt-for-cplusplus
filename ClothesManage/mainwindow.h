#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"domxml.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void connectDb();
    void initData();
private slots:
    void on_actionCar_triggered();

    void on_actionCalc_triggered();

    void on_comboBoxFactory_currentIndexChanged(const QString &arg1);

    void on_comboBoxBrand_currentIndexChanged(const QString &arg1);

    void on_spinBox_valueChanged(int arg1);

    void on_pushButtonCancel_clicked();

    void on_pushButtonSure_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
