#ifndef PAQUETDECARTE_H
#define PAQUETDECARTE_H
#include "Carte.h"
#include <vector>

class PaquetDeCarte
{
private:
    std::vector<Carte> paquet;

public:
    PaquetDeCarte();
    int operator=(const Carte &carte);
    int operator[](int index);
    PaquetDeCarte getPaquet();
    void setPaquet(PaquetDeCarte paquet);
    void afficherPaquet() const;
    Carte getCarteDansPaquet(int index);
};

#endif