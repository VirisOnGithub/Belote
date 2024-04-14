#include "PaquetDeCarte.h"
#include "Table.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

void Table::jeuGraphique(PaquetDeCarte &p, Couleur atout)
{
    p = PaquetDeCarte();
    atout = rien;
    Joueurs[1].setEstBot(true);
    Joueurs[2].setEstBot(true);
    Joueurs[3].setEstBot(true);
    p.melanger();
    distribuer1(p);
    trierMains();
}