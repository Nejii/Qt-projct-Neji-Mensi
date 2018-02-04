#include<iostream>
#include<vector>
#include<string>
#include "TableD.h"
#include <fstream>
#include <stdio.h>
#include <algorithm>



using namespace std;

TableD::TableD ()
{
}


/************ Getteurs ***************/

descripteur TableD::Getdescripteur (int Titre)
{
    return _description[Titre];
}

descripteur TableD::GetdescripteurIndice (int ind)
{
    return _description[ind];
}


/*********** Setteurs **************/

void
TableD::Setdescripteur (descripteur des, int i)
{
    _description[i].SetTitre (des.GetTitre ());
    _description[i].SetExtension (des.GetExtension ());
    _description[i].SetTaille (des.GetTaille ());
    _description[i].SetCout (des.GetCout ());
    _description[i].SetNum (des.GetNum ());
    _description[i].SetTaille (des.GetTaille());
    _description[i].SetSignature (des.GetSignature());
}

/***** taille de tableau****/
int TableD::sizeTab (){return _description.size ();}

/**********Initialisation de TableD*******/
void
TableD::InitialiserTableD (string Titre, string auteur, string Extension, float Taille, float Cout, int Num, int Signature)
{
    descripteur des;


    des.SetTitre (Titre);

    des.SetExtension (Extension);

    des.SetTaille (Taille);

    des.SetCout (Cout);

    des.SetNum (Num);
    des.Setauteur(auteur);
    des.SetSignature(Signature);
    _description.push_back (des);

}



/**********Ajout*******/
void
TableD::Ajouterdescripteur (string Titre,string auteur, string Extension, float Taille, float Cout, int Num)
{
    descripteur des;

    des.SetTitre (Titre);
    des.Setauteur(auteur);
    des.SetExtension (Extension);

    des.SetTaille (Taille);

    des.SetCout (Cout);

    des.SetNum (Num);
    des.SetSignature(2);
    _description.push_back (des);
}


/******************Modification  *********/

void
TableD::ModifierDescripteur (string Titre,string auteur, string Extension, float Taille, float Cout, int indice)
{
    if (Titre!=""){_description[indice].SetTitre(Titre);}
    if (auteur!=""){_description[indice].Setauteur(auteur);}
    if (Extension!=""){_description[indice].SetExtension (Extension);}
    {_description[indice].SetTaille (Taille);}
    {_description[indice].SetCout(Cout);}

}


/******************* Suppression de description**********/
void TableD::SupprimerEntiere ()
{
    _description.clear();
}


void TableD::SupDernier ()
{ descripteur des;
    _description.resize(_description.size()-1);}



void TableD::SupprimerUnparUn (int Num)
{
    for (int i = Num; i < _description.size ()-1; i++)
    { _description[i]=_description[i+1];}

}


/***** Trie par Taille ****/

void TableD::Trie (int choix, int ch)
{
    descripteur v, vs;
    vector < string > tabs (_description.size ());
    vector < float >tab (_description.size (), 0);	// pour éliminer l'erreur de segmentation fault

    string a;
    if (choix == 1)
    {
        if (ch == 1)
        {
            for (int i = 0; i < _description.size (); i++)
            {
                tab[i] = _description[i].GetTaille ();
            }

            sort (tab.begin (), tab.end ());
            int j;
            int i;

            for (j = 0; j < _description.size (); j++)
                for (i = 0; i < _description.size (); i++)

                    if (tab[j] == _description[i].GetTaille ())

                    {
                        v = _description[j];
                        _description[j] = _description[i];
                        _description[i] = v;
                    }
        }
        else if (ch == 2)
        {
            for (int i = 0; i < _description.size (); i++)
            {
                tab[i] = _description[i].GetTaille ();
            }

            sort (tab.begin (), tab.end ());
            reverse (tab.begin (), tab.end ());
            int j = 0;
            int i;

            for (j = 0; j < _description.size (); j++)
                for (i = 0; i < _description.size (); i++)

                    if (tab[j] == _description[i].GetTaille ())

                    {
                        v = _description[j];
                        _description[j] = _description[i];
                        _description[i] = v;
                    }
        }
    }


    else if (choix == 2)
    {
        if (ch == 1)
        {
            for (int i = 0; i < _description.size (); i++)
            {
                tab[i] = _description[i].GetCout ();
            }
            sort (tab.begin (), tab.end ());
            int j = 0;
            int i;

            for (j = 0; j < _description.size (); j++)
                for (i = 0; i < _description.size (); i++)

                    if (tab[j] == _description[i].GetCout ())

                    {
                        v = _description[j];
                        _description[j] = _description[i];
                        _description[i] = v;
                    }
        }
        else if (ch == 2)
        {
            for (int i = 0; i < _description.size (); i++)
            {
                tab[i] = _description[i].GetCout ();
            }

            sort (tab.begin (), tab.end ());
            reverse (tab.begin (), tab.end ());
            int j = 0;
            int i;

            for (j = 0; j < _description.size (); j++)
                for (i = 0; i < _description.size (); i++)

                    if (tab[j] == _description[i].GetCout ())

                    {
                        v = _description[j];
                        _description[j] = _description[i];
                        _description[i] = v;
                    }
        }
    }

    else if (choix == 3)
    {
        if (ch == 1)
        {
            for (int i = 0; i < _description.size (); i++)
            {
                tabs[i] = _description[i].GetTitre ();
            }

            sort (tabs.begin () + 0, tabs.end ());
            int j = 0;
            int i;

            for (j = 0; j < _description.size (); j++)
                for (i = 0; i < _description.size (); i++)

                    if (tabs[j] == _description[i].GetTitre ())

                    {
                        vs = _description[j];
                        _description[j] = _description[i];
                        _description[i] = vs;
                    }
        }
        else if (ch == 2)
        {
            for (int i = 0; i < _description.size (); i++)
            {
                tabs[i] = _description[i].GetTitre ();
            }
            sort (tabs.begin (), tabs.end ());
            reverse (tabs.begin (), tabs.end ());
            int j = 0;
            int i;

            for (j = 0; j < _description.size (); j++)
                for (i = 0; i < _description.size (); i++)

                    if (tabs[j] == _description[i].GetTitre ())

                    {
                        vs = _description[j];
                        _description[j] = _description[i];
                        _description[i] = vs;
                    }
        }}




}
