#ifndef CARTE_H
#define CARTE_H

#include <iostream>
#include <vector>
#include <string.h>
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
    std::string getCouleurStr() const;
    void setCouleur(Couleur couleur);
    ChiffreCarte getChiffre() const;
    std::string getChiffreStr() const;
    void setChiffre(ChiffreCarte chiffre);
    bool isAtout() const;
    void setAtout(bool atout);
    bool isAccessible() const;
    void setAccessible(bool accessible);
    void afficherCarte() const;
    bool operator==(const Carte &carte1) const;
    bool estValide(std::vector<Carte> CartesSurTable, Couleur atout, std::vector<Carte> mainJoueur) const;
    ValeurCarteAtout getValeurAtout() const;
    ValeurCarteNonAtout getValeurNonAtout() const;
};

#endif