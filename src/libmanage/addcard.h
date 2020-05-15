#ifndef ADDCARD_H
#define ADDCARD_H

#include <QDialog>
#include"const.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDebug>
#include<QSqlError>
namespace Ui {
class Addcard;
}

class Addcard : public QDialog
{
    Q_OBJECT

public:
    explicit Addcard(QWidget *parent = nullptr);
    ~Addcard();

private slots:
    void on_pushButton_clicked();
    void opendb();

private:
    Ui::Addcard *ui;
    QSqlDatabase db;
};

#endif // ADDCARD_H
