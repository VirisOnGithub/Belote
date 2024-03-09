#include "Table.h"
#include "PaquetDeCarte.h"
#include <cstdlib>
#include <string>

Table::Table()
{
    nbPlis = 0;
    Equipe1 = Equipe();
    Equipe2 = Equipe();
    Mains = std::vector<MainJoueur>();
    for (int i = 0; i < 4; i++)
    {
        MainJoueur m;
        Mains.push_back(m);
    }
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
    PaquetDeCarte paquet;
    Couleur atout = rien;
    paquet.melanger();
    distribuer1(paquet);
    prise(paquet, atout);
    std::cout << "clear here" << std::endl;
    if (atout != rien)
    {
        distribuer2(paquet);
        trierMains(Mains);
        afficherMains();
        mettreCarteAtout(Mains, atout);
        for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 4; j++)
            {
                tourDeJeu(j, atout);
                std::cout << "clear here" << std::endl;
                attente();
            }
            std::cout << "Fin du pli" << std::endl;
            for (int k = 0; k < 4; k++)
            {
                CartesJouees.push_back(CartesSurTable[k]);
            }
            CartesSurTable = std::vector<Carte>();
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "clear here" << std::endl;
        }
    }
    else
    {
        std::cout << "Aucune couleur n'a été prise, la partie est annulée" << std::endl;
    }
}

void Table::trierMains(std::vector<MainJoueur> &m)
{
    for (int i = 0; i < 4; i++)
    {
        Mains[i].trierMain();
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
    std::string nomAtout;
    switch (atout)
    {
    case 0:
        nomAtout = "coeur";
        break;
    case 1:
        nomAtout = "carreau";
        break;
    case 2:
        nomAtout = "pique";
        break;
    case 3:
        nomAtout = "trèfle";
        break;
    default:
        break;
    }
    std::cout << "C'est au tour du joueur " << joueur + 1 << std::endl;
    std::string raisonRefus="";
    do
    {
        std::cout << "Atout: " << nomAtout << std::endl;
        std::cout << raisonRefus << std::endl;
        std::cout << "Cartes sur la table: " << std::endl;
        for (int i = 0; i < CartesSurTable.size(); i++)
        {
            CartesSurTable[i].afficherCarte();
        }
        std::cout << std::endl << std::endl << std::endl;
        Mains[joueur].afficherMain();
        indexCarte = Joueurs[joueur].demanderCarte()-1; // -1 car l'index commence à 0
    } while (indexCarte < 0 || indexCarte >= Mains[joueur].getMain().size() || !Mains[joueur].getMain()[indexCarte].estValide(CartesSurTable, atout, Mains[joueur].getMain(), raisonRefus));

    CartesSurTable.push_back(Mains[joueur].getMain()[indexCarte]);
    Mains[joueur].getMain().erase(Mains[joueur].getMain().begin() + indexCarte);
    std::cout << std::endl;
}

void Table::distribuerCartes3(PaquetDeCarte &p, int index)
{
    for (int j = 0; j < 3; j++)
    {
        Mains[index].addCarte(p.getPremiereCarte());
    }
}

void Table::distribuerCartes2(PaquetDeCarte &p, int index)
{

    for (int j = 0; j < 2; j++)
    {
        Mains[index].addCarte(p.getPremiereCarte());
    }
}

void Table::distribuer1(PaquetDeCarte &p)
{
    for (int i = 0; i < 4; i++)
    {
        distribuerCartes3(p, i);
    }
    for (int i = 0; i < 4; i++)
    {
        distribuerCartes2(p, i);
    }
}

void Table::distribuer2(PaquetDeCarte &p)
{

    for (int i = 0; i < 4; i++)
    {
        if (Mains[i].getMain().size() == 6)
        {
            distribuerCartes2(p, i);
        }
        else
        {
            distribuerCartes3(p, i);
        }
    }
}

void Table::afficherMains()
{
    for (int i = 0; i < 4; i++)
    {
        std::cout << "Main du joueur " << i + 1 << std::endl;
        std::cout << std::endl;
        Mains[i].afficherMain();
        std::cout << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        std::cout << "clear here" << std::endl;
    }
}

void Table::prise(PaquetDeCarte &p, Couleur &atout)
{
    Carte carteRetournee = p.getPremiereCarte();
    bool prise;
    for (int i = 0; i < 4; i++)
    {
        Mains[i].trierMain();
        Mains[i].afficherMain();
        std::cout << "La carte retournée est: " << carteRetournee.getChiffreStr() << " de " << carteRetournee.getCouleurStr() << std::endl;
        std::cout << "Joueur " << i + 1 << " voulez-vous prendre cette couleur ? (1 pour oui, 0 pour non)" << std::endl;

        std::cin >> prise;

        if (prise)
        {
            atout = carteRetournee.getCouleur();
            Mains[i].addCarte(carteRetournee);
            break;
        }
        std::cout << "clear here" << std::endl;
        attente();
    }
    if (!prise)
    {
        for (int i = 0; i < 4; i++)
        {
            Mains[i].afficherMain();
            std::cout << "La carte retournée est: " << carteRetournee.getChiffreStr() << " de " << carteRetournee.getCouleurStr() << std::endl;
            std::cout << "Joueur " << i + 1 << " voulez-vous prendre à une autre couleur ? (1 pour oui, 0 pour non)" << std::endl;
            std::cin >> prise;
            if (prise)
            {
                std::cout << "Quelle couleur voulez-vous prendre ?" << std::endl;
                std::cout << "0. Coeur" << std::endl;
                std::cout << "1. Carreau" << std::endl;
                std::cout << "2. Pique" << std::endl;
                std::cout << "3. Trèfle" << std::endl;
                int couleur;
                std::cin >> couleur;
                atout = static_cast<Couleur>(couleur);
                Mains[i].addCarte(carteRetournee);
                break;
            }
            std::cout << "clear here" << std::endl;
            if (i!=3){
                attente();
            }
        }
    }
}

void Table::mettreCarteAtout(std::vector<MainJoueur> &m, Couleur atout)
{
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < m[i].getMain().size(); j++)
        {
            if (m[i].getMain()[j].getCouleur() == atout)
            {
                m[i].getMain()[j].setAtout(true);
            }
        }
    }
}

void Table::changementOrdreJoueur(std::vector<Joueur> &joueurs, int index)
{
    std::vector<Joueur> temp;
    for (int i = index; i < 4; i++)
    {
        temp.push_back(joueurs[i]);
    }
    for (int i = 0; i < index; i++)
    {
        temp.push_back(joueurs[i]);
    }
    joueurs = temp;
}

int getGagnant(std::vector<Carte> CartesSurTable, Couleur atout)
{
    int gagnant = 0;
    for (int i = 1; i < 4; i++)
    {
        if (CartesSurTable[i].getCouleur() == atout && CartesSurTable[i].getValeurAtout() > CartesSurTable[gagnant].getValeurAtout())
        {
            gagnant = i;
        }
        else if (CartesSurTable[i].getCouleur() == atout && CartesSurTable[i].getValeurAtout() == CartesSurTable[gagnant].getValeurAtout())
        {
            if (CartesSurTable[i].getChiffre() < CartesSurTable[gagnant].getChiffre())
            {
                gagnant = i;
            }
        }
        else if (CartesSurTable[i].getCouleur() != atout && CartesSurTable[i].getValeurNonAtout() > CartesSurTable[gagnant].getValeurNonAtout() && CartesSurTable[i].getCouleur() == CartesSurTable[0].getCouleur())
        {
            gagnant = i;
        }
        else if (CartesSurTable[i].getCouleur() != atout && CartesSurTable[i].getValeurNonAtout() == CartesSurTable[gagnant].getValeurNonAtout() && CartesSurTable[i].getCouleur() == CartesSurTable[0].getCouleur())
        {
            if (CartesSurTable[i].getChiffre() < CartesSurTable[gagnant].getChiffre())
            {
                gagnant = i;
            }
        }
    }
    return gagnant;
}

void Table::attente()
{
    std::cout << "Au tour du joueur suivant, appuyer sur une touche" << std::endl;
    std::cin.get();
    std::cin.ignore();
    std::cout << "clear here" << std::endl;
}