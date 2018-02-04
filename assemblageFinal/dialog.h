#ifndef DIALOG_H
#define DIALOG_H
#include "mymainwindow.h"
#include "mainwindow.h"
#include <QDialog>
#include "otherwindow.h"

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_des_clicked();

    void on_pushButton_return_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Dialog *ui;
    MainWindow *mMW;
    myMainWindow *mret;
    otherWindow *menuPict;

};

#endif // DIALOG_H
