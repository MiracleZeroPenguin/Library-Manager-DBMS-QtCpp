#ifndef CREATEUSER_H
#define CREATEUSER_H

#include <QDialog>
#include<QDebug>
#include<QSqlDatabase>
#include<QSqlQuery>
namespace Ui {
class Createuser;
}

class Createuser : public QDialog
{
    Q_OBJECT

public:
    explicit Createuser(QWidget *parent = nullptr);
    ~Createuser();

private slots:
    void on_pushButton_clicked();
    void opendb();

private:
    Ui::Createuser *ui;
    QSqlDatabase db;

};

#endif // CREATEUSER_H
