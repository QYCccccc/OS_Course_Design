#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QMessageBox>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mCpu = new cpu;
    connect(mCpu, SIGNAL(isMsg(QStringList)), this, SLOT(RcvMsg_cpu(QStringList)));
    mtimer = new QTimer(this);
    mtimer->setInterval(100);
    mtimer->setSingleShot(false);
    mtimer->start();
    connect(mtimer, SIGNAL(timeout()), this, SLOT(RcvTimer()));
    ui->tabWidget->setCurrentIndex(0);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::RcvTimer(){
    int index = ui->tabWidget->currentIndex();
    switch (index) {
    case 0:
        mCpu->start();
        break;
    case 1:
        ShowProcess();
        break;
    case 2:
        ShowModule();
        break;
    case 3:
        ShowSysinfo();
        break;
    default:
        break;
    }
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
void MainWindow::ShowProcess() {
    
}

void MainWindow::ShowModule() {
    QStringList header;
    ui->tableWidget_module->adjustSize();
    ui->tableWidget_module->setColumnCount(3);
    header << "名称" << "内存" << "使用次数";
    ui->tableWidget_module->setHorizontalHeaderLabels(header);
    int rowcount = ui->tableWidget_module->rowCount();
    ui->tableWidget_module->insertRow(rowcount);
    
}

void MainWindow::ShowSysinfo() {
    QFile inFile;
    QString tempStr;
    int pos;
    inFile.setFileName(("/proc/cpuinfo"));
    if(!inFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("warning"), tr("The cpuinfo file can not open!"),QMessageBox::Yes);
        return ;
    }
    while((tempStr = inFile.readLine()) != NULL) {
        if((pos = tempStr.indexOf("model name")) != -1) {
            pos += 13;
            QString cpu_name = tempStr.mid(pos, tempStr.length());
            ui->label_cpuname->adjustSize();
            ui->label_cpuname->setText(cpu_name);
        }
        else if((pos = tempStr.indexOf("cpu cores")) != -1) {
            pos += 12;
            QString cpu_core = tempStr.mid(pos, tempStr.length());
//            qDebug() << cpu_core.length() << "str = " << cpu_core;
            ui->label_cpucore->adjustSize();
            ui->label_cpucore->setText(cpu_core);
        }
        else if((pos = tempStr.indexOf("cache size")) != -1) {
            pos += 13;
            QString cacheStr = tempStr.mid(pos, tempStr.length());
            ui->label_cachesize->adjustSize();
            ui->label_cachesize->setText(cacheStr);
        }
    }
    inFile.close();
    
    inFile.setFileName("/proc/version");
    if(!inFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("warning"), tr("The version file can not open!"),QMessageBox::Yes);
        return ;
    }
    tempStr = inFile.readLine();
    pos = tempStr.indexOf("(");
    QString versionStr = tempStr.mid(0, pos);
    ui->label_sysinfo->adjustSize();
    ui->label_sysinfo->setText(versionStr);
    inFile.close();
}
