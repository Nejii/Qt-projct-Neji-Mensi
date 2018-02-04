#include<iostream>
#include <string>
#ifndef __descripteur__h
#define __descripteur__h

using namespace std;
class descripteur
{
private:

    string _Titre, _Extension; 
    float _Cout, _Taille; 
    string _auteur;
    int _Num, _Signature;
  
public:

    // constructeurs
    descripteur(){}
descripteur (string Titre, string Extension, float Taille, float Cout, int Num, string auteur, int Signature);

//Méthodes
string GetTitre();
string GetExtension();
float GetCout();
float GetTaille();
string Getauteur();
int GetNum();
int GetSignature();

void SetTitre(string Titre);
void SetExtension(string Extension);
void  SetCout(float Cout);		
void  SetTaille(float Taille);
void  Setauteur( string auteur);
void SetNum(int Num);
void SetSignature(int Signature);

};
 #endif

