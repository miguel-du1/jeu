#ifndef OBJET_H
#define OBJET_H
#include "Image.h"
#include "Dictionnaire.h"
#include <string>
using namespace std;

class Objet {
private:
    Image image;          // Image associée à l'objet
    int niveau_x;         // Coordonnée x dans le niveau (en pixels)
    int niveau_y;         // Coordonnée y dans le niveau (en pixels)
    int skin_x;           // Coordonnée x dans la feuille de sprites
    int skin_y;           // Coordonnée y dans la feuille de sprites
    string propriete; // Propriété de l'objet (ex. "Normal", "Obstacle")

public:
    // Constructeur
    Objet();
    Objet(const Image& img, const string& nom, const Dictionnaire& dico, int x, int y);

    // Méthode pour dessiner l'objet
   void dessiner()const ;
   int getX()const;
   int getY()const;
   string getProp()const;
   void cacher() ;
};

#endif // OBJET_H
