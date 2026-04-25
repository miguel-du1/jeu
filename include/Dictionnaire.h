#ifndef DICTIONNAIRE_H
#define DICTIONNAIRE_H
#include <memory>

#include "Image.h"
#include "Tuile.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

using namespace std;
class Dictionnaire
{
        private :
            vector<Tuile> _tuiles ;
            // Constructeur prenant un fichier comme param鑤re

        public :
            Dictionnaire() ;
             Dictionnaire(const string& nomFichier);
             void afficher() const;
              // Méthode de recherche
        bool recherche(const string& nom, Tuile& resultat)const ;


};
#endif
