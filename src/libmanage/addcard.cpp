#include "addcard.h"
#include "ui_addcard.h"

Addcard::Addcard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Addcard)
{
    ui->setupUi(this);
}

Addcard::~Addcard()
{
    delete ui;
}

void Addcard::on_pushButton_clicked()
{
    opendb();
    if(!db.isOpen()){
        qDebug()<<"数据库连接失败";
    }
    else{
        QString cno,name,department,type;
        cno=ui->text_cno->text();
        if(cno.isEmpty()){
            ui->label_info->setText("必须输入卡号");
        }
        else{
            name=ui->text_name->text();
            department=ui->text_department->text();
            if(ui->box_type->currentIndex()==1){
                type="T";
            }
            else if(ui->box_type->currentIndex()==2){
                type="S";
            }
            else{
                type="";
            }
            //****************查询是否已经存在该借书证**********
            QString str1="select * from card where cno='"+cno+"';";
            qDebug()<<str1;
            QSqlQuery query1;
            query1.exec(str1);
            if(query1.next()){
                qDebug()<<"存在该卡号";
                ui->label_info->setText("已经存在卡号"+cno);
            }
            //**************新建借书证***********
            else{
                str1="insert into card values('"+cno+"'";
                if(!name.isEmpty()){
                    str1=str1+",'"+name+"'";
                }
                else{
                    qDebug()<<"未设置姓名";
                    str1=str1+",null";
                }
                if(!department.isEmpty()){
                    str1=str1+",'"+department+"'";
                }
                else{
                    qDebug()<<"未设置部门";
                    str1=str1+",null";
                }
                if(!type.isEmpty()){
                    str1=str1+",'"+type+"'";
                }
                else{
                    qDebug()<<"未设置类别";
                    str1=str1+",null";
                }
                str1=str1+");";
                qDebug()<<str1;
                bool success2=query1.exec(str1);
                if(success2){
                    qDebug()<<"新建借书证成功";
                    ui->label_info->setText("新建借书证"+cno+"成功");
                }
                else {
                    qDebug()<<"新建借书证失败";
                    QString error=query1.lastError().text();
                    ui->label_info->setText(error);
                }
            }
        }
        db.close();
    }
}

void Addcard::opendb(){
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName(database);      //连接数据库名，与设置一致
    db.setUserName(username);          //数据库用户名，与设置一致
    db.setPassword(password);    //数据库密码，与设置一致
    db.open();
}
