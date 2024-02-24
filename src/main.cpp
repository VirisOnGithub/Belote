#include <iostream>
#include "Table.h"
#include "MainJoueur.h"

int main()
{
    srand(time(NULL));
    Table table;
    std::vector<MainJoueur> mains;
    Table::Pour4Joueurs(table.getAllCards(), mains);
    table.setMains(mains);

    for (int i = 0; i < 4; i++)
    {
        std::cout << "Joueur " << i + 1 << std::endl;
        table.getJoueurs()[i].afficherJoueur();
        std::cout << std::endl;
    }
    return 0;
}