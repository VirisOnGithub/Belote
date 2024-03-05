#include "PaquetDeCarte.h"
#include <algorithm>
#include <cassert>

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

PaquetDeCarte PaquetDeCarte::getPaquet()
{
    return *this;
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
    std::random_shuffle(paquet.begin(), paquet.end());
}

Carte PaquetDeCarte::getPremiereCarte()
{
    assert(paquet.size() > 0);
    Carte carte = paquet[0];
    paquet.erase(paquet.begin());
    return carte;
}