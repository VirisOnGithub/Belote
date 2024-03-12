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
    bool ajoue;      // Indicates if the player has played a card
    bool aPrisAtout; // Indicates if the player has taken the trump card

public:
    /**
     * @brief Default constructor for the Joueur class.
     */
    Joueur();

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
     * @brief Checks if the player has taken the trump card.
     * @return True if the player has taken the trump card, false otherwise.
     */
    bool getAPrisAtout();

    /**
     * @brief Sets whether the player has taken the trump card.
     * @param aPrisAtout True if the player has taken the trump card, false otherwise.
     */
    void setAPrisAtout(bool aPrisAtout);

    /**
     * @brief Displays information about the player.
     */
    void afficherJoueur();

    /**
     * @brief Asks the player to choose a card.
     * @return The index of the chosen card.
     */
    int demanderCarte();

    /**
     * @brief Displays the player's hand.
     */
    void afficherMain();
};

#endif