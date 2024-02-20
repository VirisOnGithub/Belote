#include <iostream>

#include "PaquetDeCarte.h"

PaquetDeCarte::PaquetDeCarte()
{
    while (paquet.size() < 32)
    {
        Carte carte;
        bool alreadyExists = false;

        // Vérifier si la carte existe déjà dans le paquet
        for (const Carte &c : paquet)
        {
            if (c == carte)
            {
                alreadyExists = true;
                break;
            }
        }

        // Si la carte n'existe pas déjà, l'ajouter au paquet
        if (!alreadyExists)
        {
            paquet.push_back(carte);
        }
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