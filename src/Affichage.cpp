#include "Affichage.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include "MainJoueur.h"
#include "Table.h"
#include "imgui-master/imgui.h"
#include "imgui-sfml/imgui-SFML.h"
#include <memory>

void Affichage::init(){
    std::string couleurs[4] = {"coeur", "carreau", "pique", "trefle"};
    std::string chiffres[8] = {"sept", "huit", "neuf", "dix", "valet", "dame", "roi", "as"};

    for (const auto& couleur : couleurs) {
        for (const auto& chiffre : chiffres) {
            auto texture = std::make_shared<sf::Texture>();
            if (!texture->loadFromFile("../assets/cartes/" + chiffre + "_" + couleur + ".png")) {
                std::cerr << "Error loading texture" << std::endl;
            } else {
                textures[chiffre + "_" + couleur] = texture;
            }
        }
    }

    font = loadFont();
    window.create(sf::VideoMode(1920, 1080), "Belote");
    if (!ImGui::SFML::Init(window)) {
        std::cerr << "Erreur d'initialisation" << std::endl;
    }
    window.clear(sf::Color(0,128,0));
    titre.setFont(font);
    titre.setString("BelotePro");
    titre.setCharacterSize(100);
    titre.setFillColor(sf::Color::White);
    titre.setStyle(sf::Text::Bold);
    titre.setPosition(static_cast<float>(window.getSize().x)/2 - titre.getGlobalBounds().width/2, static_cast<float>(window.getSize().y)/3);
    window.display();
}

void Affichage::jeu(){
    bool menu = true;
    sf::Clock deltaClock;
    
    while (window.isOpen())
    {
        ImGui::SFML::Update(window, deltaClock.restart());
        sf::Event event;
        window.clear(sf::Color(0,128,0));
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed || 
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)) 
                window.close();
        }
        menu ? menuLoop(menu) : jeuLoop();
        ImGui::SFML::Render(window);
        window.display();
    }std::map<std::string, sf::Texture> textures;
}

void Affichage::menuLoop(bool &menu){
    window.clear(sf::Color(0,128,0));
    window.draw(titre);
    ImGui::SetNextWindowPos(ImVec2(window.getSize().x/2., window.getSize().y*2/3.), ImGuiCond_Once, ImVec2(0.5f, 0.5f));
    ImGui::Begin("Menu", &menu, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    const ImVec2 buttonSize(100, 30); // Set the size of your button here

    // Center the button
    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - buttonSize.x) / 2.0f);
    ImGui::SetCursorPosY((ImGui::GetWindowSize().y - buttonSize.y) / 2.0f);

    if (ImGui::Button("Jouer", buttonSize)) {
        menu = false;
    }
    ImGui::End();
}

void Affichage::jeuLoop(){
    Table table;
    table.jeuGraphique();
    afficherMainGraphique(table.getMains()[0]);
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

void Affichage::afficherMainGraphique(MainJoueur main){
    std::vector<sf::Sprite> cartesG;
    auto cartes = main.getCartesG();    

    // Vérifiez que getCartesG() renvoie les bonnes valeurs
    std::cout << "Nombre de cartes : " << cartes.size() << std::endl;
    

    for (const auto& carte : cartes) {
        sf::Sprite sprite;
        sprite.setTexture(*textures[carte]);

        // Vérifiez que les textures sont chargées correctement
        if (textures[carte]->getSize().x == 0) {
            std::cout << "Erreur de chargement de la texture pour la carte : " << carte.toAnsiString() << std::endl;
        } else {
            std::cout << "Texture chargée pour la carte : " << carte.toAnsiString() << std::endl;
        }

        cartesG.push_back(sprite);
    }

    if (!cartesG.empty()) {
        std::cout << "Dessin de la première carte" << std::endl;
        window.draw(cartesG[0]);
    } else {
        std::cerr << "Erreur : aucune carte à dessiner" << std::endl;
    }

    // Vérifiez que window.display() est appelé après window.draw()
    std::cout << "Affichage de la fenêtre" << std::endl;
    window.display();
}