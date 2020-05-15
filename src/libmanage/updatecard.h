#ifndef UPDATECARD_H
#define UPDATECARD_H

#include <QDialog>
#include"const.h"
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlQueryModel>
#include<QDebug>
#include<QSqlError>
#include<QColor>
#include<QSqlError>

namespace Ui {
class Updatecard;
}

class Updatecard : public QDialog
{
    Q_OBJECT

public:
    explicit Updatecard(QWidget *parent = nullptr);
    ~Updatecard();

private slots:
    void on_btn_check_clicked();
    void opendb();
    void on_check_name_clicked(bool checked);
    void on_check_department_clicked(bool checked);
    void on_check_type_clicked(bool checked);

    void on_btn_update_clicked();

private:
    Ui::Updatecard *ui;
    QSqlDatabase db;
};

#endif // UPDATECARD_H
