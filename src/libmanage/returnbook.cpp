#include "returnbook.h"
#include "ui_returnbook.h"

Returnbook::Returnbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Returnbook)
{
    ui->setupUi(this);
    QDate date(QDate::currentDate());
        int year = date.year();
        int month = date.month();
        int day = date.day();
    ui->text_date->setText(QString::number(year)+"."+QString::number(month)+"."+QString::number(day));
    ui->text_date->setEnabled(0);
}

Returnbook::~Returnbook()
{
    delete ui;
}

void Returnbook::on_btn_return_clicked()
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
        str1="select return_date from borrow where bno='"+ui->text_bno->text()+"'and cno='"+ui->text_cno->text()+"';";
        qDebug()<<str1;
        query.exec(str1);
        if(!query.next()){
            ui->label_info->setText("该借书证无该记录");
        }
        else{
            qDebug()<<query.value(0).toString();
            if(query.value(0).toString()!="0"){
                ui->label_info->setText("本书已归还");
            }
            else{

                //有借书未还
                QString str2="update book set stock=stock+1 where bno='"+ui->text_bno->text()+"';";
                bool s1=query.exec(str2);
                int day=QDateTime::currentSecsSinceEpoch()/3600/24;
                qDebug()<<QString::number(day);
                str2="update borrow set return_date="+QString::number(day)+" where bno='"+ui->text_bno->text()+"' and cno='"+ui->text_cno->text()+"';";
                qDebug()<<str2;
                bool s2=query.exec(str2);
                if(s1&s2)ui->label_info->setText("归还成功");
                else ui->label_info->setText("归还失败");
            }
        }
    }
    db.close();
}

void Returnbook::opendb(){
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName(database);      //连接数据库名，与设置一致
    db.setUserName(username);          //数据库用户名，与设置一致
    db.setPassword(password);    //数据库密码，与设置一致
    db.open();
}
