#include "PaquetDeCarte.h"
#include "Table.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>

void Table::jeuGraphique(PaquetDeCarte &p, Couleur atout){
    p=PaquetDeCarte();
    atout = rien;
    p.melanger();
    distribuer1(p);
}