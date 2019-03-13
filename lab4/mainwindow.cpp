#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QMessageBox>
#include<QDir>
#include<vector>
#include<algorithm>
#include<sys/types.h>
#include<QLineEdit>
#include<QInputDialog>
#include<signal.h>
#include<QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mCpu = new cpu;
    //将发送cpu信息的函数和接受信息的函数关联起来
    connect(mCpu, SIGNAL(isMsg(QStringList)), this, SLOT(RcvMsg_cpu(QStringList)));
    //使用定时器定期刷新页面
    mtimer = new QTimer(this);
    mtimer->setInterval(100);
    mtimer->setSingleShot(false);
    mtimer->start();
    //当计时器超时后刷新当前页面
    connect(mtimer, SIGNAL(timeout()), this, SLOT(RcvTimer()));
    //设置资源信息为默认首页
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
        ui->tableWidget_proc->clear();
        ui->tableWidget_proc->setRowCount(0);   
        ShowProcess();
        break;
    case 2:
        ui->tableWidget_module->clear();
        ui->tableWidget_module->setRowCount(0);
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
    QDir dr("/proc");
    QFile inFile;
    QString tmpstr;
    QStringList header;
    //将首列显示的行号取消
    ui->tableWidget_proc->verticalHeader()->setHidden(true);
    ui->tableWidget_proc->setColumnCount(5);
    //设置每列标题
    header << "PID" << "名称" << "状态" << "优先级" << "内存";
    ui->tableWidget_proc->setHorizontalHeaderLabels(header);
    //禁止编辑
    ui->tableWidget_proc->setEditTriggers(QAbstractItemView::NoEditTriggers);
    //选择一整行
    ui->tableWidget_proc->setSelectionBehavior(QAbstractItemView::SelectRows);
    //设置只能选择一个单元
    ui->tableWidget_proc->setSelectionMode(QAbstractItemView::SingleSelection);
    bool isInt;
    std::vector<int> vpid;
    int pidInt;
    QStringList drlist = dr.entryList();
    for(int i = 0; i < drlist.length(); ++i){
        //将pid号保存到一个数组中
        pidInt = drlist.at(i).toInt(&isInt, 10);
        if(isInt) {
            vpid.push_back(pidInt);
        }
    }
    //将pid排序
    std::sort(vpid.begin(), vpid.end());
    int posa, posb;
    int rowcount;
    QString pName, pState, pPrio, pMem;
    for(auto e : vpid) {
        //读取每个进程的信息
        inFile.setFileName("/proc/" + QString::number(e) + "/stat");
        if(!inFile.open(QIODevice::ReadOnly)) {
            QMessageBox::warning(this, tr("warning"), tr("The pid stat file can not open!"), QMessageBox::Yes);
            return;
        }
        tmpstr = inFile.readLine();
        posa = tmpstr.indexOf("(");
        posb = tmpstr.indexOf(")");
        pName = tmpstr.mid(posa+1, posb-posa-1).trimmed();
        //利用空格将字符串分割
        pState = tmpstr.section(" ", 2, 2);
        pPrio = tmpstr.section(" ", 17, 17);
        pMem = QString::number((tmpstr.section(" ", 22, 22).toInt()) / (1024 * 1024));
        rowcount = ui->tableWidget_proc->rowCount();
        ui->tableWidget_proc->insertRow(rowcount);
        ui->tableWidget_proc->setItem(rowcount, 0, new QTableWidgetItem(QString::number(e)));
        ui->tableWidget_proc->setItem(rowcount, 1, new QTableWidgetItem(pName));
        ui->tableWidget_proc->setItem(rowcount, 2, new QTableWidgetItem(pState));
        ui->tableWidget_proc->setItem(rowcount, 3, new QTableWidgetItem(pPrio));            
        ui->tableWidget_proc->setItem(rowcount, 4, new QTableWidgetItem(pMem + "MB"));
        ui->tableWidget_proc->item(rowcount, 4)->setTextAlignment(Qt::AlignRight);
        inFile.close();
    }
    //设置单元格根据内容自动调整
    ui->tableWidget_proc->resizeRowsToContents();
    ui->tableWidget_proc->resizeColumnsToContents();
}

void MainWindow::ShowModule() {
    QFile inFile;
    inFile.setFileName("/proc/modules");
    if(!inFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(this, tr("warning"), tr("The modules file can not open!"), QMessageBox::Yes);
        return ;
    }
    QString tempStr;
    QString modName, modMem, modNum;
    QStringList header;
    int rowcount;
    ui->tableWidget_module->setColumnCount(3);
    header << "名称" << "内存" << "使用次数";
    ui->tableWidget_module->setHorizontalHeaderLabels(header);
    ui->tableWidget_module->setEditTriggers(QAbstractItemView::NoEditTriggers);
    
    ui->tableWidget_module->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget_module->setSelectionMode(QAbstractItemView::SingleSelection);
    //
    while ((tempStr = inFile.readLine()) != nullptr) {
        modName = tempStr.section(" ", 0, 0);
        modMem = QString::number(tempStr.section(" ", 1, 1).toInt() / 1024);
        modNum = tempStr.section(" ", 2, 2);
        rowcount = ui->tableWidget_module->rowCount();
        ui->tableWidget_module->insertRow(rowcount);
        ui->tableWidget_module->setItem(rowcount, 0, new QTableWidgetItem(modName));
        ui->tableWidget_module->setItem(rowcount, 1, new QTableWidgetItem(modMem + " MB"));
        ui->tableWidget_module->item(rowcount, 1)->setTextAlignment(Qt::AlignRight);       
        ui->tableWidget_module->setItem(rowcount, 2, new QTableWidgetItem(modNum));
    }
    ui->tableWidget_module->resizeRowsToContents();
    ui->tableWidget_module->resizeColumnsToContents();
    inFile.close();
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
    while((tempStr = inFile.readLine()) != nullptr) {
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

void MainWindow::on_actionShutdown_triggered()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(this, tr("warning"), 
                        tr("Power Off"),QMessageBox::Yes | QMessageBox::No);
    if(rb == QMessageBox::Yes) {
            system("poweroff");    
        qDebug() << "Power Off";
    }
}

void MainWindow::on_actionReboot_triggered()
{
    QMessageBox::StandardButton rb = QMessageBox::warning(this, tr("warning"), 
                        tr("Reboot"),QMessageBox::Yes | QMessageBox::No);
    if(rb == QMessageBox::Yes) {
            system("reboot");    
        qDebug() << "reboot";
    }
}

void MainWindow::on_action_newproc_triggered()
{
    bool isOK;
    QString procName = QInputDialog::getText(nullptr,"Create proc","please input proc name",
                                             QLineEdit::Normal,nullptr, &isOK);
    if(isOK && !procName.isEmpty()){
        procName += " &";
        system(procName.toStdString().c_str());
    }
    else {
        qDebug()<<"Hahaha";
    }
}

void MainWindow::on_action_exit_triggered()
{
    this->close();
}

void MainWindow::on_action_refresh_triggered()
{
    RcvTimer();
}

void MainWindow::on_action_about_triggered()
{
    QMessageBox::aboutQt(nullptr, "About Qt"); 
}

void MainWindow::on_action_triggered()
{
    bool isOK;
    QString pid = QInputDialog::getText(nullptr,"Kill process","please input process pid ",
                                        QLineEdit::Normal,nullptr, &isOK);
    if(isOK && !pid.isEmpty()) {
        kill(pid.toInt(), SIGKILL);
    }
}
