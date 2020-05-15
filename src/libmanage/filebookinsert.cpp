#include "filebookinsert.h"
#include "ui_filebookinsert.h"
#include"QString"
#include"QSqlQueryModel"
Filebookinsert::Filebookinsert(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Filebookinsert)
{
    ui->setupUi(this);
}

Filebookinsert::~Filebookinsert()
{
    delete ui;
}

void Filebookinsert::on_pushButton_clicked()
{

    filename=QFileDialog::getOpenFileName(this,tr("选择文件"),"D:\\",tr("*.txt"));
    if(!filename.isEmpty()){
        ui->text_filename->setText(filename);
    }
}

void Filebookinsert::opendb(){
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName(database);      //连接数据库名，与设置一致
    db.setUserName(username);          //数据库用户名，与设置一致
    db.setPassword(password);    //数据库密码，与设置一致
    db.open();

}

void Filebookinsert::on_pushButton_2_clicked()
{
    opendb();

    //ui->table_new->setHorizontalHeaderLabels(strs);
    //ui->table_old->setHorizontalHeaderLabels(strs);

    if(!filename.isEmpty()){
        //ui->text_filename->setText(filename);
        QFile file(filename);
        file.open(QIODevice::ReadOnly);

        if(file.isOpen()){
            qDebug()<<"文件加载成功";
            QTextStream in(&file);
            in.setCodec("UTF-8");
            QString line=in.readLine();
            int x=0;
            ui->table_bookinfo->setColumnCount(9);

            QString str1="select * from book;";

            qDebug()<<str1;

            //************************
            QSqlQuery queryold(db);
           queryold.exec(str1);

           int i=0;
             ui->table_old->setColumnCount(9);
           QStringList strsold = {"bno","category","title","press","year","author","price","total","stock"};
           ui->table_old->setHorizontalHeaderLabels(strsold);

           while(queryold.next()){
                i=i+1;
                ui->table_old->setRowCount(i);
                ui->table_old->setItem(i-1,0,new QTableWidgetItem(queryold.value("bno").toString()));
                ui->table_old->setItem(i-1,1,new QTableWidgetItem(queryold.value("category").toString()));
                ui->table_old->setItem(i-1,2,new QTableWidgetItem(queryold.value("title").toString()));
                ui->table_old->setItem(i-1,3,new QTableWidgetItem(queryold.value("press").toString()));
                ui->table_old->setItem(i-1,4,new QTableWidgetItem(queryold.value("year").toString()));
                ui->table_old->setItem(i-1,5,new QTableWidgetItem(queryold.value("author").toString()));
                ui->table_old->setItem(i-1,6,new QTableWidgetItem(queryold.value("price").toString()));
                ui->table_old->setItem(i-1,7,new QTableWidgetItem(queryold.value("total").toString()));
                ui->table_old->setItem(i-1,8,new QTableWidgetItem(queryold.value("stock").toString()));
           }
            //*************************************
            while(!line.isNull()){
                x=x+1;
                qDebug()<<line;
                QList<QString>lst;
                //line.remove(QChar('('), Qt::CaseInsensitive);
                line=line.mid(1,line.length()-2);
                lst=line.split(',');
                for(int i=0;i<lst.count();i++)
                   {
                       lst[i]=lst[i].simplified();
                       lst[i]="'"+lst[i]+"'";
                       qDebug()<<"lst["<<i<<"]"<<lst[i];
                   }

                QString str="INSERT INTO book VALUES("+lst[0]+","+lst[1]+","+lst[2]+","+lst[3]+","+lst[4]+","+lst[5]+","+lst[6]+","+lst[7]+","+lst[7]+");";
                qDebug()<<str;
                QSqlQueryModel query;
                query.setQuery(str);

                if (query.lastError().isValid()){

                    QString error=query.lastError().text();
                    qDebug() << error;
                    QString error_sim=error.mid(0,3);
                    //x=x+1;
                    QStringList strs = {"tips","bno","category","title","press","year","author","price","total"};
                    ui->table_bookinfo->setHorizontalHeaderLabels(strs);
                    ui->table_bookinfo->setRowCount(x);
                    for(int j=0;j<=7;j++){
                        lst[j]=lst[j].mid(1,lst[j].length()-2);
                        ui->table_bookinfo->setItem(x-1,j+1,new QTableWidgetItem(lst[j]));
                    }
                    if(error_sim!="Dup"){
                        ui->table_bookinfo->setItem(x-1,0,new QTableWidgetItem(error));
                    }
                    else{
                        ui->table_bookinfo->setItem(x-1,0,new QTableWidgetItem("更新信息"));

                        //****************更新*****************************
                        qDebug()<<"更新信息";
                        QSqlQuery query2;
                        QString str2,str0;

                        str0=" WHERE bno='"+lst[0]+"';";
                        bool successupdate=1;
                        if(!lst[1].isEmpty()){
                            str2="UPDATE book SET category='"+lst[1]+"'"+str0;
                            qDebug()<<str2;
                            successupdate=successupdate*query2.exec(str2);
                        }
                        if(!lst[2].isEmpty()){
                            str2="UPDATE book SET title='"+lst[2]+"'"+str0;
                            qDebug()<<str2;
                            successupdate=successupdate*query2.exec(str2);
                        }
                        if(!lst[3].isEmpty()){
                            str2="UPDATE book SET press='"+lst[3]+"'"+str0;
                            qDebug()<<str2;
                            successupdate=successupdate*query2.exec(str2);
                        }
                        if(!lst[4].isEmpty()){
                            str2="UPDATE book SET year='"+lst[4]+"'"+str0;
                            qDebug()<<str2;
                            successupdate=successupdate*query2.exec(str2);
                        }
                        if(!lst[5].isEmpty()){
                            str2="UPDATE book SET author='"+lst[5]+"'"+str0;
                            qDebug()<<str2;
                            successupdate=successupdate*query2.exec(str2);
                        }
                        if(!lst[6].isEmpty()){
                            str2="UPDATE book SET price='"+lst[6]+"'"+str0;
                            qDebug()<<str2;
                            successupdate=successupdate*query2.exec(str2);
                        }
                        if(!lst[7].isEmpty()){
                            str2="UPDATE book SET total='"+lst[7]+"'"+str0;
                            qDebug()<<str2;
                            successupdate=successupdate*query2.exec(str2);
                            str2="UPDATE book SET stock='"+lst[7]+"'"+str0;
                            qDebug()<<str2;
                            successupdate=successupdate*query2.exec(str2);
                        }
                        if(successupdate)qDebug()<<"更新成功&&&&&&&&&&&&&&&&&";

                    }
                }
                else {
                    qDebug() << "成功插入图书"<<lst[0];
                    //x=x+1;
                    ui->table_bookinfo->setRowCount(x);
                    for(int j=0;j<=7;j++){
                        lst[j]=lst[j].mid(1,lst[j].length()-2);
                        ui->table_bookinfo->setItem(x-1,j+1,new QTableWidgetItem(lst[j]));
                    }
                    ui->table_bookinfo->setItem(x-1,0,new QTableWidgetItem("成功导入"));
                    //ui->table_bookinfo->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
                }
                line=in.readLine();
            }
        }

        //************************
        QSqlQuery querynew(db);
        QString strnew="select * from book;";
       querynew.exec(strnew);

       int i=0;
         ui->table_new->setColumnCount(9);
       QStringList strsnew = {"bno","category","title","press","year","author","price","total","stock"};
       ui->table_new->setHorizontalHeaderLabels(strsnew);

       while(querynew.next()){
            i=i+1;
            ui->table_new->setRowCount(i);
            ui->table_new->setItem(i-1,0,new QTableWidgetItem(querynew.value("bno").toString()));
            ui->table_new->setItem(i-1,1,new QTableWidgetItem(querynew.value("category").toString()));
            ui->table_new->setItem(i-1,2,new QTableWidgetItem(querynew.value("title").toString()));
            ui->table_new->setItem(i-1,3,new QTableWidgetItem(querynew.value("press").toString()));
            ui->table_new->setItem(i-1,4,new QTableWidgetItem(querynew.value("year").toString()));
            ui->table_new->setItem(i-1,5,new QTableWidgetItem(querynew.value("author").toString()));
            ui->table_new->setItem(i-1,6,new QTableWidgetItem(querynew.value("price").toString()));
            ui->table_new->setItem(i-1,7,new QTableWidgetItem(querynew.value("total").toString()));
            ui->table_new->setItem(i-1,8,new QTableWidgetItem(querynew.value("stock").toString()));
       }
        //*************************************
        db.close();
    }
    else{
        ui->text_filename->setText("文件导入失败");
    }
}
