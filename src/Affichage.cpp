#include "Affichage.h"
#include <SFML/Graphics.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window.hpp>
#include <SFML/Window/Event.hpp>
#include <cassert>
#include <iostream>
#include "Carte.h"
#include "MainJoueur.h"
#include "PaquetDeCarte.h"
#include "Table.h"
#include "imgui-master/imgui.h"
#include "imgui-sfml/imgui-SFML.h"
#include <memory>
#include <map>
#include <ostream>
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

    if (!settingsTexture.loadFromFile("../assets/settings.png"))
    {
        std::cerr << "Error loading settings texture" << std::endl;
    }
    else
    {
        std::cout << "Settings texture loaded" << std::endl;
    }

    if (!crossTexture.loadFromFile("../assets/cross.png"))
    {
        std::cerr << "Error loading cross texture" << std::endl;
    }
    else
    {
        std::cout << "Cross texture loaded" << std::endl;
    }

    font = loadFont();
    loadMusic();
    window.create(sf::VideoMode(1920, 1080), "Belote");
    if (!ImGui::SFML::Init(window))
    {
        std::cerr << "Initialization error" << std::endl;
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
    cptTour = 0;
}

void Affichage::mainJeu()
{
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
        menu ? menuLoop() : jeuLoop();
        ImGui::SFML::Render(window);
        window.display();
    }
    std::map<std::string, sf::Texture> textures;
}

void Affichage::menuLoop()
{
    if (settings)
    {
        ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);
        ImGui::SetNextWindowPos(ImVec2(window.getSize().x / 2., window.getSize().y * 2 / 3.), ImGuiCond_Once, ImVec2(0.5f, 0.5f));
        ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
        ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
        ImGui::Begin("Settings", &settings, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);

        ImGui::SetWindowSize(ImVec2(400, 300), ImGuiCond_Always);
        ImGui::SetWindowPos(ImVec2(window.getSize().x / 2. - 200, window.getSize().y / 2. - 150), ImGuiCond_Always);
        ImGui::Text("Settings");

        ImGui::Separator();

        ImGui::Text("Volume");
        ImGui::PushStyleColor(ImGuiCol_SliderGrab, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
        ImGui::PushStyleColor(ImGuiCol_SliderGrabActive, ImVec4(0.0f, 0.0f, 0.0f, 0.5f));
        ImGui::PushStyleColor(ImGuiCol_FrameBg, ImVec4(0.0f, 0.0f, 0.0f, 0.1f));
        ImGui::PushStyleColor(ImGuiCol_FrameBgHovered, ImVec4(0.0f, 0.0f, 0.0f, 0.1f));
        ImGui::PushStyleColor(ImGuiCol_FrameBgActive, ImVec4(0.0f, 0.0f, 0.0f, 0.1f));
        ImGui::SliderFloat("##", &musicVolume, 0.0f, 100.0f, "", ImGuiSliderFlags_NoRoundToFormat);
        music.setVolume(musicVolume);

        ImGui::Separator();

        ImGui::Checkbox("Montrer les raisons de refus de la carte", &displayErrors);
        ImGui::Checkbox("Montrer les scores pendant le match", &showScoresDuringMatch);
        ImGui::Checkbox("Montrer les cartes jouées précédemment", &showLatestCards);

        ImGui::PopStyleColor(5);
        ImGui::Separator();
        ImGui::End();
        ImGui::PopStyleColor(1);
        ImGui::PopStyleVar(1);
    }
    else
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

    showParameters();
}

void Affichage::jeuLoop()
{
    if (prise)
    {
        animDistribution();
    }
    else if(jeu)
    {
        jeuDePlis(cartesG);
    } else {
        finDePartie();
    }
}

void Affichage::animDistribution()
{

    afficherMainRetourneeGraphiqueHaut1(5);
    afficherMainRetourneeGraphiqueDroite1(5);
    afficherMainRetourneeGraphiqueGauche1(5);
    if (!table.Mains[indexJoueur].main.empty())
    {
        afficherMainGraphique(table.Mains[indexJoueur]);
    }

    afficherCartePriseGraphique();
    showJoueur();
}

void Affichage::afficherCartePriseGraphique()
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
            table.trierMains();
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
                    table.trierMains();
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
                window.close(); // A FAIRE
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
    if (table.Mains[indexJoueur].getMain().empty())
    {
        // Le vecteur est vide, ne pas l'utiliser
    }
    else
    {
        // Le vecteur n'est pas vide, vous pouvez l'utiliser
        table.CartesSurTable.push_back(table.Mains[indexJoueur].getMain()[indexCarte]);
    }
    assert(indexJoueur >= 0);
    assert(indexJoueur < table.Mains.size());
    assert(indexCarte >= 0);
    assert(indexCarte < table.Mains[indexJoueur].getMain().size());
    table.Mains[indexJoueur].getMain().erase(table.Mains[indexJoueur].getMain().begin() + indexCarte);
}

