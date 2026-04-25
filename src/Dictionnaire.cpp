#include "Dictionnaire.h"
#include <fstream>
#include <iostream>
using namespace std;

Dictionnaire::Dictionnaire()
{
    cout<<"constructuin d'un dictionnaire"<<endl;
}

// Constructeur
Dictionnaire::Dictionnaire(const string& nomFichier) {
    ifstream fichier(nomFichier);
    if (!fichier.is_open()) {
        cerr << "Erreur lors de l'ouverture du fichier " << nomFichier << endl;
        return;
    }

    int nombreTuiles;
    fichier >> nombreTuiles; // Lire le nombre de tuiles

    string nom, propriete;
    int x, y;

    // Lire chaque ligne du fichier et ajouter les tuiles au vecteur
    for (int i = 0; i < nombreTuiles; i++) {
        fichier >> nom >> x >> y >> propriete;
        Tuile tuile(nom, x, y, propriete);
        _tuiles.push_back(tuile);
    }

    fichier.close();
}

// Méthode pour afficher toutes les tuiles
void Dictionnaire::afficher() const {
    // Utilisation d'une boucle classique pour parcourir le vecteur
    for (int  i = 0; i < _tuiles.size(); i++) {
        _tuiles[i].afficher();
}
}
// Méthode de recherche


bool Dictionnaire::recherche(const string& nom, Tuile& resultat)const  {
    for (int i = 0; i < _tuiles.size(); ++i) {
        if (_tuiles[i].getNom() == nom) {
            resultat = _tuiles[i];
            return true;
        }
    }
    return false; // Tuile non trouvée
}
