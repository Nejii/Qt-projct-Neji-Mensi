#include "otherwindow.h"
#include "ui_otherwindow.h"
#include "dialog.h"

#include<opencv2/opencv.hpp>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string>
#include <fstream>
#include <cstdlib>
#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/imgproc.hpp"
#include "opencv2/core/utility.hpp"
#include "opencv2/highgui/highgui_c.h"
#include "QLabel"

void  Detection_Contours_canny(std::string path );
QImage MatVersQImage(cv::Mat m);
void thresh_callback(int, void* );
void affiche_label_1 (cv::Mat source);
void affiche_label_2 (cv::Mat resultat);
void moyenneur_cv(std::string path);
void Appliquer_seuillage(std::string path);
void BC(cv::Mat src );
void histogram (std::string path);
void EnvlIm(string l,string p );
using namespace cv ;
using namespace std ;

string l, pass;
void otherWindow::EnvLoginIm(string l,string p )
{
    l=l;
    pass=p;
}

Mat src; Mat src_gray;
int thresh = 100;
int max_thresh = 255;
RNG rng(12345);

QImage MatVersQImage(Mat m)
{   QImage image1((unsigned char*) m.data, m.size().width, m.size().height, m.step, QImage::Format_RGB888);
    QImage image= image1.rgbSwapped().convertToFormat(QImage::Format_ARGB32_Premultiplied);
    return image;
}

void otherWindow::Detection_Contours_canny(string path )
{
    Mat src; Mat src_niv_gris;
    int seuil_min;
    int const max_seuil_min = 100;
    int taux = 3;
    Mat dst, contours_trouvé;
    src = imread(path);
    QWidget CB; // création de la nouvelle fenêtre pour le trackbar
    CB.resize(120 ,120);
    CB.setWindowTitle(
                QApplication::translate("Seuil Canny", "Seuil Canny"));
    imshow("Seuil Canny",src);
    createTrackbar( " Seuil Canny:", "Seuil Canny",&seuil_min, max_seuil_min );
    cvtColor( src, src_niv_gris, CV_BGR2GRAY );

    while (true)
    {
        dst.create( src.size(), src.type() );
        Canny( src_niv_gris, contours_trouvé, seuil_min, seuil_min*taux, 3 );//3 : taille de noyau Sobel à utiliser en arrière plan

        dst = Scalar::all(0);
        src.copyTo( dst, contours_trouvé);

        affiche_label_1 (src);
        affiche_label_2(dst);
       int iKey = waitKey(50);

        if (iKey ==27)
        {
            break;
        }
    }

}

void otherWindow::BC(string path)
{
    Mat src = imread(path);
    if (!src.data)
    {
        cout << "Erreur lors de chargement de l'image" << endl;

    }

    QWidget CB;
    CB.resize(150 ,150);
    CB.setWindowTitle(
                QApplication::translate("m", "BC"));


    imshow("BC",src);

    int Brillance = 50;
    createTrackbar("Brillance", "BC", &Brillance, 100);


    int contraste = 50;
    createTrackbar("contraste", "BC", &contraste, 100);

    while (true)
    {
        Mat dst;
        int nouv_Brillance  = Brillance - 50;
        double nouv_contraste = contraste / 50;
        src.convertTo(dst, -1, nouv_contraste, nouv_Brillance);
        affiche_label_1 (src);
        affiche_label_2(dst);

        int iKey = waitKey(50);


        if (iKey == 27)
        {
            break;
        }
    }

}
void otherWindow::affiche_label_1 (Mat source)
{   QImage image;

    image =MatVersQImage( source).scaledToWidth(ui->label1->width(),Qt::SmoothTransformation);
    image =image.scaledToWidth(ui->label1->width(),Qt::SmoothTransformation);
    image =image.scaledToHeight(ui->label1->height(),Qt::SmoothTransformation);
    ui->label1->clear();
    ui->label1->setPixmap(QPixmap::fromImage(image));
    ui->label1->setScaledContents( true );
    ui->label1->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );}

void otherWindow::affiche_label_2 (Mat resultat)
{   QImage imageF;

    imageF =MatVersQImage( resultat).scaledToWidth(ui->label2->width(),Qt::SmoothTransformation);
    imageF =imageF.scaledToWidth(ui->label2->width(),Qt::SmoothTransformation);
    imageF =imageF.scaledToHeight(ui->label2->height(),Qt::SmoothTransformation);
    ui->label2->clear();
    ui->label2->setPixmap(QPixmap::fromImage(imageF));
    ui->label2->setScaledContents( true );
    ui->label2->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );}


