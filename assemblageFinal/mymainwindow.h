#ifndef MYMAINWINDOW_H
#define MYMAINWINDOW_H

#include <QMainWindow>


namespace Ui {
class myMainWindow;
}

class myMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit myMainWindow(QWidget *parent = 0);
    ~myMainWindow();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::myMainWindow *ui;


};

#endif // MYMAINWINDOW_H
