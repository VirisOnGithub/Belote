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
                if (i==7) {
                    Equipe1.addScore(10);
                }
            }
            else
            {
                Equipe2.addScore(points);
                if (i==7) {
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
        indexCarte = Joueurs[joueur.getRang()].demanderCarte() - 1; // -1 car l'index commence à 0
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
        system("clear");
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
    std::sort(Joueurs.begin(), Joueurs.end(), [](const Joueur& a, const Joueur& b) {
        return a.getRang() < b.getRang();
    });
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
    std::cout << "Le gagnant du pli est le joueur " << gagnant+1 << std::endl;
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