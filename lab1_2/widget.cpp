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
    move((desktop->width() - this->width()), 0);
    setWindowTitle(tr("电子钟"));
    m_timer = new QTimer(this);
    m_timer->setSingleShot(false);
    m_timer->setInterval(1000);
    m_timer->start();

    connect(m_timer, SIGNAL(timeout()), this, SLOT(ReciveTimer()));
}

Widget::~Widget()
{
    delete ui;
}
void Widget::ReciveTimer()
{
    QDateTime dt = QDateTime::currentDateTime();

    QString strTime = dt.time().toString("HH:mm:ss");

    ui->lcdNumber->display(strTime);
}
