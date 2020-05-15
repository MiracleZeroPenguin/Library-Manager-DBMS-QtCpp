#include "searchbook.h"
#include "ui_searchbook.h"

Searchbook::Searchbook(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Searchbook)
{
    ui->setupUi(this);
    ui->text_price1->setValidator(new QDoubleValidator(0,10000000 , 2, this));
    ui->text_price2->setValidator(new QDoubleValidator(0,10000000 , 2, this));
    QRegExp regExp("[0-9][0-9][0-9][0-9]");//正则表达式，第一位数字为a-z的数字，第二位为1-9的数字，后边是0-2位0-9的数字
    ui->text_year1->setValidator(new QRegExpValidator(regExp,this));
    ui->text_year2->setValidator(new QRegExpValidator(regExp,this));
    connect(ui->text_category, SIGNAL(clicked()), this, SLOT(text_category_clicked()));
    connect(ui->text_title, SIGNAL(clicked()), this, SLOT(text_title_clicked()));
    connect(ui->text_press, SIGNAL(clicked()), this, SLOT(text_press_clicked()));
    connect(ui->text_year1, SIGNAL(clicked()), this, SLOT(text_year1_clicked()));
    connect(ui->text_year2, SIGNAL(clicked()), this, SLOT(text_year2_clicked()));
    connect(ui->text_author, SIGNAL(clicked()), this, SLOT(text_author_clicked()));
    connect(ui->text_price1, SIGNAL(clicked()), this, SLOT(text_price1_clicked()));
    connect(ui->text_price2, SIGNAL(clicked()), this, SLOT(text_price2_clicked()));

}

Searchbook::~Searchbook()
{
    delete ui;
}

void Searchbook::on_btn_search_clicked()
{
    QString str="SELECT * from book where ";
    bool flag,lack;
    flag=0;
    lack=1;
    if(ui->check_category->checkState()){
        qDebug()<<"规定类别";
        QString category=ui->text_category->text();
        if(category.isEmpty()){
            ui->text_category->setText("请取消勾选或输入类别");
            lack=0;
        }
        else{
            str=str+"category='"+category+"'";
            flag=1;
        }
    }
    if(ui->check_title->checkState()){
        qDebug()<<"规定书名";
        QString title=ui->text_title->text();
        if(title.isEmpty()){
            ui->text_title->setText("请取消勾选或输入类别");
            lack=0;
        }
        else{
            if(flag==1)str=str+" and title like'5"+title+"%'";
            else str=str+"title like'%"+title+"%'";
            flag=1;
        }
    }
    if(ui->check_press->checkState()){
        qDebug()<<"规定出版社";
        QString press=ui->text_press->text();
        if(press.isEmpty()){
            ui->text_press->setText("请取消勾选或输入类别");
            lack=0;
        }
        else{
            if(flag==1)str=str+" and press like'%"+press+"%'";
            else str=str+"press like'%"+press+"%'";
            flag=1;
        }
    }
    if(ui->check_year->checkState()){
        qDebug()<<"规定年份";
        QString year1=ui->text_year1->text();
        QString year2=ui->text_year2->text();
        if(year1.isEmpty()&&year1.isEmpty()){
            ui->text_year1->setText("请取消勾选或输入类别");
            ui->text_year2->setText("请取消勾选或输入类别");
            lack=0;
        }
        else if((!year1.isEmpty())&&year2.isEmpty()){
            if(flag==1)str=str+" and year>="+year1;
            else str=str+"year>="+year1;
            ui->text_year2->setText("默认无穷大");
            flag=1;
        }
        else if((!year2.isEmpty())&&year1.isEmpty()){
            if(flag==1)str=str+" and year<="+year2;
            else str=str+"year<="+year2;
            ui->text_year1->setText("默认无穷小");
            flag=1;
        }
        else{
            if(flag==1)str=str+" and year>="+year1+" and year<="+year2;
            else str=str+"year>="+year1+" and year<="+year2;
            flag=1;
        }
    }
    if(ui->check_author->checkState()){
        qDebug()<<"规定作者";
        QString author=ui->text_author->text();
        if(author.isEmpty()){
            ui->text_author->setText("请取消勾选或输入类别");
            lack=0;
        }
        else{
            if(flag==1)str=str+" and author like'%"+author+"%'";
            else str=str+"author like'%"+author+"%'";
            flag=1;
        }
    }
    if(ui->check_price->checkState()){
        qDebug()<<"规定价格";
        QString price1=ui->text_price1->text();
        QString price2=ui->text_price2->text();
        if(price1.isEmpty()&&price1.isEmpty()){
            ui->text_price1->setText("请取消勾选或输入类别");
            ui->text_price2->setText("请取消勾选或输入类别");
            lack=0;
        }
        else if((!price1.isEmpty())&&price2.isEmpty()){
            if(flag==1)str=str+" and price>="+price1;
            else str=str+"price>="+price1;
            ui->text_price2->setText("默认无穷大");
            flag=1;
        }
        else if((!price2.isEmpty())&&price1.isEmpty()){
            if(flag==1)str=str+" and price<="+price2;
            else str=str+"price<="+price2;
            ui->text_price1->setText("默认无穷小");
            flag=1;
        }
        else{
            if(flag==1)str=str+" and price>="+price1+" and year<="+price2;
            else str=str+"price>="+price1+" and price<="+price2;
            flag=1;
        }
    }
    if(!flag)str="select * from book;";

    if(lack){
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
            db.close();
       }
    }

}

