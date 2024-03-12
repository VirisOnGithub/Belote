#ifndef EQUIPE_H
#define EQUIPE_H

#include "Joueur.h"

/**
 * @class Equipe
 * @brief Represents a team in a game.
 *
 * The `Equipe` class stores information about a team, including the players and their score.
 */
class Equipe
{
private:
    std::vector<Joueur> team; // The players in the team
    unsigned int score;                // The score of the team

public:
    /**
     * @brief Default constructor for the `Equipe` class.
     */
    Equipe();

    /**
     * @brief Constructor for the `Equipe` class.
     * @param joueur1 The first player in the team.
     * @param joueur2 The second player in the team.
     */
    Equipe(Joueur joueur1, Joueur joueur2);

    /**
     * @brief Get the score of the team.
     * @return The score of the team.
     */
    int getScore();

    /**
     * @brief Set the score of the team.
     * @param score The new score of the team.
     */
    void setScore(int score);

    /**
     * @brief Display the information about the team.
     */
    void afficherEquipe();

    /**
     * @brief Change the score of the team by a given amount.
     * @param score The amount by which to change the score.
     */
    void addScore(int score);

    /**
     * @brief Display the score of the team.
     */
    void afficheScore();
};

#endif