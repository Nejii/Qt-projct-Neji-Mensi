#include "mymainwindow.h"
#include "ui_mymainwindow.h"
#include "mainwindow.h"
#include "otherwindow.h"
#include "dialog.h"
#include <QMessageBox>

myMainWindow::myMainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::myMainWindow)
{
    ui->setupUi(this);
}

myMainWindow::~myMainWindow()
{
    delete ui;
}

void myMainWindow::on_buttonBox_accepted()
{
    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_2_password->text();
    if((login != "user_1" && login != "root") || ( password != "user_1" && password != "root"))
    {
        QMessageBox::information(this,"buttonBox" ,"Mot de passe erroné");
    }
    else if ((login=="root" && password =="root")||(login=="user_1" && password =="user_1"))
    {

        MainWindow w;
        otherWindow ow;
        string l= login.toStdString();
        string p= login.toStdString();

        w.EnvLogin(l,p);
        ow.EnvLoginIm(l,p);
        //w.show();
        hide();

        // mchoixdiag = new ChoixDialog(this);
        //  mchoixdiag->show();

        Dialog mImgdiag;
        mImgdiag.setModal(true);
        mImgdiag.exec();
    }
}

void myMainWindow::on_buttonBox_rejected()
{
    close();
}
