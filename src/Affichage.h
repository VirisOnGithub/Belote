#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
class Affichage{
    private:
        sf::RenderWindow window;
        sf::Font font;

    public:    
        void init();
        void jeu();
        sf::Font loadFont();
};

#endif // AFFICHAGE_H