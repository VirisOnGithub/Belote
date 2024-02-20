#include <iostream>
#include <random>

#include "Carte.h"

Carte::Carte()
{
    atout = false;
    accessible = true;
    couleur = static_cast<Couleur>(rand() % 4);
    chiffre = static_cast<ChiffreCarte>(rand() % 8);
}

Couleur Carte::getCouleur() const
{
    return couleur;
}

void Carte::setCouleur(Couleur couleur)
{
    this->couleur = couleur;
}

ChiffreCarte Carte::getChiffre() const
{
    return chiffre;
}

void Carte::setChiffre(ChiffreCarte chiffre)
{
    this->chiffre = chiffre;
}

bool Carte::isAtout() const
{
    return atout;
}

void Carte::setAtout(bool atout)
{
    this->atout = atout;
}

bool Carte::isAccessible() const
{
    return accessible;
}

void Carte::setAccessible(bool accessible)
{
    this->accessible = accessible;
}

void Carte::afficherCarte() const
{
    std::string couleurStr;
    switch (couleur)
    {
    case pique:
        couleurStr = "pique";
        break;
    case coeur:
        couleurStr = "coeur";
        break;
    case carreau:
        couleurStr = "carreau";
        break;
    case trefle:
        couleurStr = "trefle";
        break;
    }

    std::string chiffreStr;
    switch (chiffre)
    {
    case as:
        chiffreStr = "as";
        break;
    case dix:
        chiffreStr = "dix";
        break;
    case roi:
        chiffreStr = "roi";
        break;
    case dame:
        chiffreStr = "dame";
        break;
    case valet:
        chiffreStr = "valet";
        break;
    case neuf:
        chiffreStr = "neuf";
        break;
    case huit:
        chiffreStr = "huit";
        break;
    case sept:
        chiffreStr = "sept";
        break;
    }

    std::cout << chiffreStr << " de " << couleurStr << std::endl;
}