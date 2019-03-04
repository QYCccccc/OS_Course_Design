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
    m_timer = new QTimer(this);

    m_timer->setSingleShot(false);

    m_timer->setInterval(1000);

    connect(m_timer, SIGNAL(timeout()), this, SLOT(f_sum()) );
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

    if(i<=1000) {
        ++i;
        sum += i;
        str = str1 + QString::number(sum);
        ui->label->setText(str);
    }

}
