#ifndef DELETEUSER_H
#define DELETEUSER_H

#include <QDialog>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QDebug>
namespace Ui {
class Deleteuser;
}

class Deleteuser : public QDialog
{
    Q_OBJECT

public:
    explicit Deleteuser(QWidget *parent = nullptr);
    ~Deleteuser();

private slots:
    void on_pushButton_clicked();
    void opendb();

private:
    Ui::Deleteuser *ui;
    QSqlDatabase db;
};

#endif // DELETEUSER_H
