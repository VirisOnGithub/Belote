#include <iostream>
#include "Joueur.h"

Joueur::Joueur()
{
    nom = "Joueur";
    rang = 0;
    main = Main();
}

std::string Joueur::getNom()
{
    return nom;
}

void Joueur::setNom(std::string nom)
{
    this->nom = nom;
}

int Joueur::getRang()
{
    return rang;
}

void Joueur::setRang(int rang)
{
    this->rang = rang;
}

Main Joueur::getMain()
{
    return main;
}

void Joueur::setMain(Main main)
{
    this->main = main;
}

void Joueur::afficherJoueur()
{
    std::cout << "Nom: " << nom << std::endl;
    std::cout << "Rang: " << rang << std::endl;
    main.afficherMain();
}