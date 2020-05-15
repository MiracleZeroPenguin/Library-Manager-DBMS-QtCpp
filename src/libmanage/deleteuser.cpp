#include "deleteuser.h"
#include "ui_deleteuser.h"
#include"const.h"

Deleteuser::Deleteuser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Deleteuser)
{
    ui->setupUi(this);

}

Deleteuser::~Deleteuser()
{
    delete ui;
}

void Deleteuser::on_pushButton_clicked()
{
    opendb();
    if(!db.open()){
        qDebug()<<"不能连接deleteuser"<<"connect to mysql error";
        }
    else{
        qDebug()<<"连接成功deleteuser"<<"connect to mysql OK";
        QString delete_name;
        delete_name=ui->text_deletename->text();
        QSqlQuery query;
        QString str1;
        str1="drop user "+delete_name+"@'localhost';";
        qDebug()<<str1;
        bool success1=query.exec(str1);

        if(success1){
            qDebug()<<"删除用户成功";
            ui->label_deleteinfo->setText("删除用户"+delete_name+"成功");
        }
        else{
            qDebug()<<"删除用户失败";
            ui->label_deleteinfo->setText("删除用户"+delete_name+"失败");
        }
        db.close();
    }

}


void Deleteuser::opendb(){
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName(database);      //连接数据库名，与设置一致
    db.setUserName(username);          //数据库用户名，与设置一致
    db.setPassword(password);    //数据库密码，与设置一致
    db.open();
}
