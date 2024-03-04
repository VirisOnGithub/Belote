#ifndef MAIN_H
#define MAIN_H

#include "Carte.h"
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
    void addCarte(Carte carte);
    void afficherMain() const;
    void trierMain();
};

#endif