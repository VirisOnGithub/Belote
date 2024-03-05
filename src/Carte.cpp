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

bool Carte::operator==(const Carte &carte) const
{
    return (couleur == carte.couleur && chiffre == carte.chiffre);
}

bool hasTrumpOnTable(const std::vector<Carte>& CartesSurTable, Couleur atout)
{
    for (const Carte& carte : CartesSurTable)
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
    if (CartesSurTable.size() == 0) //Si la carte est la première carte jouée, elle ne peut pas être invalide
    {
        return true;
    }
    else
    {
        Couleur couleurPremiereCarte = CartesSurTable[0].getCouleur(); //On récupère la couleur de la première carte jouée, pour la comparer à la couleur de la carte actuelle
        if (couleurPremiereCarte == couleur)
        {
            if (couleur == atout){
                ValeurCarteAtout valeurMax = CartesSurTable[0].getValeurAtout();
                for (int i = 0; i < CartesSurTable.size(); i++)
                {
                    if (CartesSurTable[i].getValeurAtout() > valeurMax)
                    {
                        valeurMax = CartesSurTable[i].getValeurAtout();
                    }
                }


                if (getValeurAtout() > valeurMax) //Si la carte actuelle est plus forte que la carte la plus forte sur la table, elle est valide
                {
                    return true;
                }
                else{ //Sinon, on teste si le joueur a une carte plus forte que la carte la plus forte sur la table
                    for(int i = 0; i < mainJoueur.size(); i++){
                        if(mainJoueur[i].getCouleur() == atout && mainJoueur[i].getValeurAtout() > valeurMax){
                            return false;
                        }
                    }
                    return true;
                }
            }
        }
        else{
            //on teste si le joueur a une carte de la couleur de la première carte jouée
            for (int i = 0; i < mainJoueur.size(); i++){
                if (mainJoueur[i].getCouleur() == couleurPremiereCarte)
                {
                    return false;
                }
            }
            //sinon on teste si le joueur a une carte atout
            for (int i = 0; i < mainJoueur.size(); i++){
                if (mainJoueur[i].getCouleur() == atout){
                    return false;
                }
            }
            //de plus, si il y a déjà de l'atout sur la table, le joueur doit jouer de l'atout au dessus de la carte la plus forte
            if (hasTrumpOnTable(CartesSurTable, atout)){
                ValeurCarteAtout valeurMax = CartesSurTable[0].getValeurAtout(); // on récupère la valeur de la carte atout la plus forte sur la table
                for (int i = 0; i < CartesSurTable.size(); i++){
                    if (CartesSurTable[i].getValeurAtout() > valeurMax && CartesSurTable[i].getCouleur() == atout){
                        valeurMax = CartesSurTable[i].getValeurAtout();
                    }
                }
                for (int i = 0; i < mainJoueur.size(); i++){
                    if (mainJoueur[i].getCouleur() == atout && mainJoueur[i].getValeurAtout() > valeurMax){
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
        break;
    case huit:
        return huitAtout;
        break;
    case neuf:
        return neufAtout;
        break;
    case valet:
        return valetAtout;
        break;
    case dame:
        return dameAtout;
        break;
    case roi:
        return roiAtout;
        break;
    case dix:
        return dixAtout;
        break;
    case as:
        return asAtout;
        break;
    }
}

ValeurCarteNonAtout Carte::getValeurNonAtout() const
{
    switch (chiffre)
    {
    case sept:
        return septNonAtout;
        break;
    case huit:
        return huitNonAtout;
        break;
    case neuf:
        return neufNonAtout;
        break;
    case valet:
        return valetNonAtout;
        break;
    case dame:
        return dameNonAtout;
        break;
    case roi:
        return roiNonAtout;
        break;
    case dix:
        return dixNonAtout;
        break;
    case as:
        return asNonAtout;
        break;
    }
}