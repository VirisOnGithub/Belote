#include <iostream>
#include "PaquetDeCarte.h"
#include "Table.h"
#include "MainJoueur.h"

int main()
{
    Table table;
    PaquetDeCarte paquet;
    table.distribuer(paquet);
    // table.afficherMains();
    return 0;
}