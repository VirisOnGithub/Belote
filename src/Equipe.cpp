#include <iostream>
#include "Equipe.h"

Equipe::Equipe()
{
    Joueur joueur1, joueur2;
    team.push_back(joueur1);
    team.push_back(joueur2);
    score = 0;
}

Equipe::Equipe(Joueur joueur1, Joueur joueur2)
{
    team.push_back(joueur1);
    team.push_back(joueur2);
    score = 0;
}

int Equipe::getScore()
{
    return score;
}

void Equipe::setScore(int score)
{
    this->score = score;
}

void Equipe::afficherEquipe()
{
    for (int i = 0; i < 2; i++)
    {
        team[i].afficherJoueur();
        std::cout << std::endl;
    }
}

void Equipe::addScore(int score)
{
    this->score += score;
}

void Equipe::afficheScore()
{
    std::cout << "Score de l'équipe : " << score << std::endl;
}
