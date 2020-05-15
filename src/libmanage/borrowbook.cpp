#include "borrowbook.h"
#include "ui_borrowbook.h"
#include<QString>


Borrowbook::Borrowbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Borrowbook)
{
    ui->setupUi(this);
    QDate date(QDate::currentDate());
        int year = date.year();
        int month = date.month();
        int day = date.day();
    ui->text_date->setText(QString::number(year)+"."+QString::number(month)+"."+QString::number(day));
    ui->text_date->setEnabled(0);
    //qDebug()<<QString::number(QDateTime::currentSecsSinceEpoch()/3600/24/365);
}

Borrowbook::~Borrowbook()
{
    delete ui;
}

void Borrowbook::on_btn_borrow_clicked()
{
    opendb();
    ui->label_info->clear();
    QSqlQuery query(db);
    QString str1="select * from card where cno='"+ui->text_cno->text()+"';";
    query.exec(str1);
    if(!query.next()){
        ui->label_info->setText("不存在该借书证");
    }
    else{
        str1="select stock from book where bno='"+ui->text_bno->text()+"';";
        qDebug()<<str1;
        query.exec(str1);
        if(!query.next()){
            ui->label_info->setText("不存在该书号");
        }
        else{
            if(query.value(0).toInt()>0){
                //有库存
                QString str2="update book set stock=stock-1 where bno='"+ui->text_bno->text()+"';";
                bool s1=query.exec(str2);
                int day=QDateTime::currentSecsSinceEpoch()/3600/24;
                qDebug()<<QString::number(day);
                str2="insert into borrow values('"+ui->text_cno->text()+"','"+ui->text_bno->text()+"',"+QString::number(day)+",null);";
                bool s2=query.exec(str2);
                if(s1&s2)ui->label_info->setText("借阅成功");
                else ui->label_info->setText("借阅失败，该借书证已借阅该书");
            }
            else{
                ui->label_info->setText("本书无库存");
                QString str3="select borrow_date from borrow where bno='"+ui->text_bno->text()+"';";
                query.exec(str3);
                query.next();
                int date=query.value(0).toInt();

                while(query.next()){
                    if(query.value(0).toInt()>date)date=query.value(0).toInt();
                }
                QString temp;
                temp=QDateTime::fromSecsSinceEpoch(date*24*3600).toString();
                QList<QString>lst;
                lst=temp.split(' ');
                ui->label_info->setText("本书无库存，最近借阅时间为"+lst[4]+"年"+lst[1]+lst[2]);
                qDebug()<<temp;
            }
        }
    }
    db.close();
}

void Borrowbook::opendb(){
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName(database);      //连接数据库名，与设置一致
    db.setUserName(username);          //数据库用户名，与设置一致
    db.setPassword(password);    //数据库密码，与设置一致
    db.open();
}