Mat imgent,imgentgris,imgsor,imgsor2;
int TypeDeSeuillage = 0;
int SeuillageMax = 6;
int ValeurSeuil =  0;
int ValeurSeuil2 = 255;
int SeuilMax = 255;
int BinaryValueMax = 255;




void  otherWindow::Laplacien_opencv(string path)
{ ui->label1->clear();
    Mat imgent, imgentgris, imgsor, imgsorabs;
    int ddepth = CV_16S;
    int kernel_size = 3;
    int scale = 1;
    int delta = 0;
    int c;

    /// Charger une image
    imgent = imread( path );
    affiche_label_1(imgent);

    if( !imgent.data )
    { }

    /// Supprimer le bruit en convolant l'image originale avec un filtre gaussien

    GaussianBlur( imgent, imgent, Size(3,3), 0, 0, BORDER_DEFAULT );

    /// Le filtre Laplacien s'applique que sur les images en niveau de gris
    /// Convertir l'image en niveau de gris
    cvtColor( imgent, imgentgris, CV_BGR2GRAY );


    /// Convoluer l'image originale par un filtre Laplacien

    Laplacian( imgentgris, imgsor, ddepth, kernel_size, scale, delta, BORDER_DEFAULT );

    /// A l'issue de la convolution on obtient des valeurs négatives due aux coefficients de la matrice de Laplacien
    /// Pour obtenir des valeurs de pixels significatives on prend la valeur absolue de toute la matrice de l'image

    convertScaleAbs( imgsor, imgsorabs );

    ui->label2->clear();
    ui->label2->setPixmap(QPixmap::fromImage(QImage(imgsorabs.data, imgsorabs.cols, imgsorabs.rows, imgsorabs.step, QImage::Format_Indexed8)));
    ui->label2->setScaledContents( true );
    ui->label2->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}
void otherWindow::Filtre_Sobel(std::string path)
{ ui->label1->clear();
    Mat src, src_gray;
    Mat grad;

    int ddepth = CV_16S;
    int scale = 1;
    int delta = 0;
    int c;
    /// Charger une image
    src = imread(path);
    affiche_label_1(src);
    /// éliminer le bruit blanc gaussien
    GaussianBlur( src, src, Size(3,3), 0, 0, BORDER_DEFAULT );
    /// Convertir l'image en nuance noir et balnc
    cvtColor( src, src_gray, CV_BGR2GRAY );

    /// Créer grad_x (dans la direction x) et grad_y (dans la direction y)
    Mat grad_x, grad_y;
    Mat abs_grad_x, abs_grad_y;

    /// Gradient X
    Sobel( src_gray, grad_x, ddepth, 1, 0, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_x, abs_grad_x );
    /// Gradient Y
    Sobel( src_gray, grad_y, ddepth, 0, 1, 3, scale, delta, BORDER_DEFAULT );
    convertScaleAbs( grad_y, abs_grad_y );
    /// Gradient résultant
    addWeighted( abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad );
    ui->label2->clear();
    ui->label2->setPixmap(QPixmap::fromImage(QImage(grad.data, grad.cols, grad.rows, grad.step, QImage::Format_Indexed8)));
    ui->label2->setScaledContents( true );
    ui->label2->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );

}
void otherWindow::Appliquer_F_Laplacien_Man(std::string path)
{
    ui->label2->clear();
    cv::Mat src, dst;
    src=imread(path);
    affiche_label_1(src);
    src = imread(path ,CV_LOAD_IMAGE_GRAYSCALE);
    if( !src.data )
    { }
    float Filtre[3][3] = {{ 0,  -1,  0 },
                          { -1,  4,  -1 },
                          { 0,  -1,  0 }};
    dst = src.clone();
    for(int y = 0; y < src.rows; y++)
        for(int x = 0; x < src.cols; x++)
            dst.at<uchar>(y,x) = 0.0;
    filtrelaplacien(src, dst, Filtre);
    ui->label2->clear();
    ui->label2->setPixmap(QPixmap::fromImage(QImage(dst.data, dst.cols, dst.rows, dst.step, QImage::Format_Indexed8)));
    ui->label2->setScaledContents( true );
    ui->label2->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );


}


