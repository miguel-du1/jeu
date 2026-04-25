#ifndef NIVEAU_H
#define NIVEAU_H
#include "Tuile.h"
#include "Image.h"
#include "Dictionnaire.h"
#include "objet.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>
using namespace std;

class Niveau
{
    private:


        vector<Objet> _Objets ;
        int bonusRestants;


    public:
        Niveau();
        Niveau(const Image& image, const Dictionnaire& dico, const string& fichier) ;
         // Méthode pour dessiner tous les objets du niveau
        void dessiner() const;
        bool lireObjet(ifstream& fichier, string& nom, int &x, int &y);// passage par reference pour acceder aux variables
        bool caseEstLibre(int x, int y) const;
        void testerBonusEtPrendre(int x, int y);
        bool gagne();


};



#endif
