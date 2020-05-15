#include "searchcard.h"
#include "ui_searchcard.h"

Searchcard::Searchcard(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Searchcard)
{
    ui->setupUi(this);
    ui->table_card->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

Searchcard::~Searchcard()
{
    delete ui;
}

void Searchcard::on_check_cno_clicked(bool checked)
{
    if(checked){
        ui->text_cno->setEnabled(1);
    }
    else{
        ui->text_cno->setEnabled(0);
        ui->text_cno->clear();
    }
}

void Searchcard::on_check_name_clicked(bool checked)
{
    if(checked){
        ui->text_name->setEnabled(1);
    }
    else{
        ui->text_name->setEnabled(0);
        ui->text_name->clear();
    }
}


void Searchcard::on_check_department_clicked(bool checked)
{
    if(checked){
        ui->text_department->setEnabled(1);
    }
    else{
        ui->text_department->setEnabled(0);
        ui->text_department->clear();
    }
}

void Searchcard::on_check_type_clicked(bool checked)
{
    if(checked){
        ui->box_type->setEnabled(1);
    }
    else{
        ui->box_type->setEnabled(0);
        ui->box_type->setCurrentIndex(0);
    }
}

void Searchcard::on_btn_search_clicked()
{
    ui->table_card->clearContents();
    opendb();
    QString cno,name,dep,type,str;
    bool flag=0;
    cno=ui->text_cno->text();
    name=ui->text_name->text();
    dep=ui->text_department->text();
    if(ui->box_type->currentIndex()==1){
        type="T";
    }
    else if(ui->box_type->currentIndex()==2){
        type="S";
    }
    else{
        type.clear();
    }
    str="select * from card where ";
    if(!cno.isEmpty()){
        str=str+"cno='"+cno+"' ";
        flag=1;
    }
    if(!name.isEmpty()){
        if(flag){
            str=str+"and name='"+name+"' ";
        }
        else{
            flag=1;
            str=str+"name='"+name+"' ";
        }
    }
    if(!dep.isEmpty()){
        if(flag){
            str=str+"and department='"+dep+"' ";
        }
        else{
            flag=1;
            str=str+"department='"+dep+"' ";
        }
    }
    if(!type.isEmpty()){
        if(flag){
            str=str+"and type='"+type+"' ";
        }
        else{
            flag=1;
            str=str+"type='"+type+"' ";
        }
    }
    if(!flag){
        str="select * from card;";
    }
    else{
        str=str+";";
    }

    QSqlQuery query(db);
    qDebug()<<str;
    bool success=query.exec(str);
    if(!success)qDebug()<<"查询失败";
    else{
        if(!query.next()){
            ui->table_card->setRowCount(0);
            ui->label_exist->setText("不存在符合条件的借书证");
        }
        else{
            ui->label_exist->clear();
            int i=0;
            do{
                 i=i+1;
                 ui->table_card->setRowCount(i);

                 ui->table_card->setItem(i-1,0,new QTableWidgetItem(query.value("cno").toString()));
                 ui->table_card->setItem(i-1,1,new QTableWidgetItem(query.value("name").toString()));
                 ui->table_card->setItem(i-1,2,new QTableWidgetItem(query.value("department").toString()));
                 QString t;
                 if(query.value("type").toString()=="T")t="教师";
                 else if(query.value("type").toString()=="S")t="学生";
                 else t.clear();
                 ui->table_card->setItem(i-1,3,new QTableWidgetItem(t));

            }while(query.next());
        }
    }
}



void Searchcard::opendb(){
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName(database);      //连接数据库名，与设置一致
    db.setUserName(username);          //数据库用户名，与设置一致
    db.setPassword(password);    //数据库密码，与设置一致
    db.open();

}
