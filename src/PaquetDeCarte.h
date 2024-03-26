#ifndef PAQUETDECARTE_H
#define PAQUETDECARTE_H
#include "Carte.h"
#include "Joueur.h"
#include <vector>

/**
 * @class PaquetDeCarte
 * @brief Represents a deck of cards.
 */
class PaquetDeCarte
{
private:
    std::vector<Carte> paquet;

public:
    /**
     * Default constructor for PaquetDeCarte.
     */
    PaquetDeCarte();

    /**
     * Assignment operator overload for PaquetDeCarte.
     * @param autre The other PaquetDeCarte object to assign from.
     * @return The assigned PaquetDeCarte object.
     */
    int operator=(const PaquetDeCarte &autre);

    /**
     * Subscript operator overload for accessing cards in the deck.
     * @param index The index of the card to access.
     * @return The card at the specified index.
     */
    int operator[](int index);

    /**
     * Get the current deck of cards.
     * @return The current deck of cards.
     */
    std::vector<Carte> getPaquet();

    /**
     * Set the deck of cards.
     * @param paquet The new deck of cards.
     */
    void setPaquet(PaquetDeCarte paquet);

    /**
     * Print the deck of cards.
     */
    void afficherPaquet() const;

    /**
     * Shuffle the deck of cards.
     */
    void melanger();

    /**
     * Get the first card from the deck.
     * @return The first card from the deck.
     */
    Carte getPremiereCarte();
};

#endif