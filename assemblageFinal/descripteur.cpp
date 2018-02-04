#include "descripteur.h"
#include<iostream>
#include <string>
//#include "TableD.h"

using namespace std;

//constructeur

descripteur::descripteur(string Titre, string Extension, float Taille, float Cout, int Num, string auteur, int Signature)
{_Titre=Titre;
    _Extension=Extension;
    _Taille=Taille;
    _Cout=Cout;
    _Num=Num;
    _auteur=auteur;
    _Signature=Signature;
}

//Méthodes
string descripteur::GetTitre() { return _Titre;};
string descripteur::GetExtension(){return _Extension ;};
float descripteur::GetCout(){return _Cout ;};
float descripteur::GetTaille(){return _Taille;};
string   descripteur::Getauteur(){return _auteur;};
int   descripteur::GetNum(){return _Num;};
int   descripteur::GetSignature(){return _Signature;};

void descripteur::SetTitre(string Titre){_Titre=Titre;};
void descripteur::SetExtension(string Extension){_Extension=Extension;};
void descripteur::SetCout(float Cout){_Cout=Cout;};		
void descripteur::SetTaille(float Taille){_Taille=Taille;};
void descripteur::Setauteur(string auteur){_auteur=auteur;};
void descripteur::SetNum(int Num){_Num=Num;};
void descripteur::SetSignature(int Signature){_Signature=Signature;};



































