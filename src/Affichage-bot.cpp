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

void Affichage::animDistributionBot()
{
    afficherMainRetourneeGraphiqueHaut1(5);
    afficherMainRetourneeGraphiqueDroite1(5);
    afficherMainRetourneeGraphiqueGauche1(5);
    if (!table.Mains[indexJoueur].main.empty())
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
                atoutPreneur = indexJoueur;
                atout = priseCouleur.second;
                table.getMains()[indexJoueur].addCarte(carteRetournee);
                table.distribuer2(p);
                table.trierMains();
                std::cout << "Atout : " << atout << std::endl;
            }
            else
            {
                indexJoueur++;
                if (indexJoueur == 4)
                {
                    window.close(); // A FAIRE
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
    }

    ImGui::End();
    ImGui::PopStyleColor(1);
    ImGui::PopStyleVar(1);
    sprite.setTexture(*textures[carteRetournee.getCarteG()]);
    sprite.setPosition((window.getSize().x - sprite.getGlobalBounds().width) / 2, (window.getSize().y - sprite.getGlobalBounds().height) / 2);
    window.draw(sprite);
}