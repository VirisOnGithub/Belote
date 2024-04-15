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
#include <map>
#include <ostream>
#include <string>
#include <vector>

void Affichage::animDistributionBot()
{
    afficherMainRetourneeGraphiqueHaut1(5);
    afficherMainRetourneeGraphiqueDroite1(5);
    afficherMainRetourneeGraphiqueGauche1(5);
    if (!table.Mains[0].main.empty() && !table.Joueurs[indexJoueur].getEstBot())
    {
        afficherMainGraphique(table.Mains[indexJoueur]);
    }
    afficherCartePriseGraphiqueBot();
    showJoueur();
}

void Affichage::afficherCartePriseGraphiqueBot()
{
    std::pair<int, Couleur> priseCouleur;
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
        if (table.Joueurs[indexJoueur].getEstBot())
        {
            priseCouleur = table.Joueurs[indexJoueur].botPrise(carteRetournee, table.Mains[indexJoueur].getMain(), !premierTour);
            jeu = priseCouleur.first;
            if (jeu)
            {
                prise = false;
                table.changementOrdreJoueur(indexJoueur);
                atoutPreneur = indexJoueur;
                atout = carteRetournee.getCouleur();
                table.getMains()[indexJoueur].addCarte(carteRetournee);
                table.distribuer2(p);
                table.trierMains();
            }
            else
            {
                indexJoueur++;
                if (indexJoueur == 4)
                {
                    indexJoueur = 0;
                    premierTour = false;
                }
            }
            sleep_next_time = true;
        }
        else
        {
            if (ImGui::Button("Je prends", ImVec2(100, 30)))
            {
                std::cout << "Je prends" << std::endl;
                prise = false;
                jeu = true;
                atoutPreneur = indexJoueur;
                atout = carteRetournee.getCouleur();
                table.changementOrdreJoueur(indexJoueur);
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
    }
    else
    {
        if (table.Joueurs[indexJoueur].getEstBot())
        {
            priseCouleur = table.Joueurs[indexJoueur].botPrise(carteRetournee, table.Mains[indexJoueur].getMain(), !premierTour);
            jeu = priseCouleur.first;
            if (jeu)
            {
                prise = false;
                table.changementOrdreJoueur(indexJoueur);
                atoutPreneur = indexJoueur;
                atout = priseCouleur.second;
                table.getMains()[indexJoueur].addCarte(carteRetournee);
                table.distribuer2(p);
                table.trierMains();
                std::cout << "Atout : " << atout << std::endl;
                sleep_next_time = true;
            }
            else
            {
                indexJoueur++;
                if (indexJoueur == 4)
                {
                    window.close(); // A FAIRE
                }
            }
            sleep_next_time = true;
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
                        table.changementOrdreJoueur(indexJoueur);
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
    }

    ImGui::End();
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(1);
    sprite.setTexture(*textures[carteRetournee.getCarteG()]);
    sprite.setPosition((window.getSize().x - sprite.getGlobalBounds().width) / 2, (window.getSize().y - sprite.getGlobalBounds().height) / 2);
    window.draw(sprite);
}

void Affichage::jeuDePlisBot(std::vector<sf::Sprite> &cartesG)
{
    afficherMainRetourneeGraphiqueHaut1(table.Mains[1].main.size());
    afficherMainRetourneeGraphiqueDroite1(table.Mains[2].main.size());
    afficherMainRetourneeGraphiqueGauche1(table.Mains[3].main.size());
    afficherMainGraphique(table.Mains[0]);
    afficherCartesSurTable();
    showAtoutPreneur();
    if (showScoresDuringMatch)
    {
        showScores();
    }
    showTrumpTakerBadge();
    showJoueur();
    bool action = false;
    for (int i = 0; i < 4; i++)
    {
        std::cout << "Bot : " << table.Joueurs[i].getEstBot() << std::endl;
    }
    if ((table.Joueurs[indexJoueur].getEstBot() && indexJoueur != 0 && !sleep_next_time))
    {
        jouerCarte(indexJoueur, table.Joueurs[indexJoueur].demanderCarte(indexJoueur, table.CartesSurTable, table.CartesJouees, atout, table.Mains[indexJoueur].main, table.Joueurs, raison) - 1);
        sleep_next_time = true;
        indexJoueur = (indexJoueur + 1) % 4;
    }
    else
    {
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
                        sleep_next_time = true;
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
    }
    if (displayErrors)
    {
        showError(raison);
    }
    if (table.CartesSurTable.size() == 4)
    {
        cartesPrécedentes = MainJoueur(table.CartesSurTable); // on garde les cartes pour les afficher au tour suivant
        cptTour++;
        sleep_next_time = true;
        indexJoueur = table.getGagnant(table.CartesSurTable, atout);
        std::cout << indexJoueur << std::endl;
        int points = table.getPointsSurTable(atout);
        if (indexJoueur == 0 || indexJoueur == 2)
        {
            table.Equipe1.addScore(points);
            if (cptTour == 8)
            {
                table.Equipe1.addScore(10);
            }
        }
        else
        {
            table.Equipe2.addScore(points);
            if (cptTour == 8)
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
        if (cptTour == 8)
        {
            jeu = false;
        }
    }
}