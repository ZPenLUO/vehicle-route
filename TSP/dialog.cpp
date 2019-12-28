#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_Btn1_clicked()
{
    emit sendxy(ui->Xspin->value(),ui->Yspin->value());
    close();
}


void Dialog::on_Btn2_clicked()
{
    close();
}