void Searchbook::opendb(){
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName(database);      //连接数据库名，与设置一致
    db.setUserName(username);          //数据库用户名，与设置一致
    db.setPassword(password);    //数据库密码，与设置一致
    db.open();
}

void Searchbook::text_category_clicked()
{
    if(ui->text_category->text()=="请取消勾选或输入类别")ui->text_category->clear();
}
void Searchbook::text_title_clicked(){
    if(ui->text_title->text()=="请取消勾选或输入类别")ui->text_title->clear();
}
void Searchbook::text_press_clicked(){
    if(ui->text_press->text()=="请取消勾选或输入类别")ui->text_press->clear();
}
void Searchbook::text_year1_clicked(){
    if(ui->text_year1->text()=="请取消勾选或输入类别")ui->text_year1->clear();
}
void Searchbook::text_year2_clicked(){
    if(ui->text_year2->text()=="请取消勾选或输入类别")ui->text_year2->clear();
}
void Searchbook::text_author_clicked(){
    if(ui->text_author->text()=="请取消勾选或输入类别")ui->text_author->clear();
}
void Searchbook::text_price1_clicked(){
    if(ui->text_price1->text()=="请取消勾选或输入类别"||ui->text_price1->text()=="默认无穷大")ui->text_price1->clear();
}
void Searchbook::text_price2_clicked(){
    if(ui->text_price2->text()=="请取消勾选或输入类别"||ui->text_price2->text()=="默认无穷小")ui->text_price2->clear();
}






void Searchbook::on_check_category_clicked(bool checked)
{
    if(checked){
        ui->text_category->setEnabled(1);
    }
    else{
        ui->text_category->clear();
        ui->text_category->setEnabled(0);
    }
}

void Searchbook::on_check_title_clicked(bool checked)
{
    if(checked){
        ui->text_title->setEnabled(1);
    }
    else{
        ui->text_title->clear();
        ui->text_title->setEnabled(0);
    }
}

void Searchbook::on_check_press_clicked(bool checked)
{
    if(checked){
        ui->text_press->setEnabled(1);
    }
    else{
        ui->text_press->clear();
        ui->text_press->setEnabled(0);
    }
}

void Searchbook::on_check_year_clicked(bool checked)
{
    if(checked){
        ui->text_year1->setEnabled(1);
        ui->text_year2->setEnabled(1);
    }
    else{
        ui->text_year1->clear();
        ui->text_year2->clear();
        ui->text_year1->setEnabled(0);
        ui->text_year2->setEnabled(0);
    }
}

void Searchbook::on_check_author_clicked(bool checked)
{
    if(checked){
        ui->text_author->setEnabled(1);
    }
    else{
        ui->text_author->clear();
        ui->text_author->setEnabled(0);
    }
}


void Searchbook::on_check_price_clicked(bool checked)
{
    if(checked){
        ui->text_price1->setEnabled(1);
        ui->text_price2->setEnabled(1);
    }
    else{
        ui->text_price1->clear();
        ui->text_price2->clear();
        ui->text_price1->setEnabled(0);
        ui->text_price2->setEnabled(0);
    }
}
