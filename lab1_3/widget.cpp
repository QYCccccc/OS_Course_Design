#include "widget.h"
#include "ui_widget.h"
#include<QDesktopWidget>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),count(0)
{
    ui->setupUi(this);
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move((desktop->width() - this->width())/2, 0);	//移动窗口到屏幕上部的中间位置
    m_timer = new QTimer(this); //创建定时器对象
    m_timer->setInterval(1000); //设置定时器触发间隔
    m_timer->setSingleShot(false); //设置定时器循环触发
    connect(m_timer, SIGNAL(timeout()), this, SLOT(RecvTimer()));//关联计时器超时信号到SLOT
    m_timer->start();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::RecvTimer()
{
    count = (count + 1) % 10;	//循环显示0-9
    ui->lcdNumber->display(count);	//在LCD中显示
}
