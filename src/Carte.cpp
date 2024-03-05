#include <iostream>

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

std::string Carte::getCouleurStr() const
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
    return couleurStr;
}

void Carte::setCouleur(Couleur couleur)
{
    this->couleur = couleur;
}

ChiffreCarte Carte::getChiffre() const
{
    return chiffre;
}

std::string Carte::getChiffreStr() const
{
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
    return chiffreStr;
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
    std::cout << getChiffreStr() << " de " << getCouleurStr() << std::endl;
}

bool Carte::operator==(const Carte &carte) const
{
    return (couleur == carte.couleur && chiffre == carte.chiffre);
}

bool hasTrumpOnTable(const std::vector<Carte> &CartesSurTable, Couleur atout)
{
    for (const Carte &carte : CartesSurTable)
    {
        if (carte.getCouleur() == atout)
        {
            return true;
        }
    }
    return false;
}

bool Carte::estValide(std::vector<Carte> CartesSurTable, Couleur atout, std::vector<Carte> mainJoueur) const
{
    if (CartesSurTable.size() == 0) // Si la carte est la première carte jouée, elle ne peut pas être invalide
    {
        return true;
    }
    else
    {
        Couleur couleurPremiereCarte = CartesSurTable[0].getCouleur(); // On récupère la couleur de la première carte jouée, pour la comparer à la couleur de la carte actuelle
        if (couleurPremiereCarte == couleur)
        {
            if (couleur == atout)
            {
                ValeurCarteAtout valeurMax = CartesSurTable[0].getValeurAtout();
                for (int i = 0; i < CartesSurTable.size(); i++)
                {
                    if (CartesSurTable[i].getValeurAtout() > valeurMax)
                    {
                        valeurMax = CartesSurTable[i].getValeurAtout();
                    }
                }

                if (getValeurAtout() > valeurMax) // Si la carte actuelle est plus forte que la carte la plus forte sur la table, elle est valide
                {
                    return true;
                }
                else
                { // Sinon, on teste si le joueur a une carte plus forte que la carte la plus forte sur la table
                    for (int i = 0; i < mainJoueur.size(); i++)
                    {
                        if (mainJoueur[i].getCouleur() == atout && mainJoueur[i].getValeurAtout() > valeurMax)
                        {
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        else
        {
            // on teste si le joueur a une carte de la couleur de la première carte jouée
            for (int i = 0; i < mainJoueur.size(); i++)
            {
                if (mainJoueur[i].getCouleur() == couleurPremiereCarte)
                {
                    return false;
                }
            }
            // sinon on teste si le joueur a une carte atout
            for (int i = 0; i < mainJoueur.size(); i++)
            {
                if (mainJoueur[i].getCouleur() == atout)
                {
                    return false;
                }
            }
            // de plus, si il y a déjà de l'atout sur la table, le joueur doit jouer de l'atout au dessus de la carte la plus forte
            if (hasTrumpOnTable(CartesSurTable, atout))
            {
                ValeurCarteAtout valeurMax = septAtout;
                for (int i = 0; i < CartesSurTable.size(); i++)
                {
                    if (CartesSurTable[i].getValeurAtout() > valeurMax && CartesSurTable[i].getCouleur() == atout)
                    {
                        valeurMax = CartesSurTable[i].getValeurAtout();
                    }
                }
                for (int i = 0; i < mainJoueur.size(); i++)
                {
                    if (mainJoueur[i].getCouleur() == atout && mainJoueur[i].getValeurAtout() > valeurMax)
                    {
                        return false;
                    }
                }
            }
        }
    }
    return true;
}

ValeurCarteAtout Carte::getValeurAtout() const
{
    switch (chiffre)
    {
    case sept:
        return septAtout;
    case huit:
        return huitAtout;
    case neuf:
        return neufAtout;
    case valet:
        return valetAtout;
    case dame:
        return dameAtout;
    case roi:
        return roiAtout;
    case dix:
        return dixAtout;
    case as:
        return asAtout;
    default:
        return septAtout;
    }
}

ValeurCarteNonAtout Carte::getValeurNonAtout() const
{
    switch (chiffre)
    {
    case sept:
        return septNonAtout;
    case huit:
        return huitNonAtout;
    case neuf:
        return neufNonAtout;
    case valet:
        return valetNonAtout;
    case dame:
        return dameNonAtout;
    case roi:
        return roiNonAtout;
    case dix:
        return dixNonAtout;
    case as:
        return asNonAtout;
    default:
        return septNonAtout;
    }
}