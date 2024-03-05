#include <iostream>
#include "PaquetDeCarte.h"
#include "Table.h"
#include "MainJoueur.h"

int main()
{
    Table table;
    PaquetDeCarte paquet;

    paquet.melanger();
    paquet.afficherPaquet();
    std::cout << std::endl;
    std::cout << std::endl;
    table.distribuer(paquet);
    std::cout << "Done" << std::endl;

    table.afficherMains();
    return 0;
}