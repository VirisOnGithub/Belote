#include "Table.h"
#include "Joueur.h"
#include "PaquetDeCarte.h"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

#include <cstdlib>
#include <iostream>
#include <string>
#include <algorithm>

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
    for (int i = 0; i < 4; i++)
    {
        Joueur j;
        j.setRang(i);
        Joueurs.push_back(j);
    }
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
    Joueur premierJoueur(true);
    Joueurs[0]=premierJoueur;
    std::cout << "Le premier joueur est un bot : " << Joueurs[0].getEstBot() << std::endl;

    paquet.melanger();
    distribuer1(paquet);
    prise(paquet, atout);
    system("clear");
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
                tourDeJeu(Joueurs[j], atout);
                system("clear");
                attente();
            }
            std::cout << "Fin du pli" << std::endl;
            for (int k = 0; k < 4; k++)
            {
                CartesJouees.push_back(CartesSurTable[k]);
            }
            int gagnant = getGagnant(CartesSurTable, atout);
            int points = getPointsSurTable(atout);
            changementOrdreJoueur(gagnant);
            if (gagnant == 0 || gagnant == 2)
            {
                Equipe1.addScore(points);
                if (i == 7)
                {
                    Equipe1.addScore(10);
                }
            }
            else
            {
                Equipe2.addScore(points);
                if (i == 7)
                {
                    Equipe2.addScore(10);
                }
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
            std::cout << "L'équipe 1 a " << Equipe1.getScore() << " points" << std::endl;
            std::cout << "L'équipe 2 a " << Equipe2.getScore() << " points" << std::endl;
            std::this_thread::sleep_for(std::chrono::seconds(5));
            CartesSurTable = std::vector<Carte>();
            system("clear");
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

void Table::tourDeJeu(Joueur &joueur, Couleur atout)
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
    std::cout << "C'est au tour du joueur " << joueur.getRang() + 1 << std::endl;
    std::string raisonRefus = "";
    do
    {
        std::cout << "Atout: " << nomAtout << std::endl;
        std::cout << raisonRefus << std::endl;
        std::cout << "Cartes sur la table: " << std::endl;
        for (int i = 0; i < CartesSurTable.size(); i++)
        {
            CartesSurTable[i].afficherCarte();
        }
        std::cout << std::endl
                  << std::endl
                  << std::endl;
        Mains[joueur.getRang()].afficherMain();

        indexCarte = Joueurs[joueur.getRang()].demanderCarte(CartesSurTable,atout,Mains[joueur.getRang()].getMain(),raisonRefus) - 1; // -1 car l'index commence à 0
    } while (indexCarte < 0 || indexCarte >= Mains[joueur.getRang()].getMain().size() || !Mains[joueur.getRang()].getMain()[indexCarte].estValide(CartesSurTable, atout, Mains[joueur.getRang()].getMain(), raisonRefus));

    CartesSurTable.push_back(Mains[joueur.getRang()].getMain()[indexCarte]);
    Mains[joueur.getRang()].getMain().erase(Mains[joueur.getRang()].getMain().begin() + indexCarte);
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
        system("clear");
    }
}

