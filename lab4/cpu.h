#ifndef CPU_H
#define CPU_H
#include<QStringList>
#include<QThread>
#include<QObject>
class cpu : public QThread
{
    Q_OBJECT
public:
    cpu();
    ~cpu();
signals:
    void isMsg(QStringList strlist);  // 用于发送跟CPU有关的信息到ui线程中
protected:
    void run();   //override QThread中的run，cpu线程的执行入口
};

#endif // CPU_H
