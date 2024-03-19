#include "Affichage.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>

void Affichage::init(){
    font = loadFont();
    window.create(sf::VideoMode(1920, 1080), "Belote");
    window.setFramerateLimit(60);
    window.clear(sf::Color(0,128,0));
    sf::Text text;
    text.setFont(font);
    text.setString("BelotePro");
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(static_cast<float>(window.getSize().x)/2 - text.getGlobalBounds().width/2, static_cast<float>(window.getSize().y)/3);
    window.draw(text);
    window.display();
}

void Affichage::jeu(){
    bool menu = true;
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) 
                window.close();
            menu ? menuLoop() : jeuLoop();
        }
    }
}

void Affichage::menuLoop(){
    sf::Text text;
    text.setFont(font);
    text.setString("BelotePro");
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(static_cast<float>(window.getSize().x)/2 - text.getGlobalBounds().width/2, static_cast<float>(window.getSize().y)/3);
    window.clear(sf::Color(0,128,0));
    window.draw(text);
    window.display();
}

void Affichage::jeuLoop(){
    sf::Text text;
    text.setFont(font);
    text.setString("Jeu en cours...");
    text.setCharacterSize(100);
    text.setFillColor(sf::Color::White);
    text.setStyle(sf::Text::Bold);
    text.setPosition(static_cast<float>(window.getSize().x)/2 - text.getGlobalBounds().width/2, static_cast<float>(window.getSize().y)/3);
    window.clear(sf::Color(0,128,0));
    window.draw(text);
    window.display();
}

sf::Font Affichage::loadFont(){
    sf::Font font;
    if (!font.loadFromFile("../src/fonts/GravitasOne-Regular.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
    } else {
        std::cout << "Font loaded" << std::endl;
    }
    return font;
}