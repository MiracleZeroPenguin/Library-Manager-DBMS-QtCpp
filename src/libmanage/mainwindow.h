#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include"login.h"
#include"createuser.h"
#include"deleteuser.h"
#include"searchuser.h"
#include"singlebookinsert.h"
#include"filebookinsert.h"
#include"searchbook.h"
#include"addcard.h"
#include"deletecard.h"
#include"updatecard.h"
#include"searchcard.h"
#include"showrecord.h"
#include"borrowbook.h"
#include"returnbook.h"

#include<QDebug>
#include"const.h"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:


    void on_btn_login_clicked();

private:
    Ui::MainWindow *ui;
    login mylog;
    //login mylog;
    //Createuser mycreateuser;
    //Deleteuser mydeleteuser;


private slots:
    void receiveUsername(QString data);


    void on_user_manage_currentIndexChanged(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_book_insert_currentIndexChanged(const QString &arg1);

    void on_book_search_clicked();

    void on_card_manage_currentIndexChanged(int index);

    void on_book_return_currentIndexChanged(const QString &arg1);

    void on_book_borrow_currentIndexChanged(const QString &arg1);

signals:
    void sendSQL(QSqlDatabase);
};

#endif // MAINWINDOW_H
