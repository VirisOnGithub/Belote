#include "Carte.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>

sf::String Carte::getCarteG(){
    return getChiffreStr()+"_"+getCouleurStr();
}