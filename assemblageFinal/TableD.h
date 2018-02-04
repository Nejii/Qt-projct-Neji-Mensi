#ifndef __TableD__h
#define __TableD__h
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include "descripteur.h"
#include <algorithm>

using namespace std;

class TableD
{

private:vector < descripteur > _description ;

public:

    /******** Constructeurs ***********/

    TableD ();


    /*********** Getteurs **************/

    descripteur Getdescripteur (int Titre);
    descripteur GetdescripteurIndice (int ind);

    /********** Setteurs *************/

    void Setdescripteur (descripteur des, int i);

    /***** taille de tableau****/
    int sizeTab ();

    /**************Initialisation de TableD**********/
    void InitialiserTableD (string Titre, string auteur, string Extension, float Taille, float Cout, int Num, int Signature);

    /****************Ajout******************/
    void Ajouterdescripteur (string Titre ,string auteur, string Extension, float Taille, float Cout, int Num);

    /*********************** Modification de la Taille ***********/
    void ModifierDescripteur (string Titre,string auteur, string Extension, float Taille, float Cout, int indice);

    /******************* Suppression de description **********/
    void SupDernier ();
    void SupprimerEntiere ();
    void SupprimerUnparUn (int Num);

    /****** Trie pour l'utilisateur 2****/
    void Trie (int choix, int ch);

};
#endif