void otherWindow::Appliquer_seuillage(std::string path)
{
    ui->label1->clear();

    imgent = imread(path);
    if(!imgent.data){
        cout<<"Image n'est pas chargée"<<endl;
    }

    cvtColor(imgent,imgentgris,CV_BGR2GRAY);
    namedWindow("Seuillage",WINDOW_AUTOSIZE);

    createTrackbar("TypeDeSeuillage", "Seuillage",&TypeDeSeuillage,  SeuillageMax);
    createTrackbar("ValeurSeuil","Seuillage",&ValeurSeuil,SeuilMax);
    createTrackbar("ValeurSeuil2","Seuillage",&ValeurSeuil2,SeuilMax);

    int c;
    Mat src=imread(path);
    imshow("Seuillage",src);
    while (true) {
        switch (TypeDeSeuillage) {
        case 0:
            threshold(imgentgris, imgsor, ValeurSeuil, BinaryValueMax,CV_THRESH_BINARY);
            break;
        case 1:
            threshold(imgentgris, imgsor, ValeurSeuil, BinaryValueMax,CV_THRESH_BINARY_INV);
            break;
        case 2:
            threshold(imgentgris, imgsor, ValeurSeuil, BinaryValueMax,CV_THRESH_TRUNC);
            break;
        case 3:
            threshold(imgentgris, imgsor, ValeurSeuil, BinaryValueMax,CV_THRESH_TOZERO);
            break;
        case 4:
            threshold(imgentgris, imgsor, ValeurSeuil, BinaryValueMax,CV_THRESH_TOZERO_INV);
            break;
        case 5:

            threshold(imgentgris, imgsor, ValeurSeuil, BinaryValueMax,CV_THRESH_BINARY);
            threshold(imgentgris, imgsor2, ValeurSeuil2, BinaryValueMax,CV_THRESH_BINARY_INV);
            imgsor &= imgsor2;
            break;
        case 6:
            threshold(imgentgris, imgsor, 0, BinaryValueMax,CV_THRESH_BINARY|CV_THRESH_OTSU);
            break;
        default:
            break;
        }
        ui->label2->clear();
        ui->label2->setPixmap(QPixmap::fromImage(QImage(imgsor.data, imgsor.cols, imgsor.rows, imgsor.step, QImage::Format_Indexed8)));
        ui->label2->setScaledContents( true );
        ui->label2->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
        affiche_label_1(imgent);


        c = waitKey(20);


        if((char)c == 27){
            break;
        }
    }
}

Mat otherWindow::filtrelaplacien(Mat src, Mat dst, float Filtre[][3])
{

    float sum;
    for(int y = 1; y < src.rows - 1; y++){
        for(int x = 1; x < src.cols - 1; x++){
            sum = 0.0;
            for(int k = -1; k <= 1;k++){
                for(int j = -1; j <=1; j++){
                    sum = sum + Filtre[j+1][k+1]*src.at<uchar>(y - j, x - k);
                }
            }
            dst.at<uchar>(y,x) = abs(sum);
        }
    }
    return dst;
}
void otherWindow::histogram (string path)
{
    Mat src, dst;
    src = imread( path);

    if( !src.data )
    {  }

    vector<Mat> conteneur;
    split( src, conteneur );

    int taille_hist = 256;
    float intervalle[] = { 0, 256 } ;
    const float* histintervalle = { intervalle };

    bool uniform = true; bool accumulate = false;

    Mat niv_b, niv_g, niv_r;

    calcHist( &conteneur[0], 1, 0, Mat(), niv_b, 1, &taille_hist, &histintervalle, uniform, accumulate );
    calcHist( &conteneur[1], 1, 0, Mat(), niv_g, 1, &taille_hist, &histintervalle, uniform, accumulate );
    calcHist( &conteneur[2], 1, 0, Mat(), niv_r, 1, &taille_hist, &histintervalle, uniform, accumulate );

    int W = 512; int H = 400;
    int bin_w = cvRound( (double) W/taille_hist );

    Mat histImage( H, W, CV_8UC3, Scalar( 0,0,0) );

    normalize(niv_b, niv_b, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(niv_g, niv_g, 0, histImage.rows, NORM_MINMAX, -1, Mat() );
    normalize(niv_r, niv_r, 0, histImage.rows, NORM_MINMAX, -1, Mat() );

    for( int i = 1; i < taille_hist; i++ )
    {
        line( histImage, Point( bin_w*(i-1), H - cvRound(niv_b.at<float>(i-1)) ) ,
              Point( bin_w*(i), H - cvRound(niv_b.at<float>(i)) ),
              Scalar( 255, 0, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), H - cvRound(niv_g.at<float>(i-1)) ) ,
              Point( bin_w*(i), H - cvRound(niv_g.at<float>(i)) ),
              Scalar( 0, 255, 0), 2, 8, 0  );
        line( histImage, Point( bin_w*(i-1), H - cvRound(niv_r.at<float>(i-1)) ) ,
              Point( bin_w*(i), H - cvRound(niv_r.at<float>(i)) ),
              Scalar( 0, 0, 255), 2, 8, 0  );
    }


    affiche_label_1 (src);
    affiche_label_2(histImage);

    waitKey(0);
}

