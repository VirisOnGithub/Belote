#ifndef EQUIPE_H
#define EQUIPE_H

#include "Joueur.h"

class Equipe
{
private:
    std::vector<Joueur> team;
    int score;

public:
    Equipe();
    Equipe(Joueur joueur1, Joueur joueur2);
    int getScore();
    void setScore(int score);
    void afficherEquipe();
    void changerScore(int score);
    void afficheScore();
};

#endif