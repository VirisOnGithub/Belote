#include <iostream>
#include "Table.h"
#include "Main.h"

int main()
{
    srand(time(NULL));
    Table table;
    std::vector<Main> mains;
    Pour4Joueurs(table.getAllCards(), mains);
}