#ifndef CARTE_H
#define CARTE_H

#include <iostream>

enum Couleur
{
    coeur = 0,
    carreau = 1,
    pique = 2,
    trefle = 3
};

enum ChiffreCarte
{
    as = 0,
    dix = 1,
    roi = 2,
    dame = 3,
    valet = 4,
    neuf = 5,
    huit = 6,
    sept = 7,
};

enum ValeurCarteNonAtout
{
    asNonAtout = 11,
    dixNonAtout = 10,
    roiNonAtout = 4,
    dameNonAtout = 3,
    valetNonAtout = 2,
    neufNonAtout = 0,
    huitNonAtout = 0,
    septNonAtout = 0,
};

enum ValeurCarteAtout
{
    asAtout = 11,
    dixAtout = 10,
    roiAtout = 4,
    dameAtout = 3,
    valetAtout = 20,
    neufAtout = 14,
    huitAtout = 0,
    septAtout = 0,
};

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