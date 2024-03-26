#include "PaquetDeCarte.h"
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

PaquetDeCarte::PaquetDeCarte()
{
    for (int couleur = Couleur::coeur; couleur <= Couleur::trefle; couleur++)
    {
        for (int chiffre = ChiffreCarte::as; chiffre <= ChiffreCarte::sept; chiffre++)
        {
            Carte carte;
            carte.setCouleur(static_cast<Couleur>(couleur));
            carte.setChiffre(static_cast<ChiffreCarte>(chiffre));
            paquet.push_back(carte);
        }
    }
}

int PaquetDeCarte::operator=(const PaquetDeCarte &autre)
{
    if (this != &autre)
    {
        paquet = autre.paquet;
    }
    return 0;
}

int PaquetDeCarte::operator[](int index)
{
    return index;
}

std::vector<Carte> PaquetDeCarte::getPaquet()
{
    return paquet;
}

void PaquetDeCarte::setPaquet(PaquetDeCarte paquet)
{
    this->paquet = paquet.paquet;
}

void PaquetDeCarte::afficherPaquet() const
{
    for (int i = 0; i < 32; i++)
    {
        paquet[i].afficherCarte();
    }
}

void PaquetDeCarte::melanger()
{
    srand(time(0));
    int n = paquet.size();
    for (int i = n - 1; i > 0; i--)
    {
        int j = rand() % (i + 1);
        std::swap(paquet[i], paquet[j]);
    }
}

Carte PaquetDeCarte::getPremiereCarte()
{
    assert(paquet.size() > 0);
    Carte carte = paquet[0];
    paquet.erase(paquet.begin());
    return carte;
}