#include "showrecord.h"
#include "ui_showrecord.h"
#include<QDebug>
#include<QDateTime>
Showrecord::Showrecord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Showrecord)
{
    ui->setupUi(this);
}

Showrecord::~Showrecord()
{
    delete ui;
}

void Showrecord::on_btn_search_clicked()
{
    ui->table_borrow->clearContents();
    ui->label_info->clear();
    opendb();
    QString searchcno;
    QSqlQuery query;
    searchcno="select * from card where cno='"+ui->text_cno->text()+"';";
    qDebug()<<searchcno;
    bool exist=query.exec(searchcno);
    if(!query.next()){
        ui->label_info->setText("不存在该借书证");
    }
    else{
        QString searchbook;
        searchbook="select bno,borrow_date,return_date from borrow where borrow.cno='"+ui->text_cno->text()+"';";
        qDebug()<<searchbook;
        query.exec(searchbook);
        int i=0;
        //**************************

        //
        while(query.next()){
            if(!ui->check_ifreturn->isChecked()){
                i=i+1;
                ui->table_borrow->setRowCount(i);

                int date=query.value(1).toInt();
                QString temp;
                temp=QDateTime::fromSecsSinceEpoch(date*24*3600).toString();
                QList<QString>lst;
                lst=temp.split(' ');
                ui->table_borrow->setItem(i-1,0,new QTableWidgetItem(lst[4]+"年"+lst[1]+lst[2]));

                //ui->table_borrow->setItem(i-1,0,new QTableWidgetItem(query.value(1).toString()));
                ui->table_borrow->setItem(i-1,2,new QTableWidgetItem(query.value(0).toString()));
                if(query.value(2).toString()=="0")
                    ui->table_borrow->setItem(i-1,1,new QTableWidgetItem("未还"));
                else{
                    date=query.value(2).toInt();
                    temp=QDateTime::fromSecsSinceEpoch(date*24*3600).toString();
                    lst=temp.split(' ');
                    ui->table_borrow->setItem(i-1,1,new QTableWidgetItem(lst[4]+"年"+lst[1]+lst[2]));
                }

               QString str2="select * from book where bno='"+query.value(0).toString()+"';";
               QSqlQuery query2;
               qDebug()<<str2;
               bool s=query2.exec(str2);
               while(query2.next()){
                   ui->table_borrow->setItem(i-1,3,new QTableWidgetItem(query2.value("category").toString()));
                   ui->table_borrow->setItem(i-1,4,new QTableWidgetItem(query2.value("title").toString()));
                   ui->table_borrow->setItem(i-1,5,new QTableWidgetItem(query2.value("year").toString()));
                   ui->table_borrow->setItem(i-1,6,new QTableWidgetItem(query2.value("press").toString()));
                   ui->table_borrow->setItem(i-1,7,new QTableWidgetItem(query2.value("author").toString()));
                   ui->table_borrow->setItem(i-1,8,new QTableWidgetItem(query2.value("price").toString()));
                   ui->table_borrow->setItem(i-1,9,new QTableWidgetItem(query2.value("total").toString()));
                   ui->table_borrow->setItem(i-1,10,new QTableWidgetItem(query2.value("stock").toString()));
               }
            }
            else{
                qDebug()<<query.value(2).toString();
                if(query.value(2).toString()=="0"){

                    i=i+1;
                    ui->table_borrow->setRowCount(i);

                    int date=query.value(1).toInt();
                    QString temp;
                    temp=QDateTime::fromSecsSinceEpoch(date*24*3600).toString();
                    QList<QString>lst;
                    lst=temp.split(' ');
                    ui->table_borrow->setItem(i-1,0,new QTableWidgetItem(lst[4]+"年"+lst[1]+lst[2]));
                    ui->table_borrow->setItem(i-1,2,new QTableWidgetItem(query.value(0).toString()));
                    ui->table_borrow->setItem(i-1,1,new QTableWidgetItem("未归还"));
                   QString str2="select * from book where bno='"+query.value(0).toString()+"';";
                   QSqlQuery query2;
                   qDebug()<<str2;
                   bool s=query2.exec(str2);
                   while(query2.next()){
                       ui->table_borrow->setItem(i-1,3,new QTableWidgetItem(query2.value("category").toString()));
                       ui->table_borrow->setItem(i-1,4,new QTableWidgetItem(query2.value("title").toString()));
                       ui->table_borrow->setItem(i-1,5,new QTableWidgetItem(query2.value("year").toString()));
                       ui->table_borrow->setItem(i-1,6,new QTableWidgetItem(query2.value("press").toString()));
                       ui->table_borrow->setItem(i-1,7,new QTableWidgetItem(query2.value("author").toString()));
                       ui->table_borrow->setItem(i-1,8,new QTableWidgetItem(query2.value("price").toString()));
                       ui->table_borrow->setItem(i-1,9,new QTableWidgetItem(query2.value("total").toString()));
                       ui->table_borrow->setItem(i-1,10,new QTableWidgetItem(query2.value("stock").toString()));
                   }
                }

            }
         }
    }

}


void Showrecord::opendb(){
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName(database);      //连接数据库名，与设置一致
    db.setUserName(username);          //数据库用户名，与设置一致
    db.setPassword(password);    //数据库密码，与设置一致
    db.open();
}
