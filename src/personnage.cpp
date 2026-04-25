#include <iostream>
#include "personnage.h"
#include "Image.h"

using namespace std;

// Définition des constantes de direction
string haut = "haut";
string bas = "bas";
string droite = "droite";
string gauche = "gauche";

Personnage::Personnage()
{
    // Constructeur par défaut
}

Personnage::Personnage(const Image& image, int x, int y, int skin_x, int skin_y, const string& direction)
{
    _x = x;
    _y = y;
    _image = image;
    _skin_x = skin_x;
    _skin_y = skin_y;
    _direction_courante = direction;

    // Sélection de la première frame (16x16 pixels)
    _image.selectionnerRectangle(_skin_x * 16, _skin_y * 16, 16, 16);

    // Mise à jour de l'image selon la direction initiale
    MettreAjourDirection(_direction_courante);
}

void Personnage::dessiner() const
{
    _image.dessiner(_x, _y);
}

void Personnage::allerDroite(const Niveau& niveau)
{
    // On vérifie si on ne sort pas de l'écran et si la case cible est libre
    if (!bordAtteint(droite) && niveau.caseEstLibre(_x + 16, _y))
    {
        _x = _x + 16;
        _direction_courante = droite;
        MettreAjourDirection(_direction_courante);
    }
}

void Personnage::allerGauche(const Niveau& niveau)
{
    if (!bordAtteint(gauche) && niveau.caseEstLibre(_x - 16, _y))
    {
        _x = _x - 16;
        _direction_courante = gauche;
        MettreAjourDirection(_direction_courante);
    }
}

void Personnage::allerHaut(const Niveau& niveau)
{
    if (!bordAtteint(haut) && niveau.caseEstLibre(_x, _y - 16))
    {
        _y = _y - 16;
        _direction_courante = haut;
        MettreAjourDirection(_direction_courante);
    }
}

void Personnage::allerBas(const Niveau& niveau)
{
    if (!bordAtteint(bas) && niveau.caseEstLibre(_x, _y + 16))
    {
        _y = _y + 16;
        _direction_courante = bas;
        MettreAjourDirection(_direction_courante);
    }
}

bool Personnage::bordAtteint(const string& direction)
{
    if (direction == bas && _y + 16 >= HAUTEUR_FENETRE) return true;
    else if (direction == haut && _y - 16 < 0) return true;
    else if (direction == droite && _x + 16 >= LARGEUR_FENETRE) return true;
    else if (direction == gauche && _x - 16 < 0) return true;
    else return false;
}

void Personnage::MettreAjourDirection(const string& direction)
{
    // On sélectionne la ligne de sprites correspondant à la direction
    // (Ligne 0: bas, 1: gauche, 2: droite, 3: haut)
    if (direction == bas)
        _image.selectionnerRectangle(_skin_x * 16, _skin_y * 16, 16, 16);
    else if (direction == haut)
        _image.selectionnerRectangle(_skin_x * 16, (_skin_y + 3) * 16, 16, 16);
    else if (direction == gauche)
        _image.selectionnerRectangle(_skin_x * 16, (_skin_y + 1) * 16, 16, 16);
    else if (direction == droite)
        _image.selectionnerRectangle(_skin_x * 16, (_skin_y + 2) * 16, 16, 16);
}

void Personnage::avancer()
{
    // Inversion de direction si on touche un bord
    if (bordAtteint(_direction_courante))
    {
        if (_direction_courante == "droite") _direction_courante = "gauche";
        else if (_direction_courante == "gauche") _direction_courante = "droite";
        else if (_direction_courante == "haut") _direction_courante = "bas";
        else if (_direction_courante == "bas") _direction_courante = "haut";

        MettreAjourDirection(_direction_courante);
        return;
    }

    // Mouvement continu
    if (_direction_courante == "droite") _x += 16;
    else if (_direction_courante == "gauche") _x -= 16;
    else if (_direction_courante == "haut") _y -= 16;
    else if (_direction_courante == "bas") _y += 16;

    MettreAjourDirection(_direction_courante);
}

bool Personnage::toucher(Personnage& p1)
{
    // Collision simple : les coordonnées doivent être identiques
    return (this->_x == p1._x && this->_y == p1._y);
}

int Personnage::getX() const { return _x; }
int Personnage::getY() const { return _y; }
int Personnage::getSkinX() const { return _skin_x; }
int Personnage::getSkinY() const { return _skin_y; }
