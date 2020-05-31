#ifndef COUNTTHREAD_H
#define COUNTTHREAD_H

#include <QObject>

class countThread : public QObject
{
    Q_OBJECT
public:
    explicit countThread(QObject *parent = nullptr);
    void timeOut();
    void setFlag(bool flag);
signals:
    void sendSignal();
public slots:
private:
    bool isSend;
};

#endif // COUNTTHREAD_H
