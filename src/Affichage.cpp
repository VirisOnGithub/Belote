#include "Affichage.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
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
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
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
    ImGui::PopStyleVar(1);
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
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
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
            atoutPreneur = indexJoueur;
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
                    atoutPreneur = indexJoueur;
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
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(1);
    sprite.setTexture(*textures[carteRetournee.getCarteG()]);
    sprite.setPosition((window.getSize().x - sprite.getGlobalBounds().width) / 2, (window.getSize().y - sprite.getGlobalBounds().height) / 2);
    window.draw(sprite);
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
    assert(indexJoueur >= 0);
    assert(indexJoueur < table.Mains.size());
    assert(indexCarte >= 0);
    assert(indexCarte < table.Mains[indexJoueur].getMain().size());
    table.Mains[indexJoueur].getMain().erase(table.Mains[indexJoueur].getMain().begin() + indexCarte);
}

void Affichage::jeuDePlis(int &indexJoueur, std::vector<sf::Sprite> &cartesG)
{
    afficherMainRetourneeGraphiqueHaut1(table.getMains()[(indexJoueur + 2) % 4].getMain().size());
    afficherMainRetourneeGraphiqueDroite1(table.getMains()[(indexJoueur + 3) % 4].getMain().size());
    afficherMainRetourneeGraphiqueGauche1(table.getMains()[(indexJoueur + 1) % 4].getMain().size());
    afficherMainGraphique(table.getMains()[indexJoueur]);
    afficherCartesSurTable();
    showAtoutPreneur();
    showTrumpTakerBadge(indexJoueur);
    bool action = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !action)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        for (int i = cartesG.size() - 1; i >= 0; i--)
        {
            if (cartesG[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                if (table.Mains[indexJoueur].getMain()[i].estValide(table.CartesSurTable, atout, table.Mains[indexJoueur].getMain(), raison) && !action)
                {
                    action = true;
                    jouerCarte(indexJoueur, i);
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                    raison = "";
                    break; // sort de la boucle une fois qu'une carte valide a été jouée
                }
                else
                {
                    std::cout << raison << std::endl;
                }
            }
        }
        if (action)
        {
            indexJoueur++;
            action = false;
        }
        sf::sleep(sf::milliseconds(200)); // Pause après chaque clic
    }
    showError(raison);
    if (table.CartesSurTable.size() == 4)
    {
        sf::sleep(sf::milliseconds(1000));
        indexJoueur = table.getGagnant(table.CartesJouees, atout);
        table.changementOrdreJoueur(indexJoueur);
        for (int i = 0; i < 4; i++)
        {
            table.CartesJouees.push_back(table.getCartesSurTable()[i]);
        }
        table.CartesSurTable.clear();
    }
}