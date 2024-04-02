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
#include <vector>

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
    sf::Texture settingsTexture, crossTexture;
    float musicVolume = 50;
    std::map<Couleur, sf::Texture> texturesCouleurs;
    std::vector<sf::Sprite> cartesG;
    bool action = false, menu = true, prise = false, jeu = false, premierTour = true, settings = false;
    int indexJoueur = 0;
    std::string raison;
    int atoutPreneur;

public:
    void init();
    void mainJeu();
    void menuLoop();
    void jeuLoop();
    sf::Font loadFont();
    void afficherMainGraphique(MainJoueur main);
    void afficherCartePriseGraphique();
    void afficherMainRetourneeGraphiqueHaut1(int nbCartes);
    void afficherMainRetourneeGraphiqueDroite1(int nbCartes);
    void afficherMainRetourneeGraphiqueGauche1(int nbCartes);
    void animDistribution();

    void jeuDePlis(std::vector<sf::Sprite> &cartesG);
    void showAtoutPreneur();
    void afficherCartesSurTable();
    void jouerCarte(int indexJoueur, int indexCarte);
    void showError(std::string message);
    void showTrumpTakerBadge();
    void showParameters();
};

#endif // AFFICHAGE_H