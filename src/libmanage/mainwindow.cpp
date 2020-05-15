#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    login *dlg = &mylog;
    connect(dlg,SIGNAL(sendUsername(QString)),this,SLOT(receiveUsername(QString)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_login_clicked()
{
    mylog.show();
}

void MainWindow::receiveUsername(QString data)
{
    ui->label4_username->setText(data);
    if(username=="root"){
        ui->user_manage->setEnabled(1);
    }
    else{
        ui->user_manage->setEnabled(0);
    }
    ui->book_insert->setEnabled(1);
    ui->btn_login->setEnabled(1);
    ui->book_borrow->setEnabled(1);
    ui->book_return->setEnabled(1);
    ui->card_manage->setEnabled(1);
    ui->book_search->setEnabled(1);
}



void MainWindow::on_user_manage_currentIndexChanged(const QString &arg1)
{
    if(ui->user_manage->currentIndex() == 1){
        Createuser * mycrea=new Createuser;
        mycrea->show();//新增管理员
    }
    else if(ui->user_manage->currentIndex() == 2){
        Deleteuser *mydele=new Deleteuser;
        mydele->show();
    }
    else if(ui->user_manage->currentIndex() == 3){
        Searchuser * mysear=new Searchuser;
        mysear->show();
    }
    ui->user_manage->setCurrentIndex(0);
}

void MainWindow::on_pushButton_2_clicked()
{
    username="";
    password="";
    ui->user_manage->setEnabled(0);
    ui->book_insert->setEnabled(0);
    ui->label4_username->setText("游客");// 登出


    ui->book_borrow->setEnabled(0);
    ui->book_return->setEnabled(0);
    ui->card_manage->setEnabled(0);
    ui->book_search->setEnabled(0);
}

void MainWindow::on_book_insert_currentIndexChanged(const QString &arg1)
{
    if(ui->book_insert->currentIndex()==1){
        Singlebookinsert * mysbookin=new Singlebookinsert;
        mysbookin->show();
    }
    if(ui->book_insert->currentIndex()==2){
        Filebookinsert * myfbookin=new Filebookinsert;
        myfbookin->show();
    }
    ui->book_insert->setCurrentIndex(0);
}

void MainWindow::on_book_search_clicked()
{
    Searchbook * mysbook=new Searchbook;
    mysbook->show();
}

void MainWindow::on_card_manage_currentIndexChanged(int index)
{
    if(ui->card_manage->currentIndex()==1){
        Addcard * myaddc=new Addcard;
        myaddc->show();
    }
    else if(ui->card_manage->currentIndex()==2){
        Updatecard * myupdc=new Updatecard;
        myupdc->show();
    }
    else if(ui->card_manage->currentIndex()==3){
        Deletecard * mydelc=new Deletecard;
        mydelc->show();
    }
    else if(ui->card_manage->currentIndex()==4){
        Searchcard * myseac=new Searchcard;
        myseac->show();
    }

    ui->card_manage->setCurrentIndex(0);
}

void MainWindow::on_book_return_currentIndexChanged(const QString &arg1)
{
    if(ui->book_return->currentIndex()==1){//显示
        Showrecord * myshowr=new Showrecord;
        myshowr->show();
    }
    else if(ui->book_return->currentIndex()==2){//还书
        Returnbook * myretnb=new Returnbook;
        myretnb->show();
    }
    ui->book_return->setCurrentIndex(0);
}

void MainWindow::on_book_borrow_currentIndexChanged(const QString &arg1)
{
    if(ui->book_borrow->currentIndex()==1){
        Showrecord * myshowr=new Showrecord;
        myshowr->show();
    }
    else if(ui->book_borrow->currentIndex()==2){//借书
        Borrowbook * myborrb=new Borrowbook;
        myborrb->show();
    }
}
