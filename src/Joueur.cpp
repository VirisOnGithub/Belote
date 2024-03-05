#include <iostream>
#include "Joueur.h"

Joueur::Joueur()
{
    nom = "Joueur";
    rang = 0;
    main = MainJoueur();
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

MainJoueur& Joueur::getMain()
{
    return main;
}

void Joueur::setMain(const MainJoueur& main) {
    this->main = main;
}

bool Joueur::getAPrisAtout()
{
    return aPrisAtout;
}

void Joueur::setAPrisAtout(bool aPris)
{
    this->aPrisAtout = aPris;
}

void Joueur::afficherJoueur()
{
    std::cout << "Nom: " << nom << std::endl;
    std::cout << "Rang: " << rang << std::endl;
}

int Joueur::demanderCarte()
{
    int index;
    std::cout << "Entrez l'index de la carte que vous voulez jouer: ";
    std::cin >> index;
    return index;
}

void Joueur::afficherMain()
{
    main.afficherMain();
}

