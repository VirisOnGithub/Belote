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

public:
    Joueur();
    std::string getNom();
    void setNom(std::string nom);
    int getRang();
    void setRang(int rang);
    MainJoueur& getMain();
    void setMain(const MainJoueur &main);
    void afficherJoueur();
};

#endif