#ifndef CARTE_H
#define CARTE_H

#include <iostream>
#include "enums.cpp"

class Carte
{
private:
    Couleur couleur;
    ChiffreCarte chiffre;
    bool atout;
    bool accessible;

public:
    Carte();
    Couleur getCouleur() const;
    void setCouleur(Couleur couleur);
    ChiffreCarte getChiffre() const;
    void setChiffre(ChiffreCarte chiffre);
    bool isAtout() const;
    void setAtout(bool atout);
    bool isAccessible() const;
    void setAccessible(bool accessible);
    void afficherCarte() const;
    bool operator==(const Carte &carte1) const;
};

#endif