void otherWindow::moyenneur_cv(string path)
{    ui->label2->clear();
     using namespace cv;
     cv::Mat dst, intermidiere;


      cv::Mat src = cv::imread(path);

       cv::Point anchor = cv::Point( -1, -1 );
        double delta = 0;
         int ddepth = -1;
          int dimension = 3;
           intermidiere = cv::Mat::ones( dimension, dimension, CV_32F )/ (float)(dimension*dimension);
            cv::filter2D(src, dst, ddepth , intermidiere, anchor, delta, cv::BORDER_REFLECT  );

             affiche_label_1 (src);
              affiche_label_2(dst);}
std::string path;

otherWindow::otherWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::otherWindow)
{
    ui->setupUi(this);
    if(pass=="user_1") {ui->groupBox->hide();
        ui->label->hide();}
}

otherWindow::~otherWindow()
{
    delete ui;
}


void otherWindow::on_pushButton_3_clicked()
{
    QString  filename =QFileDialog::getOpenFileName(this, tr("choose"),"",tr("Images(*.png *.jpg *.jpeg)"));
    if (QString::compare(filename, QString())!=0)
    {
        QImage image;
        bool valid =image.load(filename);
        if(valid)
        {
            path=filename.toStdString();
            if(pass=="root")
            {  image =image.scaledToWidth(ui->label1->width(),Qt::SmoothTransformation);
                ui->label1->clear();
                ui->label1->setPixmap(QPixmap::fromImage(image));
                ui->label1->setScaledContents( true );
                ui->label1->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
                ui->label2->clear();}
            else if (pass=="user_1"){image =image.scaledToWidth(ui->label->width(),Qt::SmoothTransformation);
                ui->label->clear();
                ui->label->setPixmap(QPixmap::fromImage(image));
                ui->label->setScaledContents( true );
                ui->label->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
                ui->label->show();}
        }
    }
    else
    {}

    ;
}




void otherWindow::on_pushButton_1_clicked()
{ui->label2->clear();
    moyenneur_cv(path);

}



void otherWindow::on_pushButton_2_clicked()
{ui->label2->clear();

    Detection_Contours_canny(path );
}


void otherWindow::on_pushButton_4_clicked()
{ui->label2->clear();
    BC(path);
}





void otherWindow::on_pushButton_clicked()
{ui->label2->clear();
    histogram(path);
}

void otherWindow::on_pushButton_5_clicked()
{ui->label2->clear();
    Appliquer_seuillage(path);
}

void otherWindow::on_pushButton_6_clicked()
{ui->label2->clear();
    Appliquer_F_Laplacien_Man(path);

}

void otherWindow::on_pushButton_7_clicked()
{ui->label2->clear();
    Laplacien_opencv(path);
}

void otherWindow::on_pushButton_8_clicked()
{ ui->label2->clear();
    Filtre_Sobel(path);
}


void otherWindow::on_commandLinkButton_clicked()
{
    hide();
    Dialog mmdiag;
    mmdiag.setModal(true);
    mmdiag.exec();
    hide();

}

void otherWindow::on_commandLinkButton_2_clicked()
{
   QString imagePath = QFileDialog::getSaveFileName(this,tr("Save File"),".jpeg");
   QImage dst= ui->label2->pixmap()->toImage();
   dst.save(imagePath);
}
