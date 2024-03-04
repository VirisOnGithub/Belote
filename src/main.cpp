#include <iostream>
#include "PaquetDeCarte.h"
#include "Table.h"
#include "MainJoueur.h"

int main()
{
    PaquetDeCarte paquet;
    paquet.afficherPaquet();
    std::cout << std::endl;
    paquet.melanger();
    paquet.afficherPaquet();
    return 0;
}