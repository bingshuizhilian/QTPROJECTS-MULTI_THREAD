#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QObject>
#include <QString>
#include <pthread.h>

class MyThreadTypeA : public QThread
{
    Q_OBJECT

public:
    MyThreadTypeA();
    void closeThread();
    void restartThread();

protected:
    virtual void run();

signals:
    void updateSignal(QString info);

private:
    volatile bool isStop;       //isStop是易失性变量，需要用volatile进行申明
};

class MyThreadTypeB : public QObject
{
    Q_OBJECT

public:
    explicit MyThreadTypeB(QObject* parent = nullptr);
    void closeThread();
    void restartThread();

signals:
    void updateSignal(QString info);

public slots:
    void startThreadSlot();

private:
    volatile bool isStop;
};

#endif // MYTHREAD_H

