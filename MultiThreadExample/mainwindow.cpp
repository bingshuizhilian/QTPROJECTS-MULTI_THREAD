#include "mainwindow.h"
#include <QDebug>
#include <QString>
#include <windows.h>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    mythreadA = new MyThreadTypeA;
    connect(mythreadA, &mythreadA->updateSignal, this, &onMythreadAupdateEvent);
    connect(mythreadA, &mythreadA->finished, this, &onThreadAfinished);

    QPushButton* btnStart1 = new QPushButton(tr("start multi thread 1"));
    connect(btnStart1, &btnStart1->clicked, this, &onStartButton1Clicked);
    QPushButton* btnStop1 = new QPushButton(tr("stop multi thread 1"));
    connect(btnStop1, &btnStop1->clicked, this, &onStopButton1Clicked);

    isMythreadBactive = false;

    QPushButton* btnStart2 = new QPushButton(tr("start multi thread 2"));
    connect(btnStart2, &btnStart2->clicked, this, &onStartButton2Clicked);
    QPushButton* btnStop2 = new QPushButton(tr("stop multi thread 2"));
    connect(btnStop2, &btnStop2->clicked, this, &onStopButton2Clicked);

    QPushButton* btnClear = new QPushButton(tr("clear screen"));
    pteOutput = new QPlainTextEdit;
    connect(btnClear, &btnClear->clicked, pteOutput, &pteOutput->clear);

    mainLayout = new QVBoxLayout;
    mainLayout->addWidget(btnStart1);
    mainLayout->addWidget(btnStop1);
    mainLayout->addWidget(btnStart2);
    mainLayout->addWidget(btnStop2);
    mainLayout->addWidget(btnClear);
    mainLayout->addWidget(pteOutput);

    QWidget *widget = new QWidget(this);
    widget->setLayout(mainLayout);
    this->setCentralWidget(widget);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onStartButton1Clicked()
{
    qDebug() << "start mythreadA";
    pteOutput->appendPlainText("start mythreadA");

    mythreadA->restartThread();

    if(!mythreadA->isRunning())
        mythreadA->start();

    qDebug() << "main thread id of A : " << QThread::currentThreadId();
    pteOutput->appendPlainText("main thread id of A : winapi GetCurrentThreadId() = 0x" + QString::number(GetCurrentThreadId(), 16));
}

void MainWindow::onStopButton1Clicked()
{
    qDebug() << "stop mythreadA";
    pteOutput->appendPlainText("stop mythreadA");

    if(mythreadA->isRunning())
    {
        mythreadA->closeThread();
        mythreadA->wait();
    }
}

void MainWindow::onMythreadAupdateEvent(QString str)
{
    pteOutput->appendPlainText(str);
}

void MainWindow::onThreadAfinished()
{
    qDebug() << "is mythreadA finished? : " << mythreadA->isFinished();
    pteOutput->appendPlainText("is mythreadA finished? : " + QString(mythreadA->isFinished() ? "true" : "false"));
}

void MainWindow::onStartButton2Clicked()
{
    qDebug() << "start mythreadB";
    pteOutput->appendPlainText("start mythreadB");

    if(isMythreadBactive)
        return;

    mythreadB = new MyThreadTypeB;
    containerOfmythreadB = new QThread;
    isMythreadBactive = true;

    mythreadB->moveToThread(containerOfmythreadB);
    connect(containerOfmythreadB, &containerOfmythreadB->finished, containerOfmythreadB, &containerOfmythreadB->deleteLater);
    connect(containerOfmythreadB, &containerOfmythreadB->started, mythreadB, &mythreadB->startThreadSlot);
    connect(containerOfmythreadB, &containerOfmythreadB->finished, this, &onThreadBfinished);

    connect(mythreadB, &mythreadB->updateSignal, this, &onMythreadBupdateEvent);

    mythreadB->restartThread();

    if(!containerOfmythreadB->isRunning())
        containerOfmythreadB->start();

    qDebug() << "main thread id of B : " << QThread::currentThreadId();
    pteOutput->appendPlainText("main thread id of B : winapi GetCurrentThreadId() = 0x" + QString::number(GetCurrentThreadId(), 16));
}

void MainWindow::onStopButton2Clicked()
{
    qDebug() << "stop mythreadB";
    pteOutput->appendPlainText("stop mythreadB");

    if(isMythreadBactive)
    {
        isMythreadBactive = false;

        mythreadB->closeThread();
        containerOfmythreadB->quit();
        containerOfmythreadB->wait();
    }
}

void MainWindow::onMythreadBupdateEvent(QString str)
{
    pteOutput->appendPlainText(str);
}

void MainWindow::onThreadBfinished()
{
    qDebug() << "is containerOfmythreadB finished? : " << containerOfmythreadB->isFinished();
    pteOutput->appendPlainText("is containerOfmythreadB finished? : " + QString(containerOfmythreadB->isFinished() ? "true" : "false"));
}
