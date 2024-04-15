#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "Carte.h"
#include "MainJoueur.h"
#include "PaquetDeCarte.h"
#include "Table.h"
#include "imgui-master/imgui.h"
#include <SFML/Audio/Music.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <unordered_map>
#include <memory>
#include <vector>
#include <mutex>

/**
 * @class Affichage
 * @brief The Affichage class represents the graphical interface of the Belote game.
 * 
 * This class handles the game window, fonts, textures, and various game states.
 * It provides methods for initializing the game, starting the main game loop, and displaying game elements.
 * The Affichage class also includes methods for playing cards, showing error messages, and managing game settings.
 */
class Affichage {
private:
    sf::RenderWindow window;                                                                            /**< The game window for rendering graphics. */
    sf::Font font;                                                                                      /**< The font used for displaying text. */
    sf::Text titre;                                                                                     /**< The title text displayed on the game window. */
    sf::Music music;                                                                                    /**< The background music for the game. */
    std::map<sf::String, std::shared_ptr<sf::Texture>> textures;                                        /**< A map of textures used in the game. */
    Table table;                                                                                        /**< The game table where cards are played. */
    PaquetDeCarte p;                                                                                    /**< The deck of cards used in the game. */
    Couleur atout;                                                                                      /**< The trump suit for the current round. */
    Carte carteRetournee;                                                                               /**< The card that is turned face up. */
    sf::Sprite sprite;                                                                                  /**< The sprite used for displaying cards. */
    sf::Texture settingsTexture, crossTexture;                                                          /**< Textures used for displaying game settings. */
    float musicVolume = 0;                                                                              /**< The volume level for game music. */
    std::map<Couleur, sf::Texture> texturesCouleurs;                                                    /**< A map of textures for different card suits. */
    std::vector<sf::Sprite> cartesG;                                                                    /**< The graphical representation of player cards. */
    bool action = false, menu = true, prise = false, jeu = false, premierTour = true, settings = false; /**< Flags for different game states. */
    int indexJoueur = table.Joueurs[0].getRang();                                                       /**< The index of the current player. */
    std::string raison;                                                                                 /**< The reason for an error or game event. */
    int atoutPreneur;                                                                                   /**< The index of the player who chose the trump suit. */
    int cptTour;                                                                                        /**< The current round number. */
    std::mutex mtx;                                                                                     /**< Mutex for thread synchronization. */
    bool displayErrors = true, showScoresDuringMatch = true, showLatestCards = true;                    /**< Flags for game settings. */
    int playingTime = 1;                                                                                /**< Flag for settings. */
    MainJoueur cartesPrécedentes;                                                                       /**< The cards played in the previous round. */

    bool bots = false, sleep_next_time = false;

public:
    /**
     * @brief Initializes the game window, fonts, and textures.
     */
    void init();

    /**
     * @brief Starts the main game loop.
     */
    void mainJeu();

    /**
     * @brief Starts the menu loop.
     */
    void menuLoop();

    /**
     * @brief Starts the game loop.
     */
    void jeuLoop();

    /**
     * @brief Loads the game music.
     */
    void loadMusic();

    /**
     * @brief Loads the game font.
     * @return The loaded font.
     */
    sf::Font loadFont();

    /**
     * @brief Displays the player's hand graphically.
     * @param main The player's hand.
     */
    void afficherMainGraphique(MainJoueur main);

    /**
     * @brief Displays the taken card graphically.
     */
    void afficherCartePriseGraphique();

    /**
     * @brief Displays the taken card graphically for a bot player.
     */
    void afficherCartePriseGraphiqueBot();

    /**
     * @brief Displays the face-down cards of the player at the top position.
     * @param nbCartes The number of face-down cards to display.
     */
    void afficherMainRetourneeGraphiqueHaut1(int nbCartes);

    /**
     * @brief Displays the face-down cards of the player at the right position.
     * @param nbCartes The number of face-down cards to display.
     */
    void afficherMainRetourneeGraphiqueDroite1(int nbCartes);

    /**
     * @brief Displays the face-down cards of the player at the left position.
     * @param nbCartes The number of face-down cards to display.
     */
    void afficherMainRetourneeGraphiqueGauche1(int nbCartes);

    /**
     * @brief Animates the card distribution.
     */
    void animDistribution();

    /**
     * @brief Animates the card distribution for a bot player.
     */
    void animDistributionBot();

    /**
     * @brief Plays the game of plis.
     * @param cartesG The graphical representation of player cards.
     */
    void jeuDePlis(std::vector<sf::Sprite> &cartesG);

    /**
     * @brief Plays the game of plis for a bot player.
     * @param cartesG The graphical representation of player cards.
     */
    void jeuDePlisBot(std::vector<sf::Sprite> &cartesG);

    /**
     * @brief Shows the player who chose the trump suit.
     */
    void showAtoutPreneur();

    /**
     * @brief Displays the cards on the table.
     */
    void afficherCartesSurTable();

    /**
     * @brief Plays a card.
     * @param indexJoueur The index of the player.
     * @param indexCarte The index of the card to play.
     */
    void jouerCarte(int indexJoueur, int indexCarte);

    /**
     * @brief Shows an error message.
     * @param message The error message to display.
     */
    void showError(std::string message);

    /**
     * @brief Shows a badge indicating the player who chose the trump suit.
     */
    void showTrumpTakerBadge();

    /**
     * @brief Shows the game settings.
     */
    void showParameters();

    /**
     * @brief Shows the game scores.
     */
    void showScores();

    /**
     * @brief Shows the current player.
     */
    void showJoueur();

    /**
     * @brief Ends the game.
     */
    void finDePartie();
};

#endif // AFFICHAGE_H