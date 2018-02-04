#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include "descripteur.h"
#include "TableD.h"
#include "dialog.h"
#include "QMessageBox"
#include <QAbstractItemView>
#include <iostream>
#include <QtXml>
#include <QFile>

TableD pre_affichage ();
void AffichageTable(TableD table);
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
void SuupDernier (int Num);
float Somme_generale_cout(TableD table);
float Somme_generale_cout_1(TableD table);
float Somme_generale_Taille(TableD table);
float Somme_generale_Taille_1(TableD table);


TableD table;
string login, password;
void MainWindow::EnvLogin(string l,string p )
{
    login=l;
    password=p;
}

/*****************Importer les données **************/
TableD MainWindow::pre_affichage ()
{TableD td;
    QDomDocument document;
    QFile f("/home/neji/Downloads/ProjetC++/FileXML/descriptif.xml");
    if (!f.open(QIODevice::ReadOnly ))
    {
        std::cerr << "Erreur lors de chargement du fichier" << std::endl;
    }
    document.setContent(&f);
    f.close();
    QDomElement root=document.documentElement();
    QDomElement DESC=root.firstChild().toElement();
    while(!DESC.isNull())
    {
        if (DESC.tagName()=="DESC")
        {
            QString ID=DESC.attribute("ID","No ID");
            QDomElement Child=DESC.firstChild().toElement();
            QString Titre;
            QString Auteur;
            QString Extension;
            QString Taille;
            QString Cout;
            QString Signature;
            while (!Child.isNull())
            {
                if (Child.tagName()=="TITRE") Titre=Child.firstChild().toText().data();
                if (Child.tagName()=="AUTEUR") Auteur=Child.firstChild().toText().data();
                if (Child.tagName()=="EXTENSION") Extension=Child.firstChild().toText().data();
                if (Child.tagName()=="TAILLE") Taille=Child.firstChild().toText().data();
                if (Child.tagName()=="COUT") Cout=Child.firstChild().toText().data();
                if (Child.tagName()=="SIGNATURE") Signature=Child.firstChild().toText().data();
                Child = Child.nextSibling().toElement();
            }
            td.InitialiserTableD(Titre.toStdString(), Auteur.toStdString(), Extension.toStdString(),
                                 Taille.toFloat(),Cout.toFloat(),ID.toInt(),Signature.toFloat());
        }
        DESC = DESC.nextSibling().toElement();
    }

    return td;}

void MainWindow::AffichageTable(TableD table)
{
    int s=table.sizeTab();
    ui->tableWidget->setRowCount(s);
    ui->tableWidget->setColumnCount(6);
    m_TableHeader<<"Image"<<"Titre"<<"Auteur"<<"Extension"<<"Taille (Ko)"<<"Coût (€)";
    ui->tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidget->verticalHeader()->setVisible(false);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: gray;}");
    if(s>0)
    { for (int i=0; i<s;i++)
        {
            { ui->tableWidget->setItem(i,0, new  QTableWidgetItem( QString::number(table.GetdescripteurIndice(i).GetNum()) ));
                ui->tableWidget->setItem(i,1, new  QTableWidgetItem( QString::fromStdString(table.GetdescripteurIndice(i).GetTitre()) ));
                ui->tableWidget->setItem(i,2, new  QTableWidgetItem( QString::fromStdString(table.GetdescripteurIndice(i).Getauteur()) ));
                ui->tableWidget->setItem(i,3, new  QTableWidgetItem(QString::fromStdString(table.GetdescripteurIndice(i).GetExtension()) ));
                ui->tableWidget->setItem(i,4, new  QTableWidgetItem( QString::number(table.GetdescripteurIndice(i).GetTaille()) ));
                ui->tableWidget->setItem(i,5, new  QTableWidgetItem( QString::number(table.GetdescripteurIndice(i).GetCout()) ));
            }}}
    else  {QMessageBox::warning(this, "", "La table est vide"); }
}

