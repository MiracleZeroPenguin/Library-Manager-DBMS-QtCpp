#include "searchuser.h"
#include "ui_searchuser.h"
#include"const.h"
Searchuser::Searchuser(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Searchuser)
{
    ui->setupUi(this);
    show_table();
}

Searchuser::~Searchuser()
{
    delete ui;
}

void Searchuser::show_table(){
    opendb();
    if(db.open()){
        qDebug()<<"连接成功Searchuser";
        QSqlQuery query(db);
       bool success=query.exec("SELECT User, Host,password_last_changed FROM mysql.user;");
       if(success) qDebug()<<"用户寻找成功";
       int i=0;
       ui->table_users->setColumnCount(3);
       QStringList strs = {"Username","Host","Create time"};
       ui->table_users->setHorizontalHeaderLabels(strs);
       while(query.next()){
            i=i+1;
            ui->table_users->setRowCount(i);
            QString user=query.value("User").toString();
            QString host=query.value("Host").toString();
            QString time=query.value("password_last_changed").toString();
            ui->table_users->setItem(i-1,0,new QTableWidgetItem(user));
            ui->table_users->setItem(i-1,1,new QTableWidgetItem(host));
            ui->table_users->setItem(i-1,2,new QTableWidgetItem(time));

        }
       ui->table_users->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
       db.close();
    }
    else qDebug()<<"连接失败Searchuser";
}

void Searchuser::opendb(){
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName(database);      //连接数据库名，与设置一致
    db.setUserName(username);          //数据库用户名，与设置一致
    db.setPassword(password);    //数据库密码，与设置一致
    db.open();
}

void Searchuser::on_pushButton_clicked()
{
    opendb();
    if(db.open()){
        qDebug()<<"连接成功Searchuser_sp";
        QSqlQuery query(db);
        QString name;
        name=ui->text_username->text();
       bool success=query.exec("SELECT EXISTS(SELECT 1 FROM mysql.user WHERE user = '"+name+"')as ans");
       int exit=0;
       if(query.next())
            exit=query.value("ans").toInt();
       if(exit==1){
           qDebug()<<"用户存在";
           ui->label_result->setText("用户"+name+"存在");
       }
       else{
           qDebug()<<"用户不存在";
           ui->label_result->setText("用户"+name+"不存在");
       }
       db.close();
    }
    else qDebug()<<"连接失败Searchuser_sp";
}

