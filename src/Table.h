#ifndef TABLE_H
#define TABLE_H

#include <chrono>
#include <thread>

#include "Equipe.h"
#include "Joueur.h"
#include "MainJoueur.h"
#include "PaquetDeCarte.h"

/**
 * @class Table
 * @brief Represents a table for playing the Belote card game.
 *
 * The Table class manages the state of the game, including the cards on the table,
 * the played cards, the number of tricks, the player hands, the deck of cards,
 * the players, and the teams.
 */

class Table
{
private:
    std::vector<Carte> CartesSurTable; /**< The cards currently on the table. */
    std::vector<Carte> CartesJouees;   /**< The cards played during the game. */
    int nbPlis;                        /**< The number of tricks won. */
    std::vector<MainJoueur> Mains;     /**< The hands of the players. */
    PaquetDeCarte AllCards;            /**< The deck of cards. */
    std::vector<Joueur> Joueurs;       /**< The players in the game. */
    Equipe Equipe1, Equipe2;           /**< The two teams in the game. */

public:
    /**
     * @brief Default constructor for the Table class.
     */
    Table();

    /**
     * @brief Sets the players in the game.
     * @param j The vector of players.
     */
    void setJoueurs(std::vector<Joueur> j);

    /**
     * @brief Sets the teams in the game.
     * @param e1 The first team.
     * @param e2 The second team.
     */
    void setEquipes(Equipe e1, Equipe e2);

    /**
     * @brief Sets the deck of cards.
     * @param p The deck of cards.
     */
    void setAllCards(PaquetDeCarte p);

    /**
     * @brief Sets the number of tricks won.
     * @param n The number of tricks won.
     */
    void setNbPlis(int n);

    /**
     * @brief Sets the cards currently on the table.
     * @param c The vector of cards.
     */
    void setCartesSurTable(std::vector<Carte> c);

    /**
     * @brief Sets the cards played during the game.
     * @param c The vector of cards.
     */
    void setCartesJouees(std::vector<Carte> c);

    /**
     * @brief Returns the cards currently on the table.
     * @return The vector of cards.
     */
    std::vector<Carte> getCartesSurTable();

    /**
     * @brief Returns the cards played during the game.
     * @return The vector of cards.
     */
    std::vector<Carte> getCartesJouees();

    /**
     * @brief Returns the number of tricks won.
     * @return The number of tricks won.
     */
    int getNbPlis();

    /**
     * @brief Returns the deck of cards.
     * @return The deck of cards.
     */
    PaquetDeCarte getAllCards();

    /**
     * @brief Returns the players in the game.
     * @return The vector of players.
     */
    std::vector<Joueur> getJoueurs();

    /**
     * @brief Returns the first team.
     * @return The first team.
     */
    Equipe getEquipe1();

    /**
     * @brief Returns the second team.
     * @return The second team.
     */
    Equipe getEquipe2();

    /**
     * @brief Sets the hands of the players.
     * @param m The vector of hands.
     */
    void setMains(std::vector<MainJoueur> m);

    /**
     * @brief Returns the hands of the players.
     * @return The vector of hands.
     */
    std::vector<MainJoueur> getMains();

    /**
     * @brief Displays the players' hands.
     */
    void afficherMains();

    /**
     * @brief Sorts the players' hands.
     * @param m The vector of hands to be sorted.
     */
    void trierMains(std::vector<MainJoueur> &m);

    /**
     * @brief Distributes 3 cards to a player.
     * @param p The deck of cards.
     * @param index The index of the player.
     */
    void distribuerCartes3(PaquetDeCarte &p, int index);

    /**
     * @brief Distributes 2 cards to a player.
     * @param p The deck of cards.
     * @param index The index of the player.
     */
    void distribuerCartes2(PaquetDeCarte &p, int index);

    /**
     * @brief Distributes 1 card to a player.
     * @param p The deck of cards.
     */
    void distribuer1(PaquetDeCarte &p);

    /**
     * @brief Distributes 2 cards to a player.
     * @param p The deck of cards.
     */
    void distribuer2(PaquetDeCarte &p);

    /**
     * @brief Performs the "prise" action in the game.
     * @param p The deck of cards.
     * @param atout The trump suit.
     */
    void prise(PaquetDeCarte &p, Couleur &atout);

    /**
     * @brief Sets the trump suit for a player's hand.
     * @param m The vector of hands.
     * @param atout The trump suit.
     */
    void mettreCarteAtout(std::vector<MainJoueur> &m, Couleur atout);

    /**
     * @brief Changes the order of the players.
     * @param joueurs The vector of players.
     * @param index The index of the player to be moved.
     */
    void changementOrdreJoueur(std::vector<Joueur> &joueurs, int index);

    /**
     * @brief Starts the game.
     */
    void jeu();

    /**
     * @brief Performs a player's turn.
     * @param joueur The index of the player.
     * @param atout The trump suit.
     */
    void tourDeJeu(int joueur, Couleur atout);

    /**
     * @brief Performs the "coupe" action in the game.
     * @param p The deck of cards.
     */
    void coupe(PaquetDeCarte &p);
};

#endif
