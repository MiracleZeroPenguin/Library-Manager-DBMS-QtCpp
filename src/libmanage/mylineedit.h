#ifndef MYLINEEDIT_H
#define MYLINEEDIT_H
#include <QLineEdit>
#include <QMouseEvent>

class mylineedit: public QLineEdit
{
    Q_OBJECT
public:
   mylineedit();
    explicit mylineedit(QWidget *parent = 0);
protected:
    //重写mousePressEvent事件
    virtual void mousePressEvent(QMouseEvent *event);
signals:
    //自定义clicked()信号,在mousePressEvent事件发生时触发
    void clicked();
public slots:
};
#endif // MYLINEEDIT_H
