#include "PaquetDeCarte.h"

PaquetDeCarte::PaquetDeCarte()
{
    for (int couleur = Couleur::coeur; couleur <= Couleur::trefle; couleur++) {
        for (int chiffre = ChiffreCarte::as; chiffre <= ChiffreCarte::sept; chiffre++) {
            Carte carte;
            carte.setCouleur(static_cast<Couleur>(couleur));
            carte.setChiffre(static_cast<ChiffreCarte>(chiffre));
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

Carte PaquetDeCarte::getCarteDansPaquet(int index)
{
    return paquet[index];
}