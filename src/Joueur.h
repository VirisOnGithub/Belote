#ifndef JOUEUR_H
#define JOUEUR_H

#include "MainJoueur.h"
#include <string>

class Joueur
{
private:
    MainJoueur main;
    std::string nom;
    int rang;
    bool ajoue;
    bool aPrisAtout;

public:
    Joueur();
    std::string getNom();
    void setNom(std::string nom);
    int getRang();
    void setRang(int rang);
    MainJoueur& getMain();
    void setMain(const MainJoueur &main);
    bool getAPrisAtout();
    void setAPrisAtout(bool aPrisAtout);
    void afficherJoueur();
    int demanderCarte();
    void afficherMain();
    
};

#endif