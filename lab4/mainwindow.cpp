#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mCpu = new cpu;
    connect(mCpu, SIGNAL(isMsg(QStringList)), this, SLOT(RcvMsg_cpu(QStringList)));
    mCpu->start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::RcvMsg_cpu(QStringList strlist) {
    ui->label_mUsed->setText(strlist.at(0) + " MB");
    ui->label_mTotal->setText(strlist.at(1) + " MB");
    ui->label_sUsed->setText(strlist.at(2) + " MB");
    ui->label_sTotal->setText(strlist.at(3) + " MB");
    QString memR = strlist.at(4);
    QString swapR = strlist.at(5);
    QString cpuR = strlist.at(6);
    ui->progressBar_Mem->setValue(memR.toInt());
    ui->progressBar_Swap->setValue(swapR.toInt());
    ui->progressBar_cpu->setValue(cpuR.toInt());
}
