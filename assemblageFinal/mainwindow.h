#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "descripteur.h"
#include "TableD.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent =0);
    ~MainWindow();
    void AffichageTable( TableD table);
    void AffichageTable_1( TableD table);
    void Tri_Taille_C(TableD table);
    void Tri_Taille_D(TableD table);
    void Tri_Cout_C(TableD table);
    void Tri_Cout_D(TableD table);
    void Tri_Titre_C(TableD table);
    void Tri_Titre_D(TableD table);
    void Tri_Taille_C_1(TableD table);
    void Tri_Taille_D_1(TableD table);
    void Tri_Cout_C_1(TableD table);
    void Tri_Cout_D_1(TableD table);
    void Tri_Titre_C_1(TableD table);
    void Tri_Titre_D_1(TableD table);
    TableD SuppEntiere(TableD table);
    void RechercheCout(TableD table, float min, float max);
    void RechercheCout_user1(TableD table, float min, float max);
    TableD Ajout (TableD table, string Titre, string Extension, float Taille, float Cout, int Num);
    TableD pre_affichage ();
    float Somme_generale_cout(TableD table);
    float Somme_generale_cout_1(TableD table);
    float Somme_generale_Taille(TableD table);
    float Somme_generale_Taille_1(TableD table);
    void EnvLogin(std::string l, std::string p);
private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_actionD_croissant_triggered();

    void on_actionD_croissant_2_triggered();

    void on_actionD_croissant_3_triggered();

    void on_actionCroissant_triggered();

    void on_actionCroissant_2_triggered();

    void on_actionD_croissant_4_triggered();

    void on_actionTable_enti_re_triggered();

    void on_actionAjout_triggered();

    void on_actionCout_par_interval_triggered();

    void on_actionModifier_triggered();

    void on_actionUn_descripteur_triggered();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_17_clicked();

    void on_actionCo_t_total_triggered();

    void on_actionTaille_totale_triggered();

    void on_pushButton_backchoix_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_8_clicked();

private:
    Ui::MainWindow *ui;

    QStringList m_TableHeader;



};

#endif // MAINWINDOW_H
