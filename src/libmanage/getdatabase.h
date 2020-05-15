#ifndef GETDATABASE_H
#define GETDATABASE_H

#include <QDialog>

namespace Ui {
class Getdatabase;
}

class Getdatabase : public QDialog
{
    Q_OBJECT

public:
    explicit Getdatabase(QWidget *parent = nullptr);
    ~Getdatabase();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Getdatabase *ui;
};

#endif // GETDATABASE_H
