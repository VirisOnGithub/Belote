#ifndef TABLE_H
#define TABLE_H

#include <chrono>
#include <thread>

#include "Equipe.h"
#include "Joueur.h"
#include "MainJoueur.h"
#include "PaquetDeCarte.h"

class Table
{
private:
    std::vector<Carte> CartesSurTable;
    std::vector<Carte> CartesJouees;
    int nbPlis;
    std::vector<MainJoueur> Mains;
    PaquetDeCarte AllCards;
    std::vector<Joueur> Joueurs;
    Equipe Equipe1, Equipe2;

public:
    Table();
    void setJoueurs(std::vector<Joueur> j);
    void setEquipes(Equipe e1, Equipe e2);
    void setAllCards(PaquetDeCarte p);
    void setNbPlis(int n);
    void setCartesSurTable(std::vector<Carte> c);
    void setCartesJouees(std::vector<Carte> c);
    std::vector<Carte> getCartesSurTable();
    std::vector<Carte> getCartesJouees();
    int getNbPlis();
    PaquetDeCarte getAllCards();
    std::vector<Joueur> getJoueurs();
    Equipe getEquipe1();
    Equipe getEquipe2();
    void setMains(std::vector<MainJoueur> m);
    std::vector<MainJoueur> getMains();
    void afficherMains();
    void trierMains(std::vector<MainJoueur> &m);
    void distribuerCartes3(PaquetDeCarte &p, int index);
    void distribuerCartes2(PaquetDeCarte &p, int index);
    void distribuer1(PaquetDeCarte &p);
    void distribuer2(PaquetDeCarte &p);
    void prise(PaquetDeCarte &p, Couleur &atout);
    void mettreCarteAtout(std::vector<MainJoueur> &m, Couleur atout);

    void jeu();

    void tourDeJeu(int joueur, Couleur atout);

    void coupe(PaquetDeCarte &p);
};

#endif
