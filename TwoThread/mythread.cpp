#include "mythread.h"
#include<QThread>
#include<QDebug>
MyThread::MyThread(QObject *parent) : QObject(parent)
{
    isStop=false;
}
void MyThread::myTimeOut()
{
    while (!isStop) {
        QThread::sleep(1);
        emit mySignal();
        qDebug()<<"zi线程号为"<<QThread:: currentThread();
        if(isStop)
        {
            break;
        }
    }
}
void MyThread::setFlag(bool flag)
{
    isStop=flag;
}
