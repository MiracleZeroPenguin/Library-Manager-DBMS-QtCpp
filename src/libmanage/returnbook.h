#ifndef RETURNBOOK_H
#define RETURNBOOK_H

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
class Returnbook;
}

class Returnbook : public QDialog
{
    Q_OBJECT

public:
    explicit Returnbook(QWidget *parent = nullptr);
    ~Returnbook();

private slots:
    void on_btn_return_clicked();
    void opendb();

private:
    Ui::Returnbook *ui;
    QSqlDatabase db;
};

#endif // RETURNBOOK_H
