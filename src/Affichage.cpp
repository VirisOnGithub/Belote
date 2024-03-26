#include "Affichage.h"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cstdint>
#include <cstdlib>
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
#include <chrono>
#include <thread>

const char *AtouttoStr(Couleur c)
{
    switch (c)
    {
    case coeur:
        return "coeur";
    case carreau:
        return "carreau";
    case pique:
        return "pique";
    case trefle:
        return "trefle";
    case rien:
        return "rien";
    default:
        return "erreur";
    }
}

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

    sf::Image icon;
    if (!icon.loadFromFile("../assets/icon.png"))
    {
        std::cerr << "Error loading icon" << std::endl;
    }
    else
    {
        std::cout << "Icon loaded" << std::endl;
        window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    }
    p = PaquetDeCarte();
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
    ImGui::PopStyleColor(1);
}

void Affichage::jeuLoop(bool &prise, bool &jeu, int &indexJoueur, bool &premierTour)
{
    if (prise)
    {
        animDistribution(prise, jeu, indexJoueur, premierTour);
    }
    else
    {
        jeuDePlis(indexJoueur, cartesG);
    }
}

void Affichage::animDistribution(bool &prise, bool &jeu, int &indexJoueur, bool &premierTour)
{

    afficherMainRetourneeGraphiqueHaut1(5);
    afficherMainRetourneeGraphiqueDroite1(5);
    afficherMainRetourneeGraphiqueGauche1(5);
    afficherMainGraphique(table.getMains()[indexJoueur]);

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
    ImGui::SetWindowSize(ImVec2(premierTour ? 220 : 400, premierTour ? 60 : 150), ImGuiCond_Always);
    if (premierTour)
    {
        if (ImGui::Button("Je prends", ImVec2(100, 30)))
        {
            std::cout << "Je prends" << std::endl;
            prise = false;
            jeu = true;
            atout = carteRetournee.getCouleur();
            table.getMains()[indexJoueur].addCarte(carteRetournee);
            table.distribuer2(p);
        }
        ImGui::SameLine();
        if (ImGui::Button("Je passe", ImVec2(100, 30)))
        {
            std::cout << "Je passe" << std::endl;
            indexJoueur++;
            if (indexJoueur == 4)
            {
                indexJoueur = 0;
                premierTour = false;
            }
        }
    }
    else
    {
        ImGui::SetWindowPos(pos, ImGuiCond_Always);
        std::vector<Couleur> couleurs = {coeur, carreau, pique, trefle};
        atout = carteRetournee.getCouleur();
        for (int i = 0; i < couleurs.size(); i++)
        {
            if (couleurs[i] != atout)
            {
                Couleur couleurBouton = couleurs[i];
                ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
                ImGui::PushStyleColor(ImGuiCol_ButtonHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.2f));
                if (ImGui::ImageButton((void *)(uintptr_t)texturesCouleurs[couleurBouton].getNativeHandle(), ImVec2(50, 50)))
                {
                    prise = false;
                    atout = couleurBouton;
                    jeu = true;
                    table.getMains()[indexJoueur].addCarte(carteRetournee);
                    table.distribuer2(p);
                }
                ImGui::PopStyleColor(2);
                if (couleurBouton != couleurs.back() || couleurBouton == atout)
                {
                    ImGui::SameLine();
                }
            }
        }
        // bouton de passe
        ImVec2 windowSize = ImGui::GetWindowSize();
        ImVec2 buttonSize(100, 30);

        ImVec2 buttonPos = ImVec2((windowSize.x - buttonSize.x) / 2.0f, (windowSize.y - buttonSize.y) / 2.0f);

        ImGui::SetCursorPos(buttonPos);
        ImGui::SameLine();
        if (ImGui::Button("Je passe", buttonPos))
        {
            std::cout << "Je passe" << std::endl;
            indexJoueur++;
            if (indexJoueur == 4)
            {
                exit(1); // A FAIRE
            }
        }
    }

    ImGui::End();
    ImGui::PopStyleColor(1); // Specify the argument type for the function call
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
            sprite.setPosition(window.getSize().x - 120, (window.getSize().y - CardHeight * (nbCartes + 1) / 2.) / 2. + i * CardHeight / 2.);
            window.draw(sprite);
        }
        sprite.setScale(1, 1);
    }
}

