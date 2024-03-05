#include <iostream>
#include "PaquetDeCarte.h"
#include "Table.h"
#include "MainJoueur.h"

int main()
{
    Table table;
    PaquetDeCarte paquet;

    paquet.melanger();
    table.setAllCards(paquet);
    table.distribuer(paquet);
    return 0;
}