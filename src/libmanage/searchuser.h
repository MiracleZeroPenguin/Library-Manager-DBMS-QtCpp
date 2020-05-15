#ifndef SEARCHUSER_H
#define SEARCHUSER_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
namespace Ui {
class Searchuser;
}

class Searchuser : public QDialog
{
    Q_OBJECT

public:
    explicit Searchuser(QWidget *parent = nullptr);
    ~Searchuser();

private:
    Ui::Searchuser *ui;
    QSqlDatabase db;

private slots:
    void show_table();
    void opendb();
    void on_pushButton_clicked();
};

#endif // SEARCHUSER_H