void Affichage::afficherMainGraphique(MainJoueur main)
{
    int nbCartesAffichees = main.getCartesG().size();
    cartesG.clear();
    auto cartes = main.getCartesG();

    for (int i = 0; i < nbCartesAffichees; i++)
    {
        sf::Sprite sprite;
        sprite.setTexture(*textures[cartes[i]]);
        sprite.setScale(0.9, 0.9);

        // Vérifiez que les textures sont chargées correctement
        if (textures[cartes[i]]->getSize().x == 0)
        {
            std::cout << "Erreur de chargement de la texture pour la carte : " << cartes[i].toAnsiString() << std::endl;
        }

        cartesG.push_back(sprite);
    }

    if (!cartesG.empty())
    {
        int CardWidth = textures[cartes[0]]->getSize().x * cartesG[0].getScale().x;  // Prendre en compte l'échelle de la carte
        int CardHeight = textures[cartes[0]]->getSize().y * cartesG[0].getScale().y; // Prendre en compte l'échelle de la carte
        float totalWidth = cartesG.size() * CardWidth;                               // La largeur totale des cartes

        for (int i = 0; i < cartesG.size(); i++)
        {
            cartesG[i].setPosition((window.getSize().x - totalWidth) / 2.0f + i * (CardWidth), window.getSize().y - CardHeight / 2.);
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

void Affichage::afficherCartesSurTable()
{
    std::vector<Carte> cartes = table.getCartesSurTable();
    for (int i = 0; i < cartes.size(); i++)
    {
        sf::Sprite sprite;
        sprite.setTexture(*textures[cartes[i].getCarteG()]);
        sprite.setPosition((window.getSize().x - sprite.getGlobalBounds().width) / 2 + i * sprite.getGlobalBounds().width / 2., (window.getSize().y - sprite.getGlobalBounds().height) / 2);
        window.draw(sprite);
    }
}

void Affichage::jouerCarte(int indexJoueur, int indexCarte)
{
    table.CartesSurTable.push_back(table.Mains[indexJoueur].getMain()[indexCarte]);
    table.Mains[indexJoueur].getMain().erase(table.Mains[indexJoueur].getMain().begin() + indexCarte);
}

void Affichage::jeuDePlis(int &indexJoueur, std::vector<sf::Sprite> &cartesG)
{
    afficherMainRetourneeGraphiqueHaut1(table.getMains()[(indexJoueur + 2) % 4].getMain().size());
    afficherMainRetourneeGraphiqueDroite1(table.getMains()[(indexJoueur + 3) % 4].getMain().size());
    afficherMainRetourneeGraphiqueGauche1(table.getMains()[(indexJoueur + 1) % 4].getMain().size());
    afficherMainGraphique(table.getMains()[indexJoueur]);
    afficherCartesSurTable();
    showAtoutPreneur(indexJoueur);
    bool action = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !action)
    {
        action = true;
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        for (int i = cartesG.size() - 1; i >= 0; i--)
        {
            if (cartesG[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                if (table.Mains[indexJoueur].getMain()[i].estValide(table.CartesSurTable, atout, table.Mains[indexJoueur].getMain(), raison))
                {
                    action = true;
                    jouerCarte(indexJoueur, i);
                    indexJoueur++;
                    action = false;
                    raison = "";
                }
                else
                {
                    std::cout << raison << std::endl;
                }
            }
        }
        action = false;
    }
    showError(raison);
    if (indexJoueur == 4)
    {
        indexJoueur = table.getGagnant(table.CartesJouees, atout);
        table.changementOrdreJoueur(indexJoueur);
        for (int i = 0; i < 4; i++)
        {
            table.CartesJouees.push_back(table.getCartesSurTable()[i]);
        }
        table.CartesSurTable.clear();
    }
}

void Affichage::showAtoutPreneur(int indexJoueur)
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::Begin("Atout", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImVec2 pos = ImVec2(50, 10);
    ImGui::SetWindowPos(pos, ImGuiCond_Once);
    ImGui::SetWindowSize(ImVec2(250, 50), ImGuiCond_Always);
    ImGui::Text("Le preneur est le joueur %d", indexJoueur + 1);
    ImGui::Text("L'atout est %s", AtouttoStr(atout));
    ImGui::End();
    ImGui::PopStyleColor(1);
}

void Affichage::showError(std::string message)
{
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::Begin("Erreur", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImVec2 pos = ImVec2(window.getSize().x - 500, 0);
    ImGui::SetWindowPos(pos, ImGuiCond_Once);
    ImGui::SetWindowSize(ImVec2(500, 50), ImGuiCond_Always);
    ImGui::Text("%s", message.c_str());
    ImGui::End();
    ImGui::PopStyleColor(1);
}