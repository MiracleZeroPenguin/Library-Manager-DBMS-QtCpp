#include "deletecard.h"
#include "ui_deletecard.h"

Deletecard::Deletecard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Deletecard)
{
    ui->setupUi(this);
}

Deletecard::~Deletecard()
{
    delete ui;
}

void Deletecard::on_pushButton_clicked()
{
    opendb();
    if(!db.isOpen()){
        qDebug()<<"数据库连接失败";
    }
    else{
        qDebug()<<"数据库连接成功";
        QString cno;
        cno=ui->text_cno->text();
        if(cno.isEmpty()){
            ui->label_deleteinfo->setText("必须输入卡号");
        }
        else{

            //****************查询是否已经存在该借书证**********
            QString str1="select * from card where cno='"+cno+"';";
            qDebug()<<str1;
            QSqlQuery query1;
            query1.exec(str1);
            if(!query1.next()){
                qDebug()<<"不存在该卡号";
                ui->label_deleteinfo->setText("不存在卡号"+cno);
            }
            //**************删除借书证***********
            else{
                str1="delete from card where cno='"+cno+"';";

                qDebug()<<str1;
                QSqlQuery query2;
                bool success2=query2.exec(str1);
                if(success2){
                    qDebug()<<"删除借书证成功";
                    ui->label_deleteinfo->setText("删除借书证"+cno+"成功");
                }
                else {
                    qDebug()<<"删除借书证失败";
                    QString error=query1.lastError().text();
                    ui->label_deleteinfo->setText(error);
                }
            }
        }
        db.close();
    }
}

void Deletecard::opendb(){
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName(database);      //连接数据库名，与设置一致
    db.setUserName(username);          //数据库用户名，与设置一致
    db.setPassword(password);    //数据库密码，与设置一致
    db.open();
}
