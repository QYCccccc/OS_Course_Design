#include "cpu.h"
#include<QFile>
#include<sstream>
#include<string>
#include<QElapsedTimer>
#include<QMessageBox>
#include<QDebug>
cpu::cpu()
{

}
cpu::~cpu()
{
    
}
void cpu::run() {

    QString tempStr;
    QFile inFile;  
    int pos;
    inFile.setFileName("/proc/meminfo");
    if(!inFile.open(QIODevice::ReadOnly)) {
        QMessageBox::warning(NULL, tr("warning"),tr("The meminfo file can not open!"), QMessageBox::Yes);
        return ;
    }
    QString memTotal;
    QString memAvb;
    QString memUsed;
    
    QString swapTotal;
    QString swapFree;
    QString swapUsed;
    int nMemTotal, nMemAvb, nMemUsed, nSwapTotal, nSwapFree, nSwapUsed;
    while(true) {
        tempStr = inFile.readLine();
        pos = tempStr.indexOf("MemTotal");
        if(pos != -1) {
            memTotal = tempStr.mid(pos+10, tempStr.length() - 13);
            memTotal = memTotal.trimmed();
            nMemTotal = memTotal.toInt() / 1024;
        }
        else if( (pos = tempStr.indexOf("MemAvailable")) != -1) {
            
            
            memAvb = tempStr.mid(pos+14, tempStr.length()-17);
            memAvb = memAvb.trimmed();
            nMemAvb = memAvb.toInt()/1024;
        }
        else if ((pos = tempStr.indexOf("SwapTotal")) != -1) {
            swapTotal = tempStr.mid(pos+11, tempStr.length()-14);
            swapTotal = swapTotal.trimmed();
            nSwapTotal = swapTotal.toInt()/1024;
        }
        else if ((pos = tempStr.indexOf("SwapFree")) != -1) {
            swapFree = tempStr.mid(pos+10,tempStr.length()-13);
            swapFree = swapFree.trimmed();
            nSwapFree = swapFree.toInt()/1024;
            break;
        }
    }
    nMemUsed = nMemTotal - nMemAvb;
    nSwapUsed = nSwapTotal - nSwapFree;
    memUsed = QString::number(nMemUsed, 10);
    swapUsed = QString::number(nSwapUsed, 10);
    memTotal = QString::number(nMemTotal, 10);
    swapTotal = QString::number(nSwapTotal, 10);
    QStringList strlist;
    strlist << memUsed << memTotal << swapUsed << swapTotal 
            << QString::number(nMemUsed * 100 / nMemTotal)
            << QString::number(nSwapUsed * 100 / nSwapTotal);
    inFile.close();
    
    int tt = 2; //取2个点采样计算cpu当前利用律
    std::string cpu;
    long int user, nice, sys, idle, iowait, irq, softirq;
    long int all[2], idle_c[2];
    int  usage;
    QElapsedTimer t;
    while (tt)
    {
        inFile.setFileName("/proc/stat"); //打开CPU使用状态信息,linux下用/proc/stat文件来计算cpu的利用率
                                            //这个文件包含了所有CPU活动的信息，该文件中的所有值都是从系统启动开始累计到当前时刻。
        if ( !inFile.open(QIODevice::ReadOnly) )
        {
            QMessageBox::warning(NULL, tr("warning"), tr("The stat file can not open!"), QMessageBox::Yes);
            return;
        }
        tempStr = inFile.readLine();
        std::istringstream strStream(tempStr.toStdString());
        strStream>>cpu >> user >> nice >> sys
                    >> idle >> iowait >> irq >> softirq;
        all[tt-1] = user + nice + sys + idle +
                    iowait + irq + softirq;
        idle_c[tt -1] = idle;
         qDebug()<<"idle="<<idle;
        tt--;
        inFile.close(); //关闭stat文件

        t.start();
        while(t.elapsed()<500);
    }
    if(all[0] - all[1]){
     usage = (all[0] - all[1] - (idle_c[0] - idle_c[1]))*100 / (all[0] - all[1]);
     strlist << QString::number(usage);
    } else
        qDebug()<<"error\n";
    emit isMsg(strlist);
}
