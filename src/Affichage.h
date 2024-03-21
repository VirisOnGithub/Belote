#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "Carte.h"
#include "MainJoueur.h"
#include "PaquetDeCarte.h"
#include "Table.h"
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <memory>

class Affichage
{
private:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text titre;
    std::map<sf::String, std::shared_ptr<sf::Texture>> textures;
    Table table;
    PaquetDeCarte p;
    Couleur atout;
    Carte carteRetournee;
    sf::Sprite sprite;

public:
    void init();
    void jeu();
    void menuLoop(bool &menu);
    void jeuLoop();
    sf::Font loadFont();
    void afficherMainGraphique(MainJoueur main);
    void afficherCartePriseGraphique();
    void afficherMainRetourneeGraphiqueHaut1();
    void afficherMainRetourneeGraphiqueDroite1();
    void afficherMainRetourneeGraphiqueGauche1();
    void afficherMainRetourneeGraphiqueHaut2();
    void afficherMainRetourneeGraphiqueDroite2();
    void afficherMainRetourneeGraphiqueGauche2();
};

#endif // AFFICHAGE_H