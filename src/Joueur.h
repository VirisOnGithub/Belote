#ifndef JOUEUR_H
#define JOUEUR_H

#include "Main.h"
#include <string>

class Joueur
{
private:
    Main main;
    std::string nom;
    int rang;

public:
    Joueur();
    std::string getNom();
    void setNom(std::string nom);
    int getRang();
    void setRang(int rang);
    Main getMain();
    void setMain(Main main);
    void afficherJoueur();
};

#endif