void MainWindow::AffichageTable_1(TableD table)
{
    int s=table.sizeTab();
    int j=-1;
    int l=0;
    for (int i=0; i<s;i++)
        if(table.GetdescripteurIndice(i).GetSignature()==2)
        {  l=l+1;}

    ui->tableWidget->setRowCount(l);
    ui->tableWidget->setColumnCount(6);
    m_TableHeader<<"Image"<<"Titre"<<"Auteur"<<"Extension"<<"Taille (Ko)"<<"Coût (€)";
    ui->tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidget->verticalHeader()->setVisible(false);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: gray;}");
    if(s>0)
    { for (int i=0; i<s;i++)
        {   if(table.GetdescripteurIndice(i).GetSignature()==2)
            {
                j++;
                ui->tableWidget->setItem(j,0, new  QTableWidgetItem( QString::number(table.GetdescripteurIndice(i).GetNum()) ));
                ui->tableWidget->setItem(j,1, new  QTableWidgetItem( QString::fromStdString(table.GetdescripteurIndice(i).GetTitre()) ));
                ui->tableWidget->setItem(j,2, new  QTableWidgetItem( QString::fromStdString(table.GetdescripteurIndice(i).Getauteur()) ));
                ui->tableWidget->setItem(j,3, new  QTableWidgetItem(QString::fromStdString(table.GetdescripteurIndice(i).GetExtension()) ));
                ui->tableWidget->setItem(j,4, new  QTableWidgetItem( QString::number(table.GetdescripteurIndice(i).GetTaille()) ));
                ui->tableWidget->setItem(j,5, new  QTableWidgetItem( QString::number(table.GetdescripteurIndice(i).GetCout()) ));
            }}}
    else  {QMessageBox::warning(this, "", "La table est vide"); }
}

float MainWindow::Somme_generale_cout(TableD table)
{
    int s=table.sizeTab();
    float somme=0;
    for (int i=0; i<s;i++)
    {  somme=somme+table.GetdescripteurIndice(i).GetCout();}
    return somme;
}
float MainWindow::Somme_generale_cout_1(TableD table)
{
    int s=table.sizeTab();
    float somme=0;
    for (int i=0; i<s;i++)
        if(table.GetdescripteurIndice(i).GetSignature()==2)
        {  somme=somme+table.GetdescripteurIndice(i).GetCout();}
    return somme;
}
float MainWindow::Somme_generale_Taille(TableD table)
{
    int s=table.sizeTab();
    float somme=0;
    for (int i=0; i<s;i++)
    {  somme=somme+table.GetdescripteurIndice(i).GetTaille();}
    return somme;
}
float MainWindow::Somme_generale_Taille_1(TableD table)
{
    int s=table.sizeTab();
    float somme=0;
    for (int i=0; i<s;i++)
        if(table.GetdescripteurIndice(i).GetSignature()==2)
        {  somme=somme+table.GetdescripteurIndice(i).GetTaille();}
    return somme;
}


TableD MainWindow::Ajout (TableD table, string Titre, string Extension, float Taille, float Cout, int Num)
{ table=pre_affichage();
    return table;}

void MainWindow::RechercheCout(TableD table, float min, float max)
{
    if(min>max){QMessageBox::warning(this, "", "La valeur min saisie est supérieure à celle de max");}
    else {
        int s=table.sizeTab();
        int j=-1;
        int  l=0;
        for (int i=0; i<s;i++)
            if (table.GetdescripteurIndice(i).GetCout()>=min && table.GetdescripteurIndice(i).GetCout()<=max )
            {  l=l+1;}
        ui->tableWidget->setRowCount(l);
        ui->tableWidget->setColumnCount(6);
        m_TableHeader<<"Image"<<"Titre"<<"Extension"<<"Taille (Ko)"<<"Coût (€)"<<"Accès";
        ui->tableWidget->setHorizontalHeaderLabels(m_TableHeader);
        ui->tableWidget->verticalHeader()->setVisible(false);

        ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        ui->tableWidget->setShowGrid(true);
        ui->tableWidget->setStyleSheet("QTableView {selection-background-color: gray;}");
        for (int i=0; i<s;i++)
            if (table.GetdescripteurIndice(i).GetCout()>=min && table.GetdescripteurIndice(i).GetCout()<=max )
            {
                j++;
                ui->tableWidget->setItem(j,0, new  QTableWidgetItem( QString::number(table.GetdescripteurIndice(i).GetNum()) ));
                ui->tableWidget->setItem(j,1, new  QTableWidgetItem( QString::fromStdString(table.GetdescripteurIndice(i).GetTitre()) ));
                ui->tableWidget->setItem(j,2, new  QTableWidgetItem( QString::fromStdString(table.GetdescripteurIndice(i).Getauteur()) ));
                ui->tableWidget->setItem(j,3, new  QTableWidgetItem(QString::fromStdString(table.GetdescripteurIndice(i).GetExtension()) ));
                ui->tableWidget->setItem(j,4, new  QTableWidgetItem( QString::number(table.GetdescripteurIndice(i).GetTaille()) ));
                ui->tableWidget->setItem(j,5, new  QTableWidgetItem( QString::number(table.GetdescripteurIndice(i).GetCout()) ));
            }
        ui->groupBox_4->hide();
        ui->tableWidget->show();

    }

}
void MainWindow::RechercheCout_user1(TableD table, float min, float max)
{
    int s=table.sizeTab();
    int j=-1;
    int  l=0;
    for (int i=0; i<s;i++)
        if (table.GetdescripteurIndice(i).GetCout()>=min && table.GetdescripteurIndice(i).GetCout()<=max  &&
                table.GetdescripteurIndice(i).GetSignature()==2   )
        {  l=l+1;}
    ui->tableWidget->setRowCount(l);
    ui->tableWidget->setColumnCount(6);
    m_TableHeader<<"Image"<<"Titre"<<"Extension"<<"Taille (Ko)"<<"Coût (€)"<<"Accès";
    ui->tableWidget->setHorizontalHeaderLabels(m_TableHeader);
    ui->tableWidget->verticalHeader()->setVisible(false);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
    ui->tableWidget->setShowGrid(true);
    ui->tableWidget->setStyleSheet("QTableView {selection-background-color: gray;}");
    for (int i=0; i<s;i++)
        if (table.GetdescripteurIndice(i).GetCout()>=min && table.GetdescripteurIndice(i).GetCout()<=max &&
                table.GetdescripteurIndice(i).GetSignature()==2 )
        {
            j++;
            ui->tableWidget->setItem(j,0, new  QTableWidgetItem( QString::number(table.GetdescripteurIndice(i).GetNum()) ));
            ui->tableWidget->setItem(j,1, new  QTableWidgetItem( QString::fromStdString(table.GetdescripteurIndice(i).GetTitre()) ));
            ui->tableWidget->setItem(j,2, new  QTableWidgetItem( QString::fromStdString(table.GetdescripteurIndice(i).Getauteur()) ));
            ui->tableWidget->setItem(j,3, new  QTableWidgetItem(QString::fromStdString(table.GetdescripteurIndice(i).GetExtension()) ));
            ui->tableWidget->setItem(j,4, new  QTableWidgetItem( QString::number(table.GetdescripteurIndice(i).GetTaille()) ));
            ui->tableWidget->setItem(j,5, new  QTableWidgetItem( QString::number(table.GetdescripteurIndice(i).GetCout()) ));
        }
    ui->groupBox_4->hide();
    ui->tableWidget->show();

}




void MainWindow::Tri_Taille_C(TableD table)
{
    table.Trie(1,1);
    AffichageTable(table);
}
void MainWindow::Tri_Taille_D(TableD table)
{
    table.Trie(1,2);
    AffichageTable(table);
}
void MainWindow::Tri_Cout_C(TableD table)
{
    table.Trie(2,1);
    AffichageTable( table);
}
void MainWindow::Tri_Cout_D(TableD table)
{
    table.Trie(2,2);
    AffichageTable(table);
}
void MainWindow::Tri_Titre_C(TableD table)
{
    table.Trie(3,1);
    AffichageTable(table);
}
void MainWindow::Tri_Titre_D(TableD table)
{
    table.Trie(3,2);
    AffichageTable(table);
}

void MainWindow::Tri_Taille_C_1(TableD table)
{
    table.Trie(1,1);
    AffichageTable_1(table);
}
void MainWindow::Tri_Taille_D_1(TableD table)
{
    table.Trie(1,2);
    AffichageTable_1(table);
}
void MainWindow::Tri_Cout_C_1(TableD table)
{
    table.Trie(2,1);
    AffichageTable_1( table);
}
void MainWindow::Tri_Cout_D_1(TableD table)
{
    table.Trie(2,2);
    AffichageTable_1(table);
}
void MainWindow::Tri_Titre_C_1(TableD table)
{
    table.Trie(3,1);
    AffichageTable_1(table);
}
void MainWindow::Tri_Titre_D_1(TableD table)
{
    table.Trie(3,2);
    AffichageTable_1(table);
}
TableD MainWindow::SuppEntiere(TableD table)
{
    table.SupprimerEntiere();
    return table;

}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
   // table=pre_affichage(); // Charger les données dans la table .
    if(login=="root")
    { ui->label_15->setText("Vous êtes utilisateur de niveau: 2");}
    else  if(login=="user_1") { ui->label_15->setText("Vous êtes utilisateur de niveau: 1");}

    ui->groupBox->hide();
    ui->groupBox_2->hide();
    ui->groupBox_3->hide();
    ui->groupBox_4->hide();


}

MainWindow::~MainWindow()
{
    delete ui;
}


/*****************Importer les données **************/
void MainWindow::on_pushButton_clicked()
{
    table=pre_affichage();

}

/***************** Afficher la table **************/
void MainWindow::on_pushButton_2_clicked()
{
    if (login=="root" && password=="root")
    { AffichageTable( table);}
    else if(login=="user_1" && password=="user_1"){AffichageTable_1( table);}
    ui->groupBox->hide();
    ui->groupBox_4->hide();
    ui->groupBox_2->hide();
    ui->groupBox_3->hide();
    ui->tableWidget->show();
}

/*****************Exporter les données **************/
void MainWindow::on_pushButton_3_clicked()
{
    QDomDocument document;
    QDomElement root = document.createElement("Descriptif");
    document.appendChild(root);
    for (int i=0; i< table.sizeTab();i++)
    {  QDomElement desc = document.createElement("desc");
        desc.setAttribute("Image",/*QString::number(2)*/i);
        root.appendChild(desc);
        QDomElement titre = document.createElement("titre");
        titre.setAttribute("valeur",QString::fromStdString(table.GetdescripteurIndice(i).GetTitre()));
        desc.appendChild(titre);
        QDomElement  auteur = document.createElement("auteur");
        auteur.setAttribute("valeur",QString::fromStdString(table.GetdescripteurIndice(i).Getauteur()));
        desc.appendChild(auteur);
        QDomElement  taille = document.createElement("taille");
        taille.setAttribute("valeur",QString::number((table.GetdescripteurIndice(i).GetTaille())));
        desc.appendChild(taille);
        QDomElement cout = document.createElement("cout");
        cout.setAttribute("valeur",QString::number(table.GetdescripteurIndice(i).GetCout()));
        desc.appendChild(cout);
        QDomElement  Num = document.createElement("Num");
        Num.setAttribute("valeur",QString::number(table.GetdescripteurIndice(i).GetNum()));
        desc.appendChild(Num);
        QDomElement  signature = document.createElement("signature");
        signature.setAttribute("valeur",QString::number(table.GetdescripteurIndice(i).GetSignature()));
        desc.appendChild(signature);

    }

     QString path_file = QFileDialog::getSaveFileName(this,tr("Save File"),".xml");
     QFile file (path_file);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        qDebug() << "Impossible d'ouvrir le fichier";

    }
    else
    {
        QTextStream stream(&file);
        stream << document.toString();
        file.close();
        qDebug() << "Fini";
    }


}



/***************** Tri **************/

void MainWindow::on_actionD_croissant_triggered()
{

    if (login=="root" && password=="root")
    { Tri_Taille_C(table);}
    else if(login=="user_1" && password=="user_1"){Tri_Taille_C_1(table);}
}

void MainWindow::on_actionD_croissant_2_triggered()
{
    if (login=="root" && password=="root")
    { Tri_Taille_D(table);}
    else if(login=="user_1" && password=="user_1"){Tri_Taille_D_1(table);}

}

void MainWindow::on_actionD_croissant_3_triggered()
{

    if (login=="root" && password=="root")
    { Tri_Cout_D(table);}
    else if(login=="user_1" && password=="user_1"){Tri_Cout_D_1(table);}
}

void MainWindow::on_actionCroissant_triggered()
{
    if (login=="root" && password=="root")
    { Tri_Cout_C(table);}
    else if(login=="user_1" && password=="user_1"){Tri_Cout_C_1(table);}
}

void MainWindow::on_actionCroissant_2_triggered()
{
    if (login=="root" && password=="root")
    { Tri_Titre_C(table);}
    else if(login=="user_1" && password=="user_1"){Tri_Titre_C_1(table);}
}

void MainWindow::on_actionD_croissant_4_triggered()
{

    if (login=="root" && password=="root")
    { Tri_Titre_D(table);}
    else if(login=="user_1" && password=="user_1"){Tri_Titre_D_1(table);}
}


/*****************Supprimer les données **************/

void MainWindow::on_actionTable_enti_re_triggered()
{
    if (login=="root" && password=="root")
    { table=SuppEntiere(table);}
    else if(login=="user_1" && password=="user_1"){QMessageBox::warning(this,"Erreur" , "Vous avez pas le droit de supprimer la table");}
    ui->tableWidget->setRowCount(0);
}

void MainWindow::on_pushButton_9_clicked()
{

    if (login=="root" && password=="root")
    {   table.SupprimerUnparUn(ui->comboBox_2->currentIndex());
        table.SupDernier();}
    else if(login=="user_1" && password=="user_1"){QMessageBox::warning(this,"Erreur" , "Vous avez pas le droit de supprimer la table");}

}

/********* Ajouter **********/
void MainWindow::on_actionAjout_triggered()
{

    ui->tableWidget->hide();
    if (login=="root" && password=="root")
    { ui->groupBox->show();
        ui->groupBox_2->hide();
        ui->groupBox_3->hide();
        ui->groupBox_4->hide();}
    else if(login=="user_1" && password=="user_1"){QMessageBox::warning(this,"Erreur" , "Vous avez pas le droit d'ajouter un descripteur à la table");}
}

void MainWindow::on_actionUn_descripteur_triggered()
{
    if (login=="root" && password=="root")
    {  ui->tableWidget->hide();
        ui->groupBox->hide();
        ui->groupBox_2->hide();
        ui->groupBox_4->hide();
        ui->comboBox_2->clear();
        for (int i=0;i<table.sizeTab();i++){
            ui->comboBox_2->addItem(QString::number(table.GetdescripteurIndice(i).GetNum()));}
        ui->groupBox_3->show();}
    else if(login=="user_1" && password=="user_1"){QMessageBox::warning(this,"Erreur" , "Vous avez pas le droit d'ajouter un descripteur à la table");}

}
void MainWindow::on_pushButton_5_clicked()
{
    ui->groupBox->hide();
}
void MainWindow::on_pushButton_6_clicked()
{
    if (login=="root" && password=="root")
    { table.Ajouterdescripteur(ui->lineEdit->text().toStdString(),
                               ui->lineEdit_2->text().toStdString(),
                               ui->lineEdit_3->text().toStdString(),
                               ui->lineEdit_4->text().toFloat(),ui->lineEdit_5->text().toFloat(),table.GetdescripteurIndice(table.sizeTab()-1).GetNum()+1); }
    else if(login=="user_1" && password=="user_1"){QMessageBox::warning(this,"s" , "Vous avez pas le droit d'ajouter un descripteur à la table");}

}


/********* Modifier **********/
void MainWindow::on_actionModifier_triggered()
{
    ui->groupBox->hide();

    ui->groupBox_3->hide();
    ui->groupBox_4->hide();
    ui->tableWidget->hide();

    if (login=="root" && password=="root")
    { ui->comboBox->clear();
        for (int i=0;i<table.sizeTab();i++){
            ui->comboBox->addItem(QString::number(table.GetdescripteurIndice(i).GetNum()));}
        ui->groupBox_2->show();
    }
    else if(login=="user_1" && password=="user_1"){QMessageBox::warning(this,"Erreur" , "Vous avez pas le droit de modifier la table");}


}
void MainWindow::on_pushButton_8_clicked()
{
    ui->groupBox_2->hide();
}

void MainWindow::on_pushButton_7_clicked()
{

    if (login=="root" && password=="root")
    {   table.ModifierDescripteur(ui->lineEdit_7->text().toStdString(),
                                  ui->lineEdit_8->text().toStdString(),
                                  ui->lineEdit_9->text().toStdString(),
                                  ui->lineEdit_10->text().toFloat(),ui->lineEdit_6->text().toFloat(),ui->comboBox->currentIndex() );}
    else if(login=="user_1" && password=="user_1"){QMessageBox::warning(this,"Erreur" , "Vous avez pas le droit de modifier la table");}


    ui->groupBox_2->hide();
}

/********* Rechercher par cout **********/
void MainWindow::on_actionCout_par_interval_triggered()
{
    ui->groupBox->hide();
    ui->groupBox_2->hide();
    ui->groupBox_3->hide();
    ui->groupBox_4->show();
    ui->tableWidget->hide();
}
void MainWindow::on_pushButton_17_clicked()
{

    if (login=="root" && password=="root")
    {  RechercheCout(table,ui->lineEdit_21->text().toFloat(),ui->lineEdit_22->text().toFloat());}
    else if(login=="user_1" && password=="user_1"){RechercheCout_user1(table,ui->lineEdit_21->text().toFloat(),ui->lineEdit_22->text().toFloat());}


    ui->groupBox_4->show();

}

/********* Calcul somme de couts/tailles **********/
void MainWindow::on_actionCo_t_total_triggered()
{
    if (login=="root" && password=="root")
    {   ui->lcdNumber->display(Somme_generale_cout(table));}
    else if(login=="user_1" && password=="user_1"){ ui->lcdNumber->display(Somme_generale_cout_1(table));}
}

void MainWindow::on_actionTaille_totale_triggered()
{

    if (login=="root" && password=="root")
    {   ui->lcdNumber_2->display(Somme_generale_Taille(table));}
    else if(login=="user_1" && password=="user_1"){ ui->lcdNumber_2->display(Somme_generale_Taille_1(table));}
}


/********* Retourner vers la fenetre précédente **********/
void MainWindow::on_pushButton_backchoix_clicked()
{
    hide();
    Dialog mndiag;
    mndiag.setModal(true);
    mndiag.exec();

}




