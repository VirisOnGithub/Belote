#ifndef CARTE_H
#define CARTE_H

#include <SFML/System/String.hpp>
#include <iostream>
#include <vector>
#include <string.h>
#include "enums.cpp"
#include <SFML/Graphics/Sprite.hpp>

/**
 * @class Carte
 * @brief Represents a playing card.
 *
 * The Carte class stores information about a playing card, including its color, rank, whether it is a trump card, and whether it is accessible.
 * It provides methods to get and set the card's properties, as well as methods to display the card and compare it with other cards.
 */
class Carte
{
private:
    Couleur couleur;      // The color of the card
    ChiffreCarte chiffre; // The rank of the card
    bool atout;           // Indicates whether the card is a trump card
    bool accessible;      // Indicates whether the card is accessible

public:
    /**
     * @brief Default constructor for the Carte class.
     */
    Carte();

    /**
     * @brief Constructor for the Carte class.
     * @param couleur The color of the card.
     * @param chiffre The rank of the card.
     * @param atout True if the card is a trump card, false otherwise.
     * @param accessible True if the card is accessible, false otherwise.
     */
    Carte(ChiffreCarte chiffre, Couleur couleur);

    /**
     * @brief Gets the color of the card.
     * @return The color of the card.
     */
    Couleur getCouleur() const;

    /**
     * @brief Gets the color of the card as a string.
     * @return The color of the card as a string.
     */
    std::string getCouleurStr() const;

    /**
     * @brief Sets the color of the card.
     * @param couleur The color to set.
     */
    void setCouleur(Couleur couleur);

    /**
     * @brief Gets the rank of the card.
     * @return The rank of the card.
     */
    ChiffreCarte getChiffre() const;

    /**
     * @brief Gets the rank of the card as a string.
     * @return The rank of the card as a string.
     */
    std::string getChiffreStr() const;

    /**
     * @brief Sets the rank of the card.
     * @param chiffre The rank to set.
     */
    void setChiffre(ChiffreCarte chiffre);

    /**
     * @brief Checks if the card is a trump card.
     * @return True if the card is a trump card, false otherwise.
     */
    bool isAtout() const;

    /**
     * @brief Sets whether the card is a trump card.
     * @param atout True if the card is a trump card, false otherwise.
     */
    void setAtout(bool atout);

    /**
     * @brief Checks if the card is accessible.
     * @return True if the card is accessible, false otherwise.
     */
    bool isAccessible() const;

    /**
     * @brief Sets whether the card is accessible.
     * @param accessible True if the card is accessible, false otherwise.
     */
    void setAccessible(bool accessible);

    /**
     * @brief Displays the card.
     */
    void afficherCarte() const;

    /**
     * @brief Checks if the card is equal to another card.
     * @param carte1 The card to compare with.
     * @return True if the cards are equal, false otherwise.
     */
    bool operator==(const Carte &carte1) const;

    /**
     * @brief Checks if the card is valid in the current game state.
     * @param CartesSurTable The cards on the table.
     * @param atout The trump color.
     * @param mainJoueur The player's hand.
     * @return True if the card is valid, false otherwise.
     */
    bool estValide(std::vector<Carte> CartesSurTable, Couleur atout, std::vector<Carte> mainJoueur, std::string &raison);

    /**
     * @brief Gets the value of the card as a trump card.
     * @return The value of the card as a trump card.
     */
    ValeurCarteAtout getValeurAtout() const;

    /**
     * @brief Gets the value of the card as a non-trump card.
     * @return The value of the card as a non-trump card.
     */
    ValeurCarteNonAtout getValeurNonAtout() const;

    bool estMeilleure(Carte carte1, Couleur atout) const;

    sf::String getCarteG();
};

#endif