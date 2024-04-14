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
    bool aPris;      // True if the player takes the card in the middle

public:
    /**
     * @brief Default constructor for the Joueur class.
     */
    Joueur();

    /**
     * @brief Constructs a new Joueur object.
     * 
     * @param estBot A boolean value indicating whether the player is a bot or not.
     * @param rang The player's rank.
     */
    Joueur(bool estBot,int rang);

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
    bool getEstBot() const;

    /**
     * @brief Sets the flag indicating whether the player is a bot or not.
     * 
     * @param estBot True if the player is a bot, false otherwise.
     */
    void setEstBot(bool estBot);

    /**
     * @brief Returns whether the player takes the card in the middle.
     * 
     * @return true if the player takes the card in the middle, false otherwise.
     */    
    bool getAPris() const;

    /**
     * @brief Sets the flag indicating whether the player takes the card in the middle.
     * 
     * @param aPris True if the player takes the card in the middle, false otherwise.
     */
    void setAPris(bool aPris);

    /**
     * @brief Displays information about the player.
     */
    void afficherJoueur();

    /**
     * @brief Asks the player to choose a card.
     * @return The index of the chosen card.
     * 
     * @param indice The index of the player.
     * @param CartesSurTable The cards currently on the table.
     * @param cartesJouees The cards played so far.
     * @param atout The trump suit.
     * @param mainJoueur The player's hand.
     * @param Joueurs The players in the game.
     * @param raison The reason for the decision.
     * 
     */
    int demanderCarte(int indice,std::vector<Carte> CartesSurTable,std::vector<Carte> cartesJouees, Couleur atout, std::vector<Carte> mainJoueur,std::vector<Joueur> Joueurs, std::string &raison);

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

    /**
     * Makes a decision for the bot to play a card.
     * 
     * @param indice The index of the player.
     * @param CartesSurTable The cards currently on the table.
     * @param cartesJouees The cards played so far.
     * @param atout The trump suit.
     * @param mainJoueur The player's hand.
     * @param Joueurs The players in the game.
     * @param raison The reason for the decision.
     * @return The index of the chosen card.
     */
    int botAction(int indice,std::vector<Carte> CartesSurTable,std::vector<Carte> cartesJouees, Couleur atout, std::vector<Carte> mainJoueur,std::vector<Joueur> Joueurs, std::string &raison);

    /**
     * Return the index of the weakest non trump card in the player's hand.
     * 
     * @param mainJoueur The player's hand.
     * @param atout The trump suit.
     * @param CartesSurTable The cards currently on the table.
     * @param raison The reason for the decision.
     * @return The index of the chosen card.
     */
    int botCarteFaible(std::vector<Carte> mainJoueur, Couleur atout, std::vector<Carte> CartesSurTable, std::string &raison);

    /**
     * Return the index of the weakest trump card in the player's hand.
     * 
     * @param mainJoueur The player's hand.
     * @param atout The trump suit.
     * @param CartesSurTable The cards currently on the table.
     * @param raison The reason for the decision.
     * @return The index of the chosen card.
     */
    int botCarteFaibleAtout(std::vector<Carte> mainJoueur, Couleur atout, std::vector<Carte> CartesSurTable, std::string &raison);

    /**
     * Return the index of the strongest non trump card in the player's hand.
     * 
     * @param mainJoueur The player's hand.
     * @param atout The trump suit.
     * @param CartesSurTable The cards currently on the table.
     * @param raison The reason for the decision.
     * @return The index of the chosen card.
     */
    int botCarteForte(std::vector<Carte> mainJoueur, Couleur atout, std::vector<Carte> CartesSurTable, std::string &raison);

    /**
     * Return the index of the strongest trump card in the player's hand.
     * 
     * @param mainJoueur The player's hand.
     * @param atout The trump suit.
     * @param CartesSurTable The cards currently on the table.
     * @param raison The reason for the decision.
     * @return The index of the chosen card.
     */
    int botCarteForteAtout(std::vector<Carte> mainJoueur, Couleur atout, std::vector<Carte> CartesSurTable, std::string &raison);

    /**
     * Return the index of the card to play according to the best card on the table.
     * 
     * @param mainJoueur The player's hand.
     * @param atout The trump suit.
     * @param CartesSurTable The cards currently on the table.
     * @param raison The reason for the decision.
     * @param equipeEstMaitre Indicates if the player's team is currently winning the trick.
     * @param carteMaitre The card that is currently winning the trick.
     * @return The index of the chosen card.
     */
    int botCarteMaitre(std::vector<Carte> mainJoueur, Couleur atout, std::vector<Carte> CartesSurTable, std::string &raison, bool const equipeEstMaitre, Carte carteMaitre);
};

#endif