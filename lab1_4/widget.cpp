#include "widget.h"
#include "ui_widget.h"
#include<QTime>
#include<QDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),i(0),sum(0)
{
    ui->setupUi(this);
    move(0, 0);
    m_timer = new QTimer(this);	//创建一个计时器对象

    m_timer->setSingleShot(false);	//设置计时器循环触发

    m_timer->setInterval(1000);		//设置计时器触发间隔为1000mesc

    connect(m_timer, SIGNAL(timeout()), this, SLOT(f_sum()) );//关联计时器超时信号到计算的函数
    m_timer->start();
    QFont ft;
    ft.setPointSize(20);
    ui->label->setFont(ft);
}

Widget::~Widget()
{
    delete ui;
}
void Widget::f_sum()
{
    QString str;
    QString str1("sum = ");
	//当计时器超时，触发该函数进行计算
    if(i<=1000) {
        sum += i;
        ++i;
        str = str1 + QString::number(sum);
        ui->label->setText(str);
    }
    else {
        m_timer->stop();	//计算完成后停止计时器
    }
}
