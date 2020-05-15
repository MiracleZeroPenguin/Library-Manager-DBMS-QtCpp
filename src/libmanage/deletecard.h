#ifndef DELETECARD_H
#define DELETECARD_H

#include <QDialog>
#include"const.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDebug>
#include<QSqlError>

namespace Ui {
class Deletecard;
}

class Deletecard : public QDialog
{
    Q_OBJECT

public:
    explicit Deletecard(QWidget *parent = nullptr);
    ~Deletecard();

private slots:
    void on_pushButton_clicked();
    void opendb();

private:
    Ui::Deletecard *ui;
    QSqlDatabase db;
};

#endif // DELETECARD_H
