#ifndef OTHERWINDOW_H
#define OTHERWINDOW_H

#include <QMainWindow>
#include "opencv2/imgcodecs.hpp"
#include <qfiledialog.h>

namespace Ui {
class otherWindow;
}

class otherWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit otherWindow(QWidget *parent = 0);
    ~otherWindow();

    void EnvLoginIm(std::string l,std::string p );
private slots:
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void BC(std::string path);
    void Detection_Contours_canny(std::string path );
    void affiche_label_1 (cv::Mat source);
    void affiche_label_2 (cv::Mat resultat);
    void histogram (std::string path);
    void moyenneur_cv(std::string path);
    void Appliquer_seuillage(std::string path);
    cv::Mat filtrelaplacien(cv::Mat src, cv::Mat dst, float Filtre[][3]);
    void  Laplacien_opencv(std::string path);
    void Appliquer_F_Laplacien_Man(std::string path);
    void Filtre_Sobel(std::string path);
    void on_pushButton_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_6_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_commandLinkButton_clicked();


private:
    Ui::otherWindow *ui;
};

#endif // OTHERWINDOW_H
