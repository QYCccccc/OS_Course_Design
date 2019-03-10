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
    void isMsg(QStringList strlist);
protected:
    void run();
};

#endif // CPU_H
