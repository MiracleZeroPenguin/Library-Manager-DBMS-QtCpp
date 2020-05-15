#ifndef SHOWRECORD_H
#define SHOWRECORD_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include<QDoubleValidator>
#include<QIntValidator>
#include<QSqlQuery>
#include<QSqlError>
#include<QTextStream>
#include"const.h"

namespace Ui {
class Showrecord;
}

class Showrecord : public QDialog
{
    Q_OBJECT

public:
    explicit Showrecord(QWidget *parent = nullptr);
    ~Showrecord();

private slots:
    void on_btn_search_clicked();
    void opendb();

private:
    Ui::Showrecord *ui;
    QSqlDatabase db;
};

#endif // SHOWRECORD_H