void Affichage::jeuDePlis(std::vector<sf::Sprite> &cartesG)
{
    afficherMainRetourneeGraphiqueHaut1(table.Mains[(indexJoueur + 2) % 4].main.size());
    afficherMainRetourneeGraphiqueDroite1(table.Mains[(indexJoueur + 3) % 4].main.size());
    afficherMainRetourneeGraphiqueGauche1(table.Mains[(indexJoueur + 1) % 4].main.size());
    if (!table.Mains[indexJoueur].main.empty())
    {
        afficherMainGraphique(table.Mains[indexJoueur]);
    }
    afficherCartesSurTable();
    showAtoutPreneur();
    if(showScoresDuringMatch) {
        showScores();
    }
    showTrumpTakerBadge();
    showJoueur();
    bool action = false;

    if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && !action)
    {
        sf::Vector2i mousePos = sf::Mouse::getPosition(window);
        for (int i = cartesG.size() - 1; i >= 0; i--)
        {
            if (cartesG[i].getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
            {
                mtx.lock();
                bool estValide = table.Mains[indexJoueur].main[i].estValide(table.CartesSurTable, atout, table.Mains[indexJoueur].main, raison);
                mtx.unlock();
                if (estValide && !action)
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
            indexJoueur = (indexJoueur + 1) % 4;
            action = false;
        }
        sf::sleep(sf::milliseconds(200)); // Pause après chaque clic
    }
    if (displayErrors) {
        showError(raison);
    }
    if (table.CartesSurTable.size() == 4)
    {
        cartesPrécedentes = MainJoueur(table.CartesSurTable); //on garde les cartes pour les afficher au tour suivant
        cptTour++;
        sf::sleep(sf::milliseconds(1000));
        indexJoueur = table.getGagnant(table.CartesSurTable, atout);
        std::cout << indexJoueur << std::endl;
        int points = table.getPointsSurTable(atout);
        if (indexJoueur == 0 || indexJoueur == 2)
        {
            table.Equipe1.addScore(points);
            if (cptTour == 7)
            {
                table.Equipe1.addScore(10);
            }
        }
        else
        {
            table.Equipe2.addScore(points);
            if (cptTour == 7)
            {
                table.Equipe2.addScore(10);
            }
        }
        table.changementOrdreJoueur(indexJoueur);
        for (int i = 0; i < 4; i++)
        {
            table.CartesJouees.push_back(table.CartesSurTable[i]);
        }
        table.CartesSurTable.clear();
        if (cptTour == 7) {
            jeu = false;
        }
    }
}

void Affichage::finDePartie()
{
    ImGui::SetNextWindowSize(ImVec2(600, 400), ImGuiCond_Once);
    ImGui::SetNextWindowPos(ImVec2(window.getSize().x / 2., window.getSize().y * 2 / 3.), ImGuiCond_Once, ImVec2(0.5f, 0.5f));
    ImGui::PushStyleColor(ImGuiCol_WindowBg, ImVec4(0.0f, 0.0f, 0.0f, 0.0f));
    ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
    ImGui::Begin("Fin de partie", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse);
    ImGui::SetWindowSize(ImVec2(400, 300), ImGuiCond_Always);
    ImGui::SetWindowPos(ImVec2(window.getSize().x / 2. - 200, window.getSize().y / 2. - 150), ImGuiCond_Always);
    ImGui::Text("Fin de partie");
    ImGui::Separator();
    if(table.Equipe1.getScore() > table.Equipe2.getScore()) {
        ImGui::Text("L'equipe 1 a gagne");
        if(atoutPreneur == 0 || atoutPreneur == 2) {
            ImGui::Text("%s", ("C'est fait ! \n L'équipe 1 marque " + std::to_string(table.Equipe1.getScore()) + " points").c_str());
        } else {
            ImGui::Text("C'est chuté ! \n L'équipe 1 marque 162 points");
        }
    } else {
        ImGui::Text("L'equipe 2 a gagne");
        if(atoutPreneur == 1 || atoutPreneur == 3) {
            ImGui::Text("%s", ("C'est fait ! \n L'équipe 2 marque " + std::to_string(table.Equipe1.getScore()) + " points").c_str());
        } else {
            ImGui::Text("C'est chuté ! \n L'équipe 2 marque 162 points");
        }
    }
    ImGui::End();
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(1);
}