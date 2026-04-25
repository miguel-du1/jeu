#include "objet.h"        // Classe Objet
#include "Image.h"        // Manipulation des images
#include "Dictionnaire.h" // Accès au dictionnaire
#include "Tuile.h"        // Gestion des tuiles
#include <stdexcept>      // Pour std::runtime_error
#include <iostream>

using namespace std;

Objet::Objet()
    : image(), niveau_x(0), niveau_y(0), skin_x(0), skin_y(0), propriete("") {
    // Constructeur par défaut
}

Objet::Objet(const Image& img, const string& nom, const Dictionnaire& dico, int x, int y)
    : image(img), niveau_x(x * TAILLE_CASE), niveau_y(y * TAILLE_CASE) {
    Tuile t; 
    if (dico.recherche(nom, t)) {
        skin_x = t.getX(); 
        skin_y = t.getY();
        propriete = t.getPropriete(); 
    } else {
        throw runtime_error("Tuile non trouvée dans le dictionnaire : " + nom);
    }
    // Sélection de la zone de l'image correspondant à l'objet
    image.selectionnerRectangle(skin_x * TAILLE_CASE, skin_y * TAILLE_CASE, TAILLE_CASE, TAILLE_CASE);
}

void Objet::dessiner() const {
    image.dessiner(niveau_x, niveau_y);
}

int Objet::getX() const {
    return niveau_x;
}

int Objet::getY() const {
    return niveau_y;
}

string Objet::getProp() const {
    return propriete;
}

void Objet::cacher() {
     propriete = "cache"; // L'objet ne sera plus dessiné
}