void Table::prise(PaquetDeCarte &p, Couleur &atout)
{
    Carte carteRetournee = p.getPremiereCarte();
    bool prise;
    bool tour2 = false;
    std::pair<int, Couleur> priseCouleur;
    for (int i = 0; i < 4; i++)
    {
        Mains[i].trierMain();
        Mains[i].afficherMain();
        std::cout << "La carte retournée est: " << carteRetournee.getChiffreStr() << " de " << carteRetournee.getCouleurStr() << std::endl;
        std::cout << "Joueur " << i + 1 << " voulez-vous prendre cette couleur ? (1 pour oui, 0 pour non)" << std::endl;

        if(Joueurs[i].getEstBot())
        {
            Joueurs[i].getEstBot();
            priseCouleur = Joueurs[i].botPrise(carteRetournee, Mains[i].getMain(),tour2);
            prise = priseCouleur.first;
            std::this_thread::sleep_for(std::chrono::seconds(5));
        }
        else
        {
            std::cin >> prise;
        }

        if (prise)
        {
            atout = carteRetournee.getCouleur();
            Mains[i].addCarte(carteRetournee);
            break;
        }
        system("clear");
        attente();
    }
    if (!prise)
    {
        tour2 = true;
        for (int i = 0; i < 4; i++)
        {
            Mains[i].afficherMain();
            std::cout << "La carte retournée est: " << carteRetournee.getChiffreStr() << " de " << carteRetournee.getCouleurStr() << std::endl;
            std::cout << "Joueur " << i + 1 << " voulez-vous prendre à une autre couleur ? (1 pour oui, 0 pour non)" << std::endl;
            if(Joueurs[i].getEstBot())
            {
                priseCouleur = Joueurs[i].botPrise(carteRetournee, Mains[i].getMain(),tour2);
                prise = priseCouleur.first;
            }
            else
            {
                std::cin >> prise;
            }
            if (prise)
            {
                std::cout << "Quelle couleur voulez-vous prendre ?" << std::endl;
                std::cout << "0. Coeur" << std::endl;
                std::cout << "1. Carreau" << std::endl;
                std::cout << "2. Pique" << std::endl;
                std::cout << "3. Trèfle" << std::endl;
                int couleur;
                if(Joueurs[i].getEstBot())
                {
                    couleur = priseCouleur.second;
                }
                else
                {
                    std::cin >> couleur;
                }
                atout = static_cast<Couleur>(couleur);
                Mains[i].addCarte(carteRetournee);
                break;
            }
            system("clear");
            if (i != 3)
            {
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

void Table::changementOrdreJoueur(int index)
{
    std::sort(Joueurs.begin(), Joueurs.end(), [](const Joueur &a, const Joueur &b)
              { return a.getRang() < b.getRang(); });
    std::rotate(Joueurs.begin(), Joueurs.begin() + index, Joueurs.end());
}

int Table::getGagnant(std::vector<Carte> CartesSurTable, Couleur atout)
{
    int gagnant = 0;
    for (int i = 1; i < CartesSurTable.size(); i++)
    {
        if (CartesSurTable[i].estMeilleure(CartesSurTable[gagnant], atout))
        {
            gagnant = Joueurs[i].getRang();
        }
    }
    std::cout << "Le gagnant du pli est le joueur " << gagnant + 1 << std::endl;
    return gagnant;
}

void Table::attente()
{
    std::cout << "Au tour du joueur suivant, appuyer sur Entrée" << std::endl;
    std::cin.get();
    std::cin.ignore();
    system("clear");
}

unsigned int Table::getPointsSurTable(Couleur atout)
{
    unsigned int points = 0;
    for (int i = 0; i < 4; i++)
    {
        if (CartesSurTable[i].getCouleur() == atout)
        {
            points += CartesSurTable[i].getValeurAtout();
        }
        else
        {
            points += CartesSurTable[i].getValeurNonAtout();
        }
    }
    std::cout << "Points sur la table: " << points << std::endl;
    return points;
}

// void Table::testregression()
// {
//     PaquetDeCarte p;
//     distribuer1(p);
//     for (int i = 0; i < 4; i++)
//     {
//         std::cout << "Main du joueur " << i + 1 << std::endl;
//         Mains[i].afficherMain();
//         std::cout << std::endl;
//     }
//     std::cout << "Test de la prise" << std::endl;
//     Couleur atout = rien;
//     prise(p, atout);
//     std::cout << "Atout: " << atout << std::endl;
//     std::cout << "Test de la distribution 2" << std::endl;
//     distribuer2(p);
//     for (int i = 0; i < 4; i++)
//     {
//         std::cout << "Main du joueur " << i + 1 << std::endl;
//         Mains[i].afficherMain();
//         std::cout << std::endl;
//     }
//     std::cout << "Test du tri des mains" << std::endl;
//     trierMains(Mains);
//     for (int i = 0; i < 4; i++)
//     {
//         std::cout << "Main du joueur " << i + 1 << std::endl;
//         Mains[i].afficherMain();
//         std::cout << std::endl;
//     }
//     std::cout << "Test de la mise des cartes atout" << std::endl;
//     mettreCarteAtout(Mains, atout);
//     for (int i = 0; i < 4; i++)
//     {
//         std::cout << "Main du joueur " << i + 1 << std::endl;
//         Mains[i].afficherMain();
//         std::cout << std::endl;
//     }
//     std::cout << "Test du changement d'ordre des joueurs" << std::endl;
//     changementOrdreJoueur(2);
//     for (int i = 0; i < 4; i++)
//     {
//         std::cout << "Joueur " << Joueurs[i].getRang() + 1 << std::endl;
//     }
//     std::cout << "Test du getGagnant" << std::endl;
//     std::vector<Carte> CartesSurTable = std::vector<Carte>();
//     Carte c1(static_cast<ChiffreCarte>(sept), static_cast<Couleur>(coeur));
//     Carte c2(static_cast<ChiffreCarte>(dame), static_cast<Couleur>(carreau));
//     Carte c3(static_cast<ChiffreCarte>(neuf), static_cast<Couleur>(pique));
//     Carte c4(static_cast<ChiffreCarte>(valet), static_cast<Couleur>(coeur));
//     CartesSurTable.push_back(c1);
//     CartesSurTable.push_back(c2);
//     CartesSurTable.push_back(c3);
//     CartesSurTable.push_back(c4);
//     int gagnant = getGagnant(CartesSurTable, atout);
//     std::cout << "Le gagnant est le joueur " << gagnant + 1 << std::endl;
//     std::cout << "Test de la fonction tourDeJeu" << std::endl;
//     tourDeJeu(Joueurs[0], atout);
//     std::cout << "Test de la fonction coupe" << std::endl;
//     coupe(p);
//     std::cout << "Test de la fonction attente" << std::endl;
//     attente();
//     std::cout << "Test de la fonction jeu" << std::endl;
//     jeu();
//     std::cout << "Test de la fonction getCartesSurTable" << std::endl;
//     std::vector<Carte> c = getCartesSurTable();
//     for (int i = 0; i < c.size(); i++)
//     {
//         c[i].afficherCarte();
//     }
//     std::cout << "Test de la fonction getNbPlis" << std::endl;
//     int n = getNbPlis();
//     std::cout << "Nombre de plis: " << n << std::endl;
//     std::cout << "Test de la fonction getAllCards" << std::endl;
//     PaquetDeCarte p2 = getAllCards();
//     p2.afficherPaquet();
//     std::cout << "Test de la fonction getJoueurs" << std::endl;
//     std::vector<Joueur> j = getJoueurs();
//     for (int i = 0; i < j.size(); i++)
//     {
//         std::cout << "Joueur " << j[i].getRang() + 1 << std::endl;
//     }
//     std::cout << "Test de la fonction getEquipe1" << std::endl;
//     Equipe e1 = getEquipe1();
//     std::cout << "Test de la fonction getEquipe2" << std::endl;
//     Equipe e2 = getEquipe2();
//     std::cout << "Test de la fonction getMains" << std::endl;
//     std::vector<MainJoueur> m = getMains();
//     for (int i = 0; i < m.size(); i++)
//     {
//         std::cout << "Main du joueur " << i + 1 << std::endl;
//         m[i].afficherMain();
//     }
//     std::cout << "Test de la fonction getCartesJouees" << std::endl;
//     std::vector<Carte> g2 = getCartesJouees();
//     for (int i = 0; i < g2.size(); i++)
//     {
//         g2[i].afficherCarte();
//     }
//     std::cout << "Test de la fonction setJoueurs" << std::endl;
// }
