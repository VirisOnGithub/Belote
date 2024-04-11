#include <cassert>
#include <iostream>
#include <vector>
#include "MainJoueur.h"

MainJoueur::MainJoueur()
{
    main = std::vector<Carte>();
}

MainJoueur &MainJoueur::operator=(const MainJoueur &autre)
{
    if (this != &autre)
    {
        main = autre.main;
    }
    return *this;
}

int MainJoueur::operator[](int index)
{
    return index;
}

std::vector<Carte> &MainJoueur::getMain()
{
    return main;
}

void MainJoueur::setMain(MainJoueur &main)
{
    this->main = main.main;
}

void MainJoueur::addCarte(Carte carte)
{
    main.push_back(carte);
}

void MainJoueur::afficherMain() const
{
    for (int i = 0; i < main.size(); i++)
    {
        std::cout << i+1 << ". ";
        main[i].afficherCarte();
    }
}

void MainJoueur::trierMain()
{
    for (int i = 0; i < main.size(); i++)
    {
        for (int j = i + 1; j < main.size(); j++)
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

void MainJoueur::jouerCarte(int index)
{
    assert(index >= 0 && index < main.size());
    assert(main.size() > 0);
    main.erase(std::next(main.begin(), index));
}