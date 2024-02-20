#ifndef MAIN_H
#define MAIN_H

#include "PaquetDeCarte.h"

class Main
{
private:
    std::vector<Carte> main;

public:
    Main();
    int operator=(const Carte &carte);
    int operator[](int index);
    Main getMain();
    void setMain(Main main);
    void afficherMain() const;
    void trierMain();
};

#endif