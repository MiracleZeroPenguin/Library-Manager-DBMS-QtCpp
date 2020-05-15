#include "bookborrow.h"
#include "ui_bookborrow.h"

bookborrow::bookborrow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::bookborrow)
{
    ui->setupUi(this);
}

bookborrow::~bookborrow()
{
    delete ui;
}
