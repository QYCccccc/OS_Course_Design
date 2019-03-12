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
private slots:
    
    void on_actionShutdown_triggered();
    
    void on_actionReboot_triggered();
    
    void on_action_newproc_triggered();
    
    void on_action_exit_triggered();
    
    void on_action_refresh_triggered();
    
    void on_action_about_triggered();
    
    void on_action_triggered();
    
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
