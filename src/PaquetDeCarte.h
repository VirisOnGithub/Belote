#ifndef PAQUETDECARTE_H
#define PAQUETDECARTE_H
#include "Carte.h"
#include "Joueur.h"
#include <vector>

class PaquetDeCarte
{
private:
    std::vector<Carte> paquet;

public:
    PaquetDeCarte();
    int operator=(const PaquetDeCarte &autre);
    int operator[](int index);
    PaquetDeCarte getPaquet();
    void setPaquet(PaquetDeCarte paquet);
    void afficherPaquet() const;
    void melanger();
    Carte getCarteDansPaquet(int index);
};

#endif