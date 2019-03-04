#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include<QTimer>
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
    void f_sum();
private:
    void sleep(int msec);
private:
    Ui::Widget *ui;
    QTimer *m_timer;
    int i, sum;
};

#endif // WIDGET_H
