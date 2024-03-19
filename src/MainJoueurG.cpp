#include "MainJoueur.h"
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/String.hpp>
#include <vector>
std::vector<sf::String> MainJoueur::getCartesG(){
    std::vector<sf::String> cartesG;
    for (int i = 0; i < main.size(); i++){
        cartesG.push_back(main[i].getCarteG());
    }
    return cartesG;    
}