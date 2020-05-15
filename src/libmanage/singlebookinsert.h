#ifndef SINGLEBOOKINSERT_H
#define SINGLEBOOKINSERT_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include<QDoubleValidator>
#include<QIntValidator>
#include<QSqlQueryModel>
#include<QSqlError>
#include<QTextStream>
#include"const.h"
namespace Ui {
class Singlebookinsert;
}

class Singlebookinsert : public QDialog
{
    Q_OBJECT

public:
    explicit Singlebookinsert(QWidget *parent = nullptr);
    ~Singlebookinsert();

private slots:
    void on_btn_insert_clicked();
    void opendb();

private:
    Ui::Singlebookinsert *ui;
    QSqlDatabase db;
};

#endif // SINGLEBOOKINSERT_H
