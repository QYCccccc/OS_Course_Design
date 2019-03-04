#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTimer> //计时器
namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = 0);
    ~Widget();
public slots:
    void RecvTimer(); //由定时器触发显示
private:
    Ui::Widget *ui;
    QTimer *m_timer;
    int count;
};

#endif // WIDGET_H
