#ifndef SEARCHBOOK_H
#define SEARCHBOOK_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
#include"const.h"
#include<QDoubleValidator>
#include<QIntValidator>

namespace Ui {
class Searchbook;
}

class Searchbook : public QDialog
{
    Q_OBJECT

public:
    explicit Searchbook(QWidget *parent = nullptr);
    ~Searchbook();

private slots:
    void on_btn_search_clicked();
    void opendb();


private:
    Ui::Searchbook *ui;
    QSqlDatabase db;

private slots:
    //定义槽函数处理lineedit clicked
    //void handlelineeditclicked();
    void text_category_clicked();
    void text_title_clicked();
    void text_press_clicked();
    void text_year1_clicked();
    void text_year2_clicked();
    void text_author_clicked();
    void text_price1_clicked();
    void text_price2_clicked();


    void on_check_category_clicked(bool checked);
    void on_check_title_clicked(bool checked);
    void on_check_press_clicked(bool checked);
    void on_check_year_clicked(bool checked);
    void on_check_author_clicked(bool checked);
    void on_check_price_clicked(bool checked);
};

#endif // SEARCHBOOK_H
