#include "login.h"
#include "ui_login.h"
#include"mainwindow.h"
#include"const.h"
QString username;
QString password;
//QString database;

login::login(QWidget *parent) :
    QDialog(parent),
    uilogin(new Ui::login)
{
    uilogin->setupUi(this);
    uilogin->edit_username->clear();
    uilogin->edit_password->clear();
    uilogin->edit_password->setEchoMode(QLineEdit::Password);

}

login::~login()
{
    delete uilogin;
}

void login::on_btn1_login_clicked()
{
    //database="libmanage";
    username=uilogin->edit_username->text();
    password=uilogin->edit_password->text();
    db=QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("localhost");      //连接数据库主机名，这里需要注意（若填的为”127.0.0.1“，出现不能连接，则改为localhost)
    db.setPort(3306);                 //连接数据库端口号，与设置一致
    db.setDatabaseName(database);      //连接数据库名，与设置一致
    db.setUserName(username);          //数据库用户名，与设置一致
    db.setPassword(password);    //数据库密码，与设置一致
    db.open();
    if(!db.open()){
        uilogin->label4_logininfo->setText("用户名与密码不匹配");
        qDebug()<<"不能连接"<<"connect to mysql error"<<db.lastError().text();
        }
    else{
        uilogin->label4_logininfo->setText("登陆成功");
        qDebug()<<"连接成功"<<"connect to mysql OK";
        emit sendUsername(username);
        this->close();
        }
    db.close();
}
