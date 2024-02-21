#include <iostream>
#include "Table.h"
#include "MainJoueur.h"

int main()
{
    srand(time(NULL));
    Table table;
    std::vector<MainJoueur> mains;
    MainJoueur::Pour4Joueurs(table.getAllCards(), mains);
    for (int i = 0; i < 4; i++)
    {
        mains[i].afficherMain();
        std::cout << std::endl;
    }
}