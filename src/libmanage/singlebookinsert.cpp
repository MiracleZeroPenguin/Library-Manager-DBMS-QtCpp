#include "singlebookinsert.h"
#include "ui_singlebookinsert.h"
#include"const.h"
#include"QString"
Singlebookinsert::Singlebookinsert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Singlebookinsert)
{
    ui->setupUi(this);

    QRegExp regExp("[0-9][0-9][0-9][0-9]");//正则表达式，第一位数字为a-z的数字，第二位为1-9的数字，后边是0-2位0-9的数字
    ui->text_year->setValidator(new QRegExpValidator(regExp,this));
    ui->text_price->setValidator(new QDoubleValidator(0,10000000 , 2, this));
    //ui->text_year->setValidator(new QIntValidator(0, 4, this));
    ui->text_total->setValidator(new QIntValidator(0, 10000000, this));
}

Singlebookinsert::~Singlebookinsert()
{
    delete ui;
}

void Singlebookinsert::on_btn_insert_clicked()
{
    opendb();

    QString str="select * from book;";

    qDebug()<<str;
    str=str+";";
    opendb();
    QSqlQuery query(db);
   bool success=query.exec(str);
   if(success) qDebug()<<"查书成功";
   int i=0;

   while(query.next()){
        i=i+1;
        ui->table_bookinfo->setRowCount(i);

        ui->table_bookinfo->setItem(i-1,0,new QTableWidgetItem(query.value("bno").toString()));
        ui->table_bookinfo->setItem(i-1,1,new QTableWidgetItem(query.value("category").toString()));
        ui->table_bookinfo->setItem(i-1,2,new QTableWidgetItem(query.value("title").toString()));
        ui->table_bookinfo->setItem(i-1,3,new QTableWidgetItem(query.value("press").toString()));
        ui->table_bookinfo->setItem(i-1,4,new QTableWidgetItem(query.value("year").toString()));
        ui->table_bookinfo->setItem(i-1,5,new QTableWidgetItem(query.value("author").toString()));
        ui->table_bookinfo->setItem(i-1,6,new QTableWidgetItem(query.value("price").toString()));
        ui->table_bookinfo->setItem(i-1,7,new QTableWidgetItem(query.value("total").toString()));
        ui->table_bookinfo->setItem(i-1,8,new QTableWidgetItem(query.value("stock").toString()));
        if(ui->text_bno->text()==query.value("bno").toString()){
            for(int m=0;m<=8;m++){
                ui->table_bookinfo->item(i-1, m)->setForeground(Qt::red);
                ui->table_bookinfo->item(i-1,m)->setBackground(Qt::yellow);
            }
        }
   }

    if(!db.open()){
        qDebug()<<"不能连接createuser"<<"connect to mysql error";
        }
    else{
        qDebug()<<"连接成功createuser"<<"connect to mysql OK";

        QString bno,category,title,press,year,author,price,total,stock;

        bno="'"+ui->text_bno->text()+"'";
        if(bno=="''"){ui->label_insertinfo->setText("请输入书号");bno="null";}
        category="'"+ui->text_category->text()+"'";
        if(category=="''")category="null";
        title="'"+ui->text_title->text()+"'";
        if(title=="''")title="null";
        press="'"+ui->text_press->text()+"'";
        if(press=="''")press="null";
        year="'"+ui->text_year->text()+"'";
        if(year=="''")year="null";
        author="'"+ui->text_author->text()+"'";
        if(author=="''")author="null";
        price="'"+ui->text_price->text()+"'";
        if(price=="''")price="null";
        total="'"+ui->text_total->text()+"'";
        if(total=="''")total="null";
        stock="'"+ui->text_stock_2->text()+"'";
        if(stock=="''")stock=total;
        else if(ui->text_stock_2->text().toInt()>ui->text_total->text().toInt()){
            ui->text_stock_2->setText("库存需小于总藏书量，否则库存设置为空");
            stock="null";
        }


        QSqlQueryModel querym;
        QString str1;
        str1="INSERT INTO book VALUES("+bno+","+category+","+title+","+press+","+year+","+author+","+price+","+total+","+stock+");";
        qDebug()<<str1;

        querym.setQuery(str1);


        if(!querym.lastError().isValid()){
            qDebug()<<"插入新书成功";
            ui->label_insertinfo->setText("插入图书"+ui->text_bno->text()+ui->text_title->text()+"成功");

            query.exec(str);

            int i=0;

            while(query.next()){
                 i=i+1;
                 ui->table_new->setRowCount(i);

                 ui->table_new->setItem(i-1,0,new QTableWidgetItem(query.value("bno").toString()));
                 ui->table_new->setItem(i-1,1,new QTableWidgetItem(query.value("category").toString()));
                 ui->table_new->setItem(i-1,2,new QTableWidgetItem(query.value("title").toString()));
                 ui->table_new->setItem(i-1,3,new QTableWidgetItem(query.value("press").toString()));
                 ui->table_new->setItem(i-1,4,new QTableWidgetItem(query.value("year").toString()));
                 ui->table_new->setItem(i-1,5,new QTableWidgetItem(query.value("author").toString()));
                 ui->table_new->setItem(i-1,6,new QTableWidgetItem(query.value("price").toString()));
                 ui->table_new->setItem(i-1,7,new QTableWidgetItem(query.value("total").toString()));
                 ui->table_new->setItem(i-1,8,new QTableWidgetItem(query.value("stock").toString()));
                 if(bno=="'"+query.value("bno").toString()+"'"){
                     for(int m=0;m<=8;m++){
                         ui->table_new->item(i-1, m)->setForeground(Qt::red);
                         ui->table_new->item(i-1,m)->setBackground(Qt::yellow);
                     }
                 }

            }
        }
        else{
            QString error=querym.lastError().text();
            error=error.mid(0,3);
            qDebug()<<error;
            if(error=="Dup"){
                qDebug()<<"更新信息";
                QSqlQuery query2;
                QString str2,str0;
                str0=" WHERE bno="+bno+";";
                bool successupdate=1;
                if(category!="null"){
                    str2="UPDATE book SET category="+category+str0;
                    qDebug()<<str2;
                    successupdate=successupdate*query2.exec(str2);
                }
                if(title!="null"){
                    str2="UPDATE book SET title="+title+str0;
                    qDebug()<<str2;
                    successupdate=successupdate*query2.exec(str2);
                }
                if(press!="null"){
                    str2="UPDATE book SET press="+press+str0;
                    qDebug()<<str2;
                    successupdate=successupdate*query2.exec(str2);
                }
                if(year!="null"){
                    str2="UPDATE book SET year="+year+str0;
                    qDebug()<<str2;
                    successupdate=successupdate*query2.exec(str2);
                }
                if(author!="null"){
                    str2="UPDATE book SET author="+author+str0;
                    qDebug()<<str2;
                    successupdate=successupdate*query2.exec(str2);
                }
                if(price!="null"){
                    str2="UPDATE book SET price="+price+str0;
                    qDebug()<<str2;
                    successupdate=successupdate*query2.exec(str2);
                }
                if(total!="null"){
                    str2="UPDATE book SET total="+total+str0;
                    qDebug()<<str2;
                    successupdate=successupdate*query2.exec(str2);
                }
                if(stock!="null"){
                    str2="UPDATE book SET stock="+stock+str0;
                    qDebug()<<str2;
                    successupdate=successupdate*query2.exec(str2);
                }

                if(successupdate)ui->label_insertinfo->setText("更新信息"+ui->text_bno->text()+"成功");
                else ui->label_insertinfo->setText("更新信息"+ui->text_bno->text()+"失败");

                //***************
               query.exec(str);

               int i=0;

               while(query.next()){
                    i=i+1;
                    ui->table_new->setRowCount(i);

                    ui->table_new->setItem(i-1,0,new QTableWidgetItem(query.value("bno").toString()));
                    ui->table_new->setItem(i-1,1,new QTableWidgetItem(query.value("category").toString()));
                    ui->table_new->setItem(i-1,2,new QTableWidgetItem(query.value("title").toString()));
                    ui->table_new->setItem(i-1,3,new QTableWidgetItem(query.value("press").toString()));
                    ui->table_new->setItem(i-1,4,new QTableWidgetItem(query.value("year").toString()));
                    ui->table_new->setItem(i-1,5,new QTableWidgetItem(query.value("author").toString()));
                    ui->table_new->setItem(i-1,6,new QTableWidgetItem(query.value("price").toString()));
                    ui->table_new->setItem(i-1,7,new QTableWidgetItem(query.value("total").toString()));
                    ui->table_new->setItem(i-1,8,new QTableWidgetItem(query.value("stock").toString()));
                    if(bno=="'"+query.value("bno").toString()+"'"){
                        for(int m=0;m<=8;m++){
                            ui->table_new->item(i-1, m)->setForeground(Qt::red);
                            ui->table_new->item(i-1,m)->setBackground(Qt::yellow);
                        }
                    }

               }



            }
            else{
                qDebug()<<"插入图书失败";
                ui->label_insertinfo->setText("插入图书"+ui->text_bno->text()+ui->text_title->text()+"失败");
            }

        }
        db.close();
    }
}


void Singlebookinsert::opendb(){
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName(database);      //连接数据库名，与设置一致
    db.setUserName(username);          //数据库用户名，与设置一致
    db.setPassword(password);    //数据库密码，与设置一致
    db.open();
}
