#include "Niveau.h"
#include "Tuile.h"
#include "Image.h"
#include "Dictionnaire.h"
#include "objet.h"
#include <fstream>
#include <iostream>

using namespace std;

Niveau::Niveau() {
    // Constructeur par défaut
    _Objets = {};
    bonusRestants = 0;
}

Niveau::Niveau(const Image& image, const Dictionnaire& dico, const string& fichier) {
    bonusRestants = 0;
    ifstream fichierNiveau(fichier); // Ouverture du fichier en lecture
    if (!fichierNiveau.is_open()) {
        throw runtime_error("Impossible d'ouvrir le fichier : " + fichier);
    }

    int nombreLignes;
    fichierNiveau >> nombreLignes; // Lire le nombre de lignes
    if (fichierNiveau.fail()) {
        throw runtime_error("Erreur lors de la lecture du fichier : " + fichier);
    }

    cout << "Nombre de lignes dans le fichier : " << nombreLignes << endl;

    string nom; // Permet de lire le nom de l'objet dans le niveau
    int x, y;   // Permet de lire les coordonnées

    // Lecture des objets dans le fichier
    while (lireObjet(fichierNiveau, nom, x, y)) {
        cout << "Lecture de l'objet : " << nom << " (" << x << ", " << y << ")" << endl;

        // Ajouter l'objet au vecteur après multiplication des coordonnées
        _Objets.push_back(Objet(image, nom, dico, x, y));

        if (_Objets.back().getProp() == "bonus") {
            bonusRestants++;
        }
    }

    fichierNiveau.close();
    cout << "Fichier niveau chargé avec succès." << endl;
}

void Niveau::dessiner() const {
    for (int i = 0; i < _Objets.size(); i++) {
        if (_Objets[i].getProp() != "cache") {
            _Objets[i].dessiner(); // Appeler la méthode dessiner() de chaque objet
        }
    }
}

bool Niveau::caseEstLibre(int x, int y) const {
    // On parcourt tous les objets du niveau
    for (int i = 0; i < (int)_Objets.size(); i++) {
        // Si un objet est à cette position
        if (_Objets[i].getX() == x && _Objets[i].getY() == y) {
            // Si l'objet est solide, la case n'est pas libre
            if (_Objets[i].getProp() == "solide") {
                return false;
            }
        }
    }
    // Si aucun objet solide n'a été trouvé à cette position, la case est libre
    return true;
}

bool Niveau::lireObjet(ifstream& fichier, string& nom, int& x, int& y) {
    // Essayer de lire les données du fichier
    if (fichier >> nom >> x >> y) {
        return true;
    } else {
        // Si la lecture échoue (fin de fichier par exemple)
        return false;
    }
}

void Niveau::testerBonusEtPrendre(int x, int y) {
    for (int i = 0; i < (int)_Objets.size(); i++) {
        // Vérifier si l'objet est un bonus et s'il est à la position spécifiée
        if (_Objets[i].getProp() == "bonus" && _Objets[i].getX() == x && _Objets[i].getY() == y) {
            bonusRestants--; // Décrémenter le compteur de bonus
            _Objets[i].cacher();  // Cacher l'objet
            cout << "Bonus pris aux coordonnées (" << x << ", " << y << ") !" << endl;
            return; // Sortir de la boucle une fois le bonus trouvé
        }
    }
}

bool Niveau::gagne() {
    return bonusRestants == 0;
}
