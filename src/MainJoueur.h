#ifndef MAIN_H
#define MAIN_H

#include "Carte.h"
#include <SFML/System/String.hpp>
#include <vector>
#include <SFML/Graphics/Sprite.hpp>

/**
 * @brief The MainJoueur class represents a player's hand in a card game.
 */
class MainJoueur
{
    friend class Table;
    friend class Affichage;

private:
    std::vector<Carte> main; /**< The vector of cards representing the player's hand. */

public:
    /**
     * @brief Default constructor for MainJoueur.
     */
    MainJoueur();

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
     * @brief Getter for the player's hand.
     * @return A reference to the vector of cards representing the player's hand.
     */
    std::vector<Carte> &getMain();

    /**
     * @brief Setter for the player's hand.
     * @param main The new hand to set.
     */
    void setMain(MainJoueur &main);

    /**
     * @brief Adds a card to the player's hand.
     * @param carte The card to add.
     */
    void addCarte(Carte carte);

    /**
     * @brief Displays the player's hand.
     */
    void afficherMain() const;

    /**
     * @brief Sorts the player's hand in ascending order.
     */
    void trierMain();

    /**
     * @brief Plays a card from the player's hand at the specified index.
     * @param index The index of the card to play.
     */
    void jouerCarte(int index);

    // GRAPHIQUE

    /**
     * @brief A container that represents a dynamic array of sf::String objects.
     *
     * This container provides a flexible way to store and manipulate a collection of sf::String objects.
     * It automatically manages the memory allocation and deallocation for the stored objects.
     *
     * @tparam T The type of elements stored in the vector.
     */
    std::vector<sf::String> getCartesG();
};

#endif