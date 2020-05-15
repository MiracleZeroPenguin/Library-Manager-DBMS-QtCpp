#include "createuser.h"
#include "ui_createuser.h"
#include"const.h"

Createuser::Createuser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Createuser)
{
    ui->setupUi(this);
}

Createuser::~Createuser()
{
    delete ui;
}

void Createuser::on_pushButton_clicked()
{
    opendb();
    //QSqlDatabase db;

    if(!db.open()){
        qDebug()<<"不能连接createuser"<<"connect to mysql error";
        }
    else{
        qDebug()<<"连接成功createuser"<<"connect to mysql OK";
        QString new_username;
        QString new_password;
        new_username=ui->text_newname->text();
        new_password=ui->text_newpassword->text();
        QSqlQuery query;
        QString str1;
        str1="CREATE USER '"+new_username+"'@'localhost' IDENTIFIED BY '"+new_password+"';";
        qDebug()<<str1;
        QString str2;
        str2="GRANT select ON libmanage.* TO '"+new_username+"'@'localhost';";
        qDebug()<<str2;
        QString str3;
        str3="GRANT create ON libmanage.* TO '"+new_username+"'@'localhost';";
        QString str4;
        str4="GRANT delete ON libmanage.* TO '"+new_username+"'@'localhost';";
        QString str5;
        str5="GRANT insert ON libmanage.* TO '"+new_username+"'@'localhost';";
        bool success1=query.exec(str1);
        bool success2=query.exec(str2);
        bool success3=query.exec(str3);
        bool success4=query.exec(str4);
        bool success5=query.exec(str5);
        if(success1*success2*success3*success4*success5){
            qDebug()<<"创建用户成功";
            ui->label_createinfo->setText("创建用户"+new_username+"成功");
        }
        else{
            qDebug()<<"创建用户失败";
            ui->label_createinfo->setText("创建用户"+new_username+"失败");
        }
    }
    db.close();
}

void Createuser::opendb(){
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName(database);      //连接数据库名，与设置一致
    db.setUserName(username);          //数据库用户名，与设置一致
    db.setPassword(password);    //数据库密码，与设置一致
    db.open();
}



