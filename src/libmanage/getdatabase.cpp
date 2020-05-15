#include "getdatabase.h"
#include "ui_getdatabase.h"
#include"const.h"
#include"mainwindow.h"
QString database;

Getdatabase::Getdatabase(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Getdatabase)
{
    ui->setupUi(this);
}

Getdatabase::~Getdatabase()
{
    delete ui;
}

void Getdatabase::on_pushButton_clicked()
{
    database=ui->text_database->text();
    MainWindow * mymain=new MainWindow;
    mymain->show();
    this->close();
}
