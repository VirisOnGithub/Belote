#include <iostream>

#include "PaquetDeCarte.h"

PaquetDeCarte::PaquetDeCarte()
{
    for (int i = 0; i < 32; i++)
    {
        paquet.push_back(Carte());
    }
}

int PaquetDeCarte::operator=(const Carte &carte)
{
    paquet.push_back(carte);
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