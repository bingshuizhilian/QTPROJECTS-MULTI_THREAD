#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QPlainTextEdit>
#include <QLayout>
#include <QString>
#include "mythread.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QVBoxLayout *mainLayout;
    QPlainTextEdit* pteOutput;

private slots:
    void onStartButton1Clicked();
    void onStopButton1Clicked();
    void onMythreadAupdateEvent(QString str);
    void onStartButton2Clicked();
    void onStopButton2Clicked();
    void onMythreadBupdateEvent(QString str);

private:
    MyThreadTypeA* mythreadA;
    QThread* containerOfmythreadB;
    MyThreadTypeB* mythreadB;
    bool isMythreadBactive;

private slots:
    void onThreadAfinished();
    void onThreadBfinished();
};

#endif // MAINWINDOW_H
