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
    int operator=(const Carte &carte);
    int operator[](int index);
    PaquetDeCarte getPaquet();
    void setPaquet(PaquetDeCarte paquet);
    void afficherPaquet() const;
    void melanger();
    void distribuer(std::vector<Joueur> &joueurs);
    Carte getCarteDansPaquet(int index);
};

#endif