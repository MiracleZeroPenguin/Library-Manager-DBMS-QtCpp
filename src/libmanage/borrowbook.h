#ifndef BORROWBOOK_H
#define BORROWBOOK_H

#include <QDialog>
#include"const.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDebug>
#include<QSqlError>
#include<QColor>
#include<QSqlError>
#include<QDate>
#include<QDateTime>

namespace Ui {
class Borrowbook;
}

class Borrowbook : public QDialog
{
    Q_OBJECT

public:
    explicit Borrowbook(QWidget *parent = nullptr);
    ~Borrowbook();

private slots:
    void on_btn_borrow_clicked();
    void opendb();

private:
    Ui::Borrowbook *ui;
    QSqlDatabase db;
};

#endif // BORROWBOOK_H
