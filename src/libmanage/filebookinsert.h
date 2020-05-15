#ifndef FILEBOOKINSERT_H
#define FILEBOOKINSERT_H

#include <QDialog>
#include<QFileDialog>
#include<QDebug>
#include<QSqlDatabase>
#include<QSqlQuery>
#include"const.h"
#include<QTextStream>
#include<iostream>
#include<QSqlError>
#include<QSqlQuery>
#include<QSqlQueryModel>

namespace Ui {
class Filebookinsert;
}

class Filebookinsert : public QDialog
{
    Q_OBJECT

public:
    explicit Filebookinsert(QWidget *parent = nullptr);
    ~Filebookinsert();

private slots:
    void on_pushButton_clicked();
    void opendb();

    void on_pushButton_2_clicked();

private:
    Ui::Filebookinsert *ui;
    QString filename;
    QSqlDatabase db;

};

#endif // FILEBOOKINSERT_H
