#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStringList>
#include"cpu.h"
#include<QTimer>
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
public slots:
    void RcvMsg_cpu(QStringList strlist);
    void RcvTimer();
private:
    void ShowModule();
    void ShowSysinfo();
    void ShowProcess();

private:
    Ui::MainWindow *ui;
    cpu *mCpu;
    QTimer * mtimer;
};

#endif // MAINWINDOW_H
