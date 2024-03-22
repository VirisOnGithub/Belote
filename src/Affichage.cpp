#include "Affichage.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cassert>
#include <cstdint>
#include <iostream>
#include "Carte.h"
#include "MainJoueur.h"
#include "PaquetDeCarte.h"
#include "Table.h"
#include "imgui-master/imgui.h"
#include "imgui-sfml/imgui-SFML.h"
#include <memory>
#include <map>
#include <string>
#include <vector>
#include "imgui-sfml/imgui-SFML.h"

void Affichage::init()
{
    std::string couleurs[4] = {"coeur", "carreau", "pique", "trefle"};
    std::string chiffres[8] = {"sept", "huit", "neuf", "dix", "valet", "dame", "roi", "as"};

    for (const auto &couleur : couleurs)
    {
        for (const auto &chiffre : chiffres)
        {
            auto texture = std::make_shared<sf::Texture>();
            if (!texture->loadFromFile("../assets/cartes/" + chiffre + "_" + couleur + ".png"))
            {
                std::cerr << "Error loading texture" << std::endl;
            }
            else
            {
                textures[chiffre + "_" + couleur] = texture;
            }
        }
    }

    font = loadFont();
    window.create(sf::VideoMode(1920, 1080), "Belote");
    if (!ImGui::SFML::Init(window))
    {
        std::cerr << "Erreur d'initialisation" << std::endl;
    }
    window.clear(sf::Color(0, 128, 0));
    titre.setFont(font);
    titre.setString("BelotePro");
    titre.setCharacterSize(100);
    titre.setFillColor(sf::Color::White);
    titre.setStyle(sf::Text::Bold);
    titre.setPosition(static_cast<float>(window.getSize().x) / 2 - titre.getGlobalBounds().width / 2, static_cast<float>(window.getSize().y) / 3);
    window.display();

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////:
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////:
    table.jeuGraphique(p, atout);
    carteRetournee = Carte(sept, rien);

    texturesCouleurs[coeur].loadFromFile("../assets/couleurs/coeur.png");
    texturesCouleurs[carreau].loadFromFile("../assets/couleurs/carreau.png");
    texturesCouleurs[pique].loadFromFile("../assets/couleurs/pique.png");
    texturesCouleurs[trefle].loadFromFile("../assets/couleurs/trefle.png");
}

void Affichage::jeu()
{
    bool menu = true;
    bool prise = false;
    bool jeu = false;
    bool premierTour = true;
    int indexJoueur = 0;
    sf::Clock deltaClock;

    while (window.isOpen())
    {
        ImGui::SFML::Update(window, deltaClock.restart());
        sf::Event event;
        window.clear(sf::Color(0, 128, 0));
        while (window.pollEvent(event))
        {
            ImGui::SFML::ProcessEvent(window, event);
            if (event.type == sf::Event::Closed ||
                (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape))
                window.close();
        }
        menu ? menuLoop(menu, prise) : jeuLoop(prise, jeu, indexJoueur, premierTour);
        ImGui::SFML::Render(window);
        window.display();
    }
    std::map<std::string, sf::Texture> textures;
}

void Affichage::menuLoop(bool &menu, bool &prise)
{
    window.draw(titre);
    ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(window.getSize().x / 2., window.getSize().y * 2 / 3.), ImGuiCond_Once, ImVec2(0.5f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::Begin("Menu", &menu, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    const ImVec2 buttonSize(300, 60);

    ImGui::SetCursorPosX((ImGui::GetWindowSize().x - buttonSize.x) / 2.0f);
    ImGui::SetCursorPosY((ImGui::GetWindowSize().y - buttonSize.y) / 2.0f);

    ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.3f));
    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.1f));
    if (ImGui::Button("Jouer", buttonSize))
    {
        menu = false;
        prise = true;
    }
    ImGui::PopStyleColor(2);
    ImGui::End();
    ImGui::PopStyleColor();
}

void Affichage::jeuLoop(bool &prise, bool &jeu, int &indexJoueur, bool &premierTour)
{
    if (prise)
    {
        animDistribution(prise, jeu, indexJoueur, premierTour);
    }
    else
    {
        // jeu
    }
}

void Affichage::animDistribution(bool &prise, bool &jeu, int &indexJoueur, bool &premierTour){
    
    afficherMainRetourneeGraphiqueHaut1(5);
    afficherMainRetourneeGraphiqueDroite1(5);
    afficherMainRetourneeGraphiqueGauche1(5);
    afficherMainGraphique(table.getMains()[indexJoueur], 5);

    afficherCartePriseGraphique(prise, jeu, indexJoueur, premierTour);
}

