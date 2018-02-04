#include "dialog.h"
#include "ui_dialog.h"
#include "mainwindow.h"
#include "mymainwindow.h"
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

void Dialog::on_pushButton_des_clicked()
{

    mMW = new MainWindow(this);
    mMW->show();



}

void Dialog::on_pushButton_return_clicked()
{


    mret = new myMainWindow(this);
    mret->show();


}

void Dialog::on_pushButton_2_clicked()
{
    menuPict = new otherWindow(this);
    menuPict->show();

}
