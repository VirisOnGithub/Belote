#include <iostream>
#include "Main.h"

int main()
{
    srand(time(NULL));
    Main main;
    main.afficherMain();
    main.trierMain();
    std::cout << std::endl;
    main.afficherMain();
    return 0;
}