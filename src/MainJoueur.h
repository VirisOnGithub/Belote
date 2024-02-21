#ifndef MAIN_H
#define MAIN_H

#include "PaquetDeCarte.h"

class MainJoueur
{
private:
    std::vector<Carte> main;

public:
    MainJoueur();
    int operator=(const Carte &carte);
    int operator[](int index);
    MainJoueur getMain();
    void setMain(MainJoueur main);
    void afficherMain() const;
    void trierMain();
};

#endif