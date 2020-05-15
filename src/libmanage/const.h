#ifndef CONST_H
#define CONST_H
#include<QSqlDatabase>
extern QString username;
extern QString password;
extern QString database;
QSqlDatabase opendb();
#endif // CONST_H
