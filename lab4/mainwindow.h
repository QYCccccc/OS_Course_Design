#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStringList>
#include"cpu.h"
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

private:
    Ui::MainWindow *ui;
    cpu *mCpu;
};

#endif // MAINWINDOW_H
