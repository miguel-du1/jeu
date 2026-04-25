#include <vector>
#include "Moteur.h"
#include "Image.h"
#include "Personnage.h"
#include "Tuile.h"
#include "Dictionnaire.h"
#include "objet.h"
#include"Niveau.h"
#include <ctime> // Pour srand(time(NULL))

using namespace std;

int main(int, char**)
{
    // Initialisation du générateur de nombres aléatoires
    srand(time(NULL));

    // Version spéciale du main, ne pas modifier
    Moteur moteur("Mon super jeu vidéo"); // Initialisation du jeu

    // Initialisation des objets Image et Personnage
    Image fond;
    Image perso;
    Image Decor;
    Image bravo;
    Image gameover;
    Personnage perso1;
    Personnage ennemi1;
    Personnage ennemi2;
    Dictionnaire dico;
    Objet Table;
    Objet Lit_bas;  // Déclaration sans initialisation
    Niveau niveau; // Objet Niveau





    try
    {
        // Chargement du dictionnaire
        dico = Dictionnaire("assets/dictionnaire.txt");
        fond = Image(moteur, "assets/fondlave.png");
        perso = Image(moteur, "assets/personnages.png");
        // On active la transparence (fond blanc) pour l'image des objets du décor
        Decor = Image(moteur,"assets/objets.png", true) ;
        bravo = Image(moteur, "assets/bravo.png", true);
        gameover = Image(moteur, "assets/gameover.png", true);
        // Chargement du niveau
        niveau = Niveau(Decor, dico, "assets/niveau1.txt");

        Table = Objet(Decor, "Table", dico, 5, 5);
        Lit_bas = Objet(Decor, "Lit_bas", dico, 10, 3);


        // Vérification du contenu du dictionnaire
        // dico.afficher(); // Décommenter pour voir le contenu du dictionnaire



        // Recherche dans le dictionnaire
        Tuile resultat;
        string nomRecherche = "Plancher";

        if (dico.recherche(nomRecherche, resultat))
        {
            cout << "La tuile '" << nomRecherche << "' a ete trouvee : ";
            resultat.afficher();
        }
        else
        {
            cout << "La tuile '" << nomRecherche << "' est introuvable." << endl;
        }

        // Initialisation des personnages
        perso1 = Personnage(perso, 3*16, 3*16, 1, 0, "bas");
        ennemi1 = Personnage(perso, 5 * 16, 16, 10, 0, "bas");
        ennemi2 = Personnage(perso, 16, 5 * 16, 10, 4, "droite");
        // Les 2 premières coordonnées pour savoir où apparaissent les personnages
        // Les 2 suivantes pour sélectionner le skin du personnage

        // Afficher le contenu du dictionnaire (débug ou gameplay)
        //dico.afficher();

    }
    catch (const runtime_error& e)
    {
        cerr << "Erreur : " << e.what() << endl;
    }

    // Variables de gestion des événements
    bool quitter = false;
    bool ouvert = false;
    bool Gauche = false;
    bool Droite = false;
    bool Haut = false;
    bool Bas = false;
bool     personnageABouge = false ;
    bool gagne = false;  // Pour savoir si le joueur a gagné
    bool perdu = false;  // Pour savoir si le joueur a perdu
    // Boucle de jeu, appelée à chaque fois que l'écran doit être mis à jour
    // (en général, 60 fois par seconde)
    while (!quitter)
    {
        // On réinitialise l'indicateur de mouvement au début de chaque tour de boucle
        personnageABouge = false;

        // I. Gestion des événements
        Evenement evenement = moteur.evenementRecu();

        while (evenement != AUCUN)
        {
            switch (evenement)
            {
            // QUITTER = croix de la fenêtre ou Echap
            case QUITTER_APPUYE:
                quitter = true;

                break;

            case ESPACE_APPUYE:
                ouvert = true;
                break;

            case ESPACE_RELACHE:
                ouvert = false;
                break;

            case GAUCHE_APPUYE:
                perso1.allerGauche(niveau);
                personnageABouge = true;
                break;

            case DROITE_APPUYE:
                perso1.allerDroite(niveau);
                personnageABouge = true;
                break;

            case HAUT_APPUYE:
                perso1.allerHaut(niveau);
                personnageABouge = true;
                break;

            case BAS_APPUYE:
                perso1.allerBas(niveau);
                personnageABouge = true;
                break;

            // TODO : gérer les autres événements si nécessaire
            default:
                break;
            }
            // Après le switch, si le personnage a bougé, tester les bonus
            if (personnageABouge)
            {
                niveau.testerBonusEtPrendre(perso1.getX(), perso1.getY());
            }
            evenement = moteur.evenementRecu();
        }


        // II. Mise à jour de l'état du jeu
        moteur.initialiserRendu(); // Efface ce qui avait été affiché précédemment et réinitialise l'écran en noir
        fond.dessiner(0, 0); // Affiche l'image de fond
        // Afficher le niveau
        niveau.dessiner();



        // III. Mise à jour des personnages
        if (moteur.animationsAmettreAjour())
        {
            // Générer un nombre aléatoire pour chaque ennemi pour décider de sa direction
            int direction_ennemi1 = rand() % 4;
            int direction_ennemi2 = rand() % 4;

            // Déplacer les ennemis en fonction de la direction aléatoire générée
            if (direction_ennemi1 == 0) ennemi1.allerHaut(niveau);   // 0 = Haut
            else if (direction_ennemi1 == 1) ennemi1.allerBas(niveau);  // 1 = Bas
            else if (direction_ennemi1 == 2) ennemi1.allerGauche(niveau);  // 2 = Gauche
            else ennemi1.allerDroite(niveau);  // 3 = Droite

            if (direction_ennemi2 == 0) ennemi2.allerHaut(niveau);   // 0 = Haut
            else if (direction_ennemi2 == 1) ennemi2.allerBas(niveau);  // 1 = Bas
            else if (direction_ennemi2 == 2) ennemi2.allerGauche(niveau);  // 2 = Gauche
            else ennemi2.allerDroite(niveau);  // 3 = Droite
        }

        if (niveau.gagne())
        {
            gagne = true;
            quitter = true;
        }


        if(perso1.toucher(ennemi1))
        {
            moteur.attendre(0.6) ;
            perdu = true;
           quitter = true ;

        }
        if(perso1.toucher(ennemi2))
        {
           moteur.attendre(0.6) ;
            perdu = true;
           quitter = true ;

        }

        perso1.dessiner();
        ennemi1.dessiner();
        ennemi2.dessiner();


        // TODO : faire bouger vos personnages, gérer des animations, etc.

        // Affiche l'image et met à jour l'écran à la fréquence de rafraîchissement (généralement 60 fois par seconde)
        moteur.finaliserRendu();


        /*Tuile t1 ("Puits",7,3,"Normal") ;
         t1.afficher();*/

    }
    // Affichage de fin selon la condition
    moteur.initialiserRendu();
    if (niveau.gagne()) {
        bravo.dessiner(35, 40);  // Affiche l'image de victoire
    } else if(perdu) {
        gameover.dessiner(35, 40);  // Affiche l'image de défaite
    }
    moteur.finaliserRendu();
    moteur.attendre(2.0);  // Pause finale avant de quitter



    return 0;
}
