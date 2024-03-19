#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "MainJoueur.h"
#include "Table.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <memory>

class Affichage{
    private:
        sf::RenderWindow window;
        sf::Font font;
        sf::Text titre;
        std::map<sf::String, std::shared_ptr<sf::Texture>> textures;
        Table table;

    public:    
        void init();
        void jeu();
        void menuLoop(bool &menu);
        void jeuLoop();
        sf::Font loadFont();
        void afficherMainGraphique(MainJoueur main);
};

#endif // AFFICHAGE_H