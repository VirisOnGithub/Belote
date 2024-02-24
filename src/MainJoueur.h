#ifndef MAIN_H
#define MAIN_H

#include "Carte.h"
#include "PaquetDeCarte.h"
#include <vector>

class MainJoueur
{
private:
    std::vector<Carte> main;

public:
    MainJoueur();
    MainJoueur& operator=(const MainJoueur &autre);
    int operator[](int index);
    std::vector<Carte> getMain();
    void setMain(MainJoueur main);
    void afficherMain() const;
    void trierMain();
};

#endif