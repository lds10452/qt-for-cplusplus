#include "countthread.h"
#include<QThread>
countThread::countThread(QObject *parent) : QObject(parent)
{

}

void countThread::timeOut()
{
    while(isSend)
    {
        QThread::sleep(1);
        emit sendSignal();
    }
}
void countThread::setFlag(bool flag)
{
    isSend=flag;
}
