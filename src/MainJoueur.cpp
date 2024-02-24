#include <iostream>
#include <vector>
#include "MainJoueur.h"

MainJoueur::MainJoueur()
{
    PaquetDeCarte paquet;

    for (int i = 0; i < 8; i++)
    {
        main.push_back(paquet.getCarteDansPaquet(i));
    }
}

MainJoueur& MainJoueur::operator=(const MainJoueur &autre)
{
    if (this != &autre) {
        main = autre.main;
    }
    return *this;
}

int MainJoueur::operator[](int index)
{
    return index;
}

std::vector<Carte> MainJoueur::getMain()
{
    return main;
}

void MainJoueur::setMain(MainJoueur main)
{
    this->main = main.main;
}

void MainJoueur::afficherMain() const
{
    for (int i = 0; i < 8; i++)
    {
        main[i].afficherCarte();
    }
}

void MainJoueur::trierMain()
{
    for (int i = 0; i < 8; i++)
    {
        for (int j = i + 1; j < 8; j++)
        {
            if (main[i].getCouleur() < main[j].getCouleur())
            {
                Carte temp = main[i];
                main[i] = main[j];
                main[j] = temp;
            }
            else if (main[i].getCouleur() == main[j].getCouleur() && main[i].getChiffre() < main[j].getChiffre())
            {
                Carte temp = main[i];
                main[i] = main[j];
                main[j] = temp;
            }
        }
    }
}