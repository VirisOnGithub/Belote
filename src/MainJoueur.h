#ifndef MAINJOUEUR_H
#define MAINJOUEUR_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "Carte.h"

/**
 * @class MainJoueur
 * @brief Represents the player's hand in the Belote card game.
 *
 * The MainJoueur class stores a vector of cards representing the player's hand.
 * It provides various methods to manipulate and interact with the player's hand.
 */
class MainJoueur {
    friend class Table;
    friend class Affichage;

private:
    std::vector<Carte> main; /**< The vector of cards representing the player's hand. */
    int rang;               /**< The rank of the player's hand. */

public:
    /**
     * @brief Default constructor for MainJoueur.
     */
    MainJoueur();

    /**
     * @brief Copy constructor for MainJoueur.
     * @param autre The MainJoueur object to copy from.
     */
    MainJoueur(const std::vector<Carte> &autre);

    /**
     * @brief Assignment operator for MainJoueur.
     * @param autre The MainJoueur object to assign from.
     * @return A reference to the assigned MainJoueur object.
     */
    MainJoueur &operator=(const MainJoueur &autre);

    /**
     * @brief Index operator for accessing cards in the player's hand.
     * @param index The index of the card to access.
     * @return The value of the card at the specified index.
     */
    int operator[](int index);

    /**
     * @brief Get the rank of the player's hand.
     * @return The rank of the player's hand.
     */
    int getRang() const;

    /**
     * @brief Set the rank of the player's hand.
     * @param rang The rank to set.
     */
    void setRang(int rang);

    /**
     * @brief Get a reference to the vector of cards representing the player's hand.
     * @return A reference to the vector of cards representing the player's hand.
     */
    std::vector<Carte> &getMain();

    /**
     * @brief Set the player's hand.
     * @param main The new hand to set.
     */
    void setMain(MainJoueur &main);

    /**
     * @brief Add a card to the player's hand.
     * @param carte The card to add.
     */
    void addCarte(Carte carte);

    /**
     * @brief Display the player's hand.
     */
    void afficherMain() const;

    /**
     * @brief Sort the player's hand in ascending order.
     */
    void trierMain();

    /**
     * @brief Play a card from the player's hand at the specified index.
     * @param index The index of the card to play.
     */
    void jouerCarte(int index);

    // GRAPHIQUE

    /**
     * @brief Get a vector of sf::String objects representing the cards in the player's hand.
     * @return A vector of sf::String objects representing the cards in the player's hand.
     */
    std::vector<sf::String> getCartesG();
};

#endif // MAINJOUEUR_H