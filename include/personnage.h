#ifndef PERSONNAGE_H
#define PERSONNAGE_H

#include <memory>

#include "Image.h"
#include "Niveau.h"



#include <iostream>
#include <vector>
#include <string>
using namespace std;

class Personnage
{
private :
    Image _image ;
    int _x ;
    int _y ;
    int _skin_x ;
    int _skin_y ;
    string _direction_courante ;
public:
    Personnage();
    Personnage(const Image&image,int x, int y,int skin_x, int skin_y,const string& direction) ;
    void dessiner ()const ;
    void allerDroite(const Niveau&niveau) ;
    void allerGauche(const Niveau&niveau);
    void  allerHaut(const Niveau&niveau);
    void  allerBas(const Niveau&niveau);
    bool bordAtteint(const string& direction);
    void avancer() ;
    void MettreAjourDirection(const string& direction);
    bool toucher(Personnage&) ;
    int getX() const; // Retourne _x
    int getY() const; // Retourne _y
    int getSkinX() const; // Retourne _skin_x
    int getSkinY() const; // Retourne _skin_y









};




#endif
