#ifndef JOUEUR_H
#define JOUEUR_H

#include "MainJoueur.h"
#include <string>

/**
 * @class Joueur
 * @brief Represents a player in the game.
 */
class Joueur
{
private:
    MainJoueur main; // The player's hand
    std::string nom; // The player's name
    int rang;        // The player's rank
    bool estBot;     // True if the player is a bot, false otherwise

public:
    /**
     * @brief Default constructor for the Joueur class.
     */
    Joueur();

    /**
     * @brief Constructs a new Joueur object.
     * 
     * @param estBot A boolean value indicating whether the player is a bot or not.
     */
    Joueur(bool estBot);

    /**
     * @brief Gets the player's name.
     * @return The player's name.
     */
    std::string getNom();

    /**
     * @brief Sets the player's name.
     * @param nom The player's name.
     */
    void setNom(std::string nom);

    /**
     * @brief Gets the player's rank.
     * @return The player's rank.
     */
    int getRang() const;

    /**
     * @brief Sets the player's rank.
     * @param rang The player's rank.
     */
    void setRang(int rang);

    /**
     * @brief Gets the player's hand.
     * @return A reference to the player's hand.
     */
    MainJoueur &getMain();

    /**
     * @brief Sets the player's hand.
     * @param main The player's hand.
     */
    void setMain(const MainJoueur &main);

    /**
     * @brief Returns whether the player is a bot or not.
     * 
     * @return true if the player is a bot, false otherwise.
     */
    bool getEstBot();

    /**
     * @brief Sets the flag indicating whether the player is a bot or not.
     * 
     * @param estBot True if the player is a bot, false otherwise.
     */
    void setEstBot(bool estBot);

    /**
     * @brief Displays information about the player.
     */
    void afficherJoueur();

    /**
     * @brief Asks the player to choose a card.
     * @return The index of the chosen card.
     */
    int demanderCarte(std::vector<Carte> CartesSurTable, Couleur atout, std::vector<Carte> mainJoueur, std::string &raison);

    /**
     * @brief Displays the player's hand.
     */
    void afficherMain();

    /**
     * Makes a decision for the bot to take or not to take the bid.
     * 
     * @param CarteAtout The trump card.
     * @param mainBot The bot's hand of cards.
     * @param tour2 Indicates if it is the second round of bidding.
     * @return A pair containing the decision (0 for not taking, 1 for taking) and the chosen trump suit.
     */
    std::pair<int, Couleur> botPrise(Carte CarteAtout, std::vector<Carte> mainBot,bool tour2);

    int botAction(std::vector<Carte> CartesSurTable, Couleur atout, std::vector<Carte> mainJoueur, std::string &raison);
};

#endif