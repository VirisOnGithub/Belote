#include "Table.h"

Table::Table()
{
    nbPlis = 0;
    AllCards = PaquetDeCarte();
}

void Table::setJoueurs(std::vector<Joueur> j)
{
    Joueurs = j;
}

void Table::setEquipes(Equipe e1, Equipe e2)
{
    Equipe1 = e1;
    Equipe2 = e2;
}

void Table::setAllCards(PaquetDeCarte p)
{
    AllCards = p;
}

void Table::setNbPlis(int n)
{
    nbPlis = n;
}

void Table::setCartesSurTable(std::vector<Carte> c)
{
    CartesSurTable = c;
}

void Table::setCartesJouees(std::vector<Carte> c)
{
    CartesJouees = c;
}

std::vector<Carte> Table::getCartesSurTable()
{
    return CartesSurTable;
}

std::vector<Carte> Table::getCartesJouees()
{
    return CartesJouees;
}

int Table::getNbPlis()
{
    return nbPlis;
}

PaquetDeCarte Table::getAllCards()
{
    return AllCards;
}

std::vector<Joueur> Table::getJoueurs()
{
    return Joueurs;
}

Equipe Table::getEquipe1()
{
    return Equipe1;
}

Equipe Table::getEquipe2()
{
    return Equipe2;
}

void Table::setMains(std::vector<MainJoueur> m)
{
    Mains = m;
}

std::vector<MainJoueur> Table::getMains()
{
    return Mains;
}

void Table::Pour4Joueurs(PaquetDeCarte p, std::vector<MainJoueur> &mains)
{
    for (int i = 0; i < 4; i++)
    {
        MainJoueur main;
        for (int j = 0; j < 8; j++)
        {
            main = p.getCarteDansPaquet(i * 8 + j);
        }
        main.trierMain();
        mains.push_back(main);
    }
}

void Table::coupe(PaquetDeCarte &p)
{
    int n = rand() % 32;
    for (int i = 0; i < n; i++)
    {
        p.getCarteDansPaquet(0);
    }
    
}