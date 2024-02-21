#include <iostream>
#include "MainJoueur.h"

MainJoueur::MainJoueur()
{
    PaquetDeCarte paquet;

    for (int i = 0; i < 8; i++)
    {
        main.push_back(paquet.getCarteDansPaquet(i));
    }
}

int MainJoueur::operator=(const Carte &carte)
{
    main.push_back(carte);
    return 0;
}

int MainJoueur::operator[](int index)
{
    return index;
}

MainJoueur MainJoueur::getMain()
{
    return *this;
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