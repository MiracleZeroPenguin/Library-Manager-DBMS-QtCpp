#include "mainwindow.h"
#include"getdatabase.h"
#include <QApplication>
#include <QApplication>
#include<QSqlDatabase>

#include<QDebug>
#include<QSqlError>

int main(int argc, char *argv[])
{
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", "1");
    QApplication a(argc, argv);
    MainWindow w;
    Getdatabase d;
    //login L;
    d.show();

    return a.exec();
}