void Affichage::afficherCartePriseGraphique(bool &prise, bool &jeu, int &indexJoueur, bool &premierTour)
{
    static bool isCarteRetourneeSet = false;
    if (!isCarteRetourneeSet && carteRetournee.getCouleur() == rien)
    {
        carteRetournee = p.getPremiereCarte();
        std::cout << "Carte retournée : " << carteRetournee.getChiffreStr() << " de " << carteRetournee.getCouleurStr() << std::endl;
        isCarteRetourneeSet = true;
    }
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::Begin("Prise", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    int offset = premierTour ? 110 : 200;
    ImVec2 pos = ImVec2(window.getSize().x / 2. - offset, window.getSize().y / 2. + 200);
    ImGui::SetWindowPos(pos, ImGuiCond_Once);
    ImGui::SetWindowSize(ImVec2(premierTour ? 220 : 400, premierTour ? 60 : 300), ImGuiCond_Once);
    if (premierTour) {
        if(ImGui::Button("Je prends", ImVec2(100, 30))){
        std::cout << "Je prends" << std::endl;
        prise = false;
        jeu = true;   
        }
        ImGui::SameLine();
        if(ImGui::Button("Je passe", ImVec2(100, 30))){
            std::cout << "Je passe" << std::endl;
            indexJoueur ++;
            if (indexJoueur == 4){
                indexJoueur = 0;
                premierTour = false;
            }
        }
    } else {
        std::vector<Couleur> couleurs = {coeur, carreau, pique, trefle};
        Couleur atout = carteRetournee.getCouleur();
        for(const auto &couleur : couleurs){
            if(couleur != atout){
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.2f));
                if(ImGui::ImageButton((void*)(uintptr_t)texturesCouleurs[couleur].getNativeHandle(), ImVec2(50, 50))){
                    prise = false;
                    jeu = true;
                }
                ImGui::PopStyleColor(2);
                ImGui::SameLine();
            }
        }
    }
    ImGui::End();
    ImGui::PopStyleColor();
    sprite.setTexture(*textures[carteRetournee.getCarteG()]);
    sprite.setPosition((window.getSize().x - sprite.getGlobalBounds().width) / 2, (window.getSize().y - sprite.getGlobalBounds().height) / 2);
    window.draw(sprite);
}

void Affichage::afficherMainRetourneeGraphiqueHaut1(int nbCartes)
{
    // Assurez-vous que la carte est définie
    sf::Texture texture;
    if (!texture.loadFromFile("../assets/back/BlueCardBack.png"))
    {
        std::cerr << "Erreur de chargement de la texture" << std::endl;
    }
    else
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setScale(0.55, 0.55);
        int CardWidth = sprite.getGlobalBounds().width;
        int CardHeight = sprite.getGlobalBounds().height;
        for (int i = 0; i < nbCartes; i++)
        {
            sprite.setPosition((window.getSize().x - CardWidth * (nbCartes + 1) / 2.) / 2. + i * CardWidth / 2., -120);
            window.draw(sprite);
        }
        sprite.setScale(1, 1);
    }
}

void Affichage::afficherMainRetourneeGraphiqueDroite1(int nbCartes)
{
    sf::Texture texture;
    if (!texture.loadFromFile("../assets/back/90DegBlueCardBack.png"))
    {
        std::cerr << "Erreur de chargement de la texture" << std::endl;
    }
    else
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setScale(0.55, 0.55);
        int CardWidth = sprite.getGlobalBounds().width;
        int CardHeight = sprite.getGlobalBounds().height;
        for (int i = 0; i < nbCartes; i++)
        {
            sprite.setPosition(-120, (window.getSize().y - CardHeight * (nbCartes + 1) / 2.) / 2. + i * CardHeight / 2.);
            window.draw(sprite);
        }
        sprite.setScale(1, 1);
    }
}

void Affichage::afficherMainRetourneeGraphiqueGauche1(int nbCartes)
{
    sf::Texture texture;
    if (!texture.loadFromFile("../assets/back/90DegBlueCardBack.png"))
    {
        std::cerr << "Erreur de chargement de la texture" << std::endl;
    }
    else
    {
        sf::Sprite sprite;
        sprite.setTexture(texture);
        sprite.setScale(0.55, 0.55);
        int CardWidth = sprite.getGlobalBounds().width;
        int CardHeight = sprite.getGlobalBounds().height;
        for (int i = 0; i < nbCartes; i++)
        {
            sprite.setPosition(window.getSize().x - 120, (window.getSize().y - CardHeight * (nbCartes +1) / 2.) / 2. + i * CardHeight / 2.);
            window.draw(sprite);
        }
        sprite.setScale(1, 1);
    }
}

void Affichage::afficherMainGraphique(MainJoueur main, int nbCartesAffichees)
{
    assert(nbCartesAffichees <= main.getCartesG().size());
    std::vector<sf::Sprite> cartesG;
    auto cartes = main.getCartesG();

    for (int i = 0; i < nbCartesAffichees; i++)
    {
        sf::Sprite sprite;
        sprite.setTexture(*textures[cartes[i]]);

        // Vérifiez que les textures sont chargées correctement
        if (textures[cartes[i]]->getSize().x == 0)
        {
            std::cout << "Erreur de chargement de la texture pour la carte : " << cartes[i].toAnsiString() << std::endl;
        }

        cartesG.push_back(sprite);
    }

    if (!cartesG.empty())
    {
        int CardWidth = textures[cartes[0]]->getSize().x;
        int CardHeight = textures[cartes[0]]->getSize().y;
        for (int i = 0; i < cartesG.size(); i++)
        {
            cartesG[i].setPosition((window.getSize().x - CardWidth * (cartesG.size() + 1) / 2.) / 2. + i * CardWidth / 2., window.getSize().y - CardHeight / 2.);
            window.draw(cartesG[i]);
        }
    }
    else
    {
        std::cerr << "Erreur : aucune carte à dessiner" << std::endl;
    }
}

sf::Font Affichage::loadFont()
{
    sf::Font font;
    if (!font.loadFromFile("../src/fonts/GravitasOne-Regular.ttf"))
    {
        std::cerr << "Error loading font" << std::endl;
    }
    else
    {
        std::cout << "Font loaded" << std::endl;
    }
    return font;
}