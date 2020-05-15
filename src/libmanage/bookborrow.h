#ifndef BOOKBORROW_H
#define BOOKBORROW_H

#include <QDialog>

namespace Ui {
class bookborrow;
}

class bookborrow : public QDialog
{
    Q_OBJECT

public:
    explicit bookborrow(QWidget *parent = nullptr);
    ~bookborrow();

private:
    Ui::bookborrow *ui;
};

#endif // BOOKBORROW_H
