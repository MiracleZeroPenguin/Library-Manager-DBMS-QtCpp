#include "updatecard.h"
#include "ui_updatecard.h"

Updatecard::Updatecard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Updatecard)
{
    ui->setupUi(this);
}

Updatecard::~Updatecard()
{
    delete ui;
}

void Updatecard::on_btn_check_clicked()
{
    if(ui->label_check->text()=="√"){
        ui->btn_check->setText("Check");
        ui->label_check->clear();
        ui->text_cno->setEnabled(1);
        ui->check_name->setEnabled(0);
        ui->check_type->setEnabled(0);
        ui->check_department->setEnabled(0);
        ui->btn_update->setEnabled(0);
        ui->text_name->clear();
        ui->text_department->clear();
        ui->box_type->setCurrentIndex(0);
        ui->text_name->setEnabled(0);
        ui->text_department->setEnabled(0);
        ui->check_name->setChecked(0);
        ui->check_department->setChecked(0);
        ui->check_type->setChecked(0);
        ui->update_name->clear();
        ui->update_type->clear();
        ui->update_department->clear();
    }
    else{
        opendb();
        if(!db.isOpen()){
            qDebug()<<"数据库连接失败";
        }
        else{
            qDebug()<<"数据库连接成功";
            QString cno;
            cno=ui->text_cno->text();
            if(cno.isEmpty()){
                ui->label_check->setText("×");
            }
            else{
                //****************查询是否已经存在该借书证**********

                QString str1="select * from card where cno='"+cno+"';";
                qDebug()<<str1;
                QSqlQuery query2(db);
                query2.exec(str1);
                if(!query2.next()){
                    qDebug()<<"不存在该卡号";
                    ui->label_check->setText("×");
                    QPalette pa;
                    pa.setColor(QPalette::WindowText,Qt::red);
                    ui->label_check->setPalette(pa);
                    ui->check_name->setEnabled(0);
                    ui->check_type->setEnabled(0);
                    ui->check_department->setEnabled(0);
                    ui->btn_update->setEnabled(0);
                }
                else{
                    qDebug()<<"存在该卡号";
                    ui->label_check->setText("√");
                    ui->btn_check->setText("Clear");
                    QPalette pa;
                    pa.setColor(QPalette::WindowText,Qt::green);
                    ui->label_check->setPalette(pa);
                    ui->check_name->setEnabled(1);
                    ui->check_type->setEnabled(1);
                    ui->check_department->setEnabled(1);
                    ui->text_cno->setEnabled(0);
                    ui->btn_update->setEnabled(1);
                }
            }
            db.close();
        }
    }
}

void Updatecard::opendb(){
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName(database);      //连接数据库名，与设置一致
    db.setUserName(username);          //数据库用户名，与设置一致
    db.setPassword(password);    //数据库密码，与设置一致
    db.open();
}

void Updatecard::on_check_name_clicked(bool checked)
{
    if(checked){
        ui->text_name->setEnabled(1);
    }
    else{
        ui->text_name->clear();
        ui->text_name->setEnabled(0);
    }
}

void Updatecard::on_check_department_clicked(bool checked)
{
    if(checked){
        qDebug()<<"check";
        ui->text_department->setEnabled(1);
    }
    else{
        ui->text_department->setEnabled(0);
        ui->text_department->clear();

    }
}

void Updatecard::on_check_type_clicked(bool checked)
{
    if(checked){
        ui->box_type->setEnabled(1);
    }
    else{
        ui->box_type->setCurrentIndex(0);
        ui->box_type->setEnabled(0);
    }
}

void Updatecard::on_btn_update_clicked()
{
    opendb();
    //**********更新借书证*********
    QSqlQuery query(db);
    QPalette pa;
    QString str1="update card set ";
    QString str2=" where cno='"+ui->text_cno->text()+"';";

    if(ui->check_name->isChecked()){
            QString str;
            bool success;
            if(ui->text_name->text().isEmpty()){
                str1=str1+"name=null";
            }
            else{
                str1=str1+"name='"+ui->text_name->text()+"'";
            }
            str=str1+str2;
            qDebug()<<str;
            success=query.exec(str);
            if(success){
                qDebug()<<"更新姓名成功";
                ui->update_name->setText("√");
                pa.setColor(QPalette::WindowText,Qt::green);
                ui->update_name->setPalette(pa);
            }
            else{
                qDebug()<<"更新姓名失败";
                ui->update_name->setText("×");
                pa.setColor(QPalette::WindowText,Qt::red);
                ui->update_name->setPalette(pa);
            }
        }
    if(ui->check_department->isChecked()){
        str1="update card set ";
            bool success;
            QString str;
            if(ui->text_department->text().isEmpty()){
                str1=str1+"department=null";
            }
            else{
                str1=str1+"department='"+ui->text_name->text()+"'";
            }
            str=str1+str2;
            qDebug()<<str;
            success=query.exec(str);
            if(success){
                qDebug()<<"更新姓名成功";
                ui->update_department->setText("√");
                pa.setColor(QPalette::WindowText,Qt::green);
                ui->update_department->setPalette(pa);
            }
            else{
                qDebug()<<"更新姓名失败";
                ui->update_department->setText("×");
                pa.setColor(QPalette::WindowText,Qt::red);
                ui->update_department->setPalette(pa);
            }
        }
    if(ui->check_type->isChecked()){
        str1="update card set ";
            bool success;
            QString str;

            if(ui->box_type->currentIndex()==0){
                str1=str1+"type=null";
            }
            else{
                QString temptype;
                if(ui->box_type->currentIndex()==1)temptype="T";
                else temptype="S";
                str1=str1+"type='"+temptype+"'";
            }
            str=str1+str2;

            query.exec(str);
            if(!query.lastError().isValid()){
                qDebug()<<"更新类型成功";
                ui->update_type->setText("√");
                pa.setColor(QPalette::WindowText,Qt::green);
                ui->update_type->setPalette(pa);
            }
            else{
                qDebug()<<"更新类型失败";
                ui->update_type->setText("×");
                pa.setColor(QPalette::WindowText,Qt::red);
                ui->update_type->setPalette(pa);
            }
    }
}
