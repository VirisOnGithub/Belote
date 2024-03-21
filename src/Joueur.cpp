#include <iostream>
#include "Joueur.h"

Joueur::Joueur()
{
    nom = "Joueur";
    rang = 0;
    main = MainJoueur();
    estBot = false;
}

Joueur::Joueur(bool estUnBot)
{
    nom = "Joueur";
    rang = 0;
    main = MainJoueur();
    estBot = estUnBot;
}

std::string Joueur::getNom()
{
    return nom;
}

void Joueur::setNom(std::string nom)
{
    this->nom = nom;
}

int Joueur::getRang() const
{
    return rang;
}

void Joueur::setRang(int rang)
{
    this->rang = rang;
}

MainJoueur& Joueur::getMain()
{
    return main;
}

void Joueur::setMain(const MainJoueur& main) {
    this->main = main;
}

bool Joueur::getEstBot()
{
    return estBot;
}

void Joueur::setEstBot(bool estBot)
{
    this->estBot = estBot;
}

void Joueur::afficherJoueur()
{
    std::cout << "Nom: " << nom << std::endl;
    std::cout << "Rang: " << rang << std::endl;
}

int Joueur::demanderCarte()
{
    int index;
    std::cout << "Entrez l'index de la carte que vous voulez jouer: ";
    std::cin >> index;
    return index;
}

void Joueur::afficherMain()
{
    main.afficherMain();
}

std::pair<int,Couleur> Joueur::botPrise(Carte CarteAtout,  std::vector<Carte> mainBot, bool tour2)
{
    bool hasValet = false;
    bool hasNeuf = false;
    bool hasValet2 = false;
    bool hasNeuf2 = false;
    bool hasAs = false;
    Couleur CouleurAtout2=rien;

    for(int i = 0; i < mainBot.size(); i++)
    {
        if(mainBot[i].getCouleur() == CarteAtout.getCouleur())
        {
            if(mainBot[i].getChiffreStr() == "Valet")
            {
                hasValet = true;
            }
            if(mainBot[i].getChiffreStr() == "neuf")
            {
                hasNeuf = true;
            }
            if(mainBot[i].getChiffreStr() == "As" && mainBot[i].getCouleur() != CarteAtout.getCouleur())
            {
                hasAs = true;
            }
            
        }
        else if (mainBot[i].getChiffreStr() == "Valet")
        {
            CouleurAtout2 = mainBot[i].getCouleur();
            hasValet2 = true;
        }
        else if(mainBot[i].getCouleur() == CouleurAtout2 && mainBot[i].getChiffreStr() == "neuf")
        {
            hasNeuf2 = true;
        }
    }   
    if((hasValet && hasNeuf && !tour2) || (hasValet && hasAs && !tour2) || (hasValet2 && hasNeuf2 && tour2))
    {
        if (tour2)
        {
            std::cout << "Le bot a décidé de prendre l'atout " << CouleurAtout2 << std::endl;
            return std::make_pair(1, CouleurAtout2);
        }
        else
        {
            std::cout<<std::endl;
            std::cout << "Le bot a décidé de prendre l'atout "<<std::endl;
            return std::make_pair(1, CouleurAtout2);
        }
    }
    else
    {
        std::cout<<std::endl;
        std::cout<<"Le bot a décidé de ne pas prendre l'atout"<<std::endl;
        return std::make_pair(0 , CouleurAtout2);
    }
}