#include "Affichage.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window.hpp>
#include <iostream>

void Affichage::init(){
    font = loadFont();
    window.create(sf::VideoMode(1920, 1080), "Belote");
    window.setFramerateLimit(60);
    window.clear(sf::Color(0,128,0));
    sf::Text text;
    text.setFont(font);
    text.setString("BelotePro");
    text.setCharacterSize(50);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(1920/2 - text.getGlobalBounds().width/2, 1080/2 - text.getGlobalBounds().height/2);
    window.draw(text);
    window.display();
}

void Affichage::jeu(){
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }
    }
}

sf::Font Affichage::loadFont(){
    sf::Font font;
    if (!font.loadFromFile("../src/fonts/arial.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
    }
    return font;
}