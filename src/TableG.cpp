#include "Table.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <string>


void Table::jeuGraphique(){
    PaquetDeCarte paquet;
    Couleur atout = rien;
    paquet.melanger();
    distribuer1(paquet);
}