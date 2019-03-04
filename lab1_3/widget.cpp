#include "widget.h"
#include "ui_widget.h"
#include<QDesktopWidget>
Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget),count(0)
{
    ui->setupUi(this);
    QDesktopWidget* desktop = QApplication::desktop(); // =qApp->desktop();也可以
    move((desktop->width() - this->width())/2, 0);
    m_timer = new QTimer(this); //创建定时器对象
    m_timer->setInterval(1000); //设置定时器触发间隔
    m_timer->setSingleShot(false); //设置定时器循环触发
    connect(m_timer, SIGNAL(timeout()), this, SLOT(RecvTimer()));
    m_timer->start();
}

Widget::~Widget()
{
    delete ui;
}
void Widget::RecvTimer()
{
    count = (count + 1) % 10;
    ui->lcdNumber->display(count);
}
