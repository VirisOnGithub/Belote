#include "Table.h"
#include "PaquetDeCarte.h"

Table::Table()
{
    nbPlis = 0;
    Equipe1 = Equipe();
    Equipe2 = Equipe();
    Mains = std::vector<MainJoueur>();
    CartesSurTable = std::vector<Carte>();
    CartesJouees = std::vector<Carte>();
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

void Table::jeu()
{
    PaquetDeCarte p;
    p.melanger();
    coupe(p);
    for (int i = 0; i < 4; i++)
    {
        MainJoueur m;
        for (int j = 0; j < 8; j++)
        {
            m.addCarte(p.getPremiereCarte());
        }
        Mains.push_back(m);
    }
}

void Table::coupe(PaquetDeCarte &p)
{
    int n = rand() % 32;
    for (int i = 0; i < n; i++)
    {
        p.getPremiereCarte();
    }
}

void Table::tourDeJeu(int joueur, Couleur atout)
{
    int indexCarte;
    do
    {
        Mains[joueur].afficherMain();
        indexCarte = Joueurs[joueur].demanderCarte();
    } while (!Mains[joueur].getMain()[indexCarte].estValide(CartesSurTable, atout, Mains[joueur].getMain()));

    CartesSurTable.push_back(Mains[joueur].getMain()[indexCarte]);
    Mains[joueur].getMain().erase(Mains[joueur].getMain().begin() + indexCarte);
}

void Table::distribuer(PaquetDeCarte p)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 3; j++) {
            Mains[i].addCarte(p.getPremiereCarte());
        }
    }
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 2; j++) {
            Mains[i].addCarte(p.getPremiereCarte());
        }
    }
}