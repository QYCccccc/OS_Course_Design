#include "widget.h"
#include "ui_widget.h"
#include<QTimer>
#include<QDateTime>
#include<QDesktopWidget>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move((desktop->width() - this->width()), 0);	//移动窗口到右上角
    setWindowTitle(tr("电子钟"));	//设置标题
    m_timer = new QTimer(this);		//创建一个计时器
    m_timer->setSingleShot(false);	//设置为循环触发
    m_timer->setInterval(1000);		//设置触发间隔为1000msec
    m_timer->start();		//开始计时

    connect(m_timer, SIGNAL(timeout()), this, SLOT(ReciveTimer())); //关联计时器超时信号到自定义SLOT 
}

Widget::~Widget()
{
    delete ui;
}
void Widget::ReciveTimer()
{
    QDateTime dt = QDateTime::currentDateTime();    //获取当前时间

    QString strTime = dt.time().toString("HH:mm:ss");	//转换时间格式为QString

    ui->lcdNumber->display(strTime);	//在LCD上显示时间
}
