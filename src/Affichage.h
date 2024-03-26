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
    std::map<Couleur, sf::Texture> texturesCouleurs;
    std::vector<sf::Sprite> cartesG;
    bool action = false;

public:
    void init();
    void jeu();
    void menuLoop(bool &menu, bool &prise);
    void jeuLoop(bool &prise, bool &jeu, int &indexJoueur, bool &premierTour);
    sf::Font loadFont();
    void afficherMainGraphique(MainJoueur main);
    void afficherCartePriseGraphique(bool &prise, bool &jeu, int &indexJoueur, bool &premierTour);
    void afficherMainRetourneeGraphiqueHaut1(int nbCartes);
    void afficherMainRetourneeGraphiqueDroite1(int nbCartes);
    void afficherMainRetourneeGraphiqueGauche1(int nbCartes);
    void animDistribution(bool &prise, bool &jeu, int &indexJoueur, bool &premierTour);

    void jeuDePlis(int &indexJoueur, std::vector<sf::Sprite> &cartesG, std::vector<Carte> &cartes);
    void showAtoutPreneur(int indexJoueur);
    void afficherCartesSurTable();
    void jouerCarte(int indexJoueur, int indexCarte);
};

#endif // AFFICHAGE_H