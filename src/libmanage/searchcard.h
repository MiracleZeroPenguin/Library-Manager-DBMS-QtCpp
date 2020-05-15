#ifndef SEARCHCARD_H
#define SEARCHCARD_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include"const.h"

namespace Ui {
class Searchcard;
}

class Searchcard : public QDialog
{
    Q_OBJECT

public:
    explicit Searchcard(QWidget *parent = nullptr);
    ~Searchcard();

private slots:
    void on_check_cno_clicked(bool checked);

    void on_check_name_clicked(bool checked);

    void on_check_department_clicked(bool checked);

    void on_check_type_clicked(bool checked);

    void on_btn_search_clicked();
    void opendb();

private:
    Ui::Searchcard *ui;
    QSqlDatabase db;

};

#endif // SEARCHCARD_H
