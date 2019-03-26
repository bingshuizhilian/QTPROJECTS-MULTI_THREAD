#include "mythread.h"
#include <QDebug>
#include <windows.h>

MyThreadTypeA::MyThreadTypeA()
{
    isStop = false;
}

void MyThreadTypeA::closeThread()
{
    isStop = true;
}

void MyThreadTypeA::restartThread()
{
    isStop = false;
}

void MyThreadTypeA::run()
{
    while(true)
    {
        if(isStop)
            return;

        emit updateSignal("mythreadA winapi GetCurrentThreadId() = 0x" + QString::number(GetCurrentThreadId(), 16));

        qDebug() << "mythreadA QThread::currentThreadId() = " << QThread::currentThreadId();

        sleep(1);
    }
}

MyThreadTypeB::MyThreadTypeB(QObject *parent) : QObject(parent)
{
    isStop = false;
}

void MyThreadTypeB::closeThread()
{
    isStop = true;
}

void MyThreadTypeB::restartThread()
{
    isStop = false;
}

void MyThreadTypeB::startThreadSlot()
{
    while(true)
    {
        if(isStop)
            return;

        emit updateSignal("mythreadB winapi GetCurrentThreadId() = 0x" + QString::number(GetCurrentThreadId(), 16));
        qDebug() << "mythreadB QThread::currentThreadId() = " << QThread::currentThreadId();

        QThread::sleep(1);
    }
}
