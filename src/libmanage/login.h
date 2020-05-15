#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include<QSqlDatabase>
#include<QDebug>
#include<QtSql>
#include"const.h"
#include<QLineEdit>

namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();

private slots:
    void on_btn1_login_clicked();

private:
    Ui::login *uilogin;
    QSqlDatabase db;

signals:
    void  sendUsername(QString);

};


#endif // LOGIN_H
