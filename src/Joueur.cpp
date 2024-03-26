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

int Joueur::demanderCarte(std::vector<Carte> CartesSurTable, Couleur atout, std::vector<Carte> mainJoueur, std::string &raison)
{
    int index;
    std::cout << "Entrez l'index de la carte que vous voulez jouer: ";
    if(estBot)
    {
        return botAction(CartesSurTable, atout, mainJoueur, raison);
        std::cout << std::endl;
    }
    else
    {
        std::cin >> index;
        return index;
    }
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
        else if (mainBot[i].getChiffreStr() == "valet")
        {
            CouleurAtout2 = mainBot[i].getCouleur();
            hasValet2 = true;
        }
        else if(mainBot[i].getCouleur() == CouleurAtout2 && mainBot[i].getChiffreStr() == "neuf")
        {
            hasNeuf2 = true;
        }
    }   
    if((hasValet && hasNeuf && !tour2) ||  (CarteAtout.getChiffreStr() == "valet" && !tour2) || (hasValet && hasAs && !tour2) || (hasValet2 && hasNeuf2 && tour2))
    {
        if (tour2)
        {
            std::cout << "Le bot a décidé de prendre l'atout au deuxieme tour" << CouleurAtout2 << std::endl;
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
        if(tour2)
        {
            std::cout<<std::endl;
            std::cout<<"Le bot a décidé de ne pas prendre l'atout au deuxieme tour"<<std::endl;
            return std::make_pair(0 , CouleurAtout2);
        }
        else{
            std::cout<<std::endl;
            std::cout<<"Le bot a décidé de ne pas prendre l'atout"<<std::endl;
            return std::make_pair(0 , CouleurAtout2);
        }
    }
}


int Joueur::botCarteFaible( std::vector<Carte> mainJoueur, Couleur atout, std::vector<Carte> CartesSurTable, std::string &raison)
{
    int indexCarteNonAtoutPlusFaible=0;
        for(int i = 0; i < mainJoueur.size(); i++)
        {
            if(mainJoueur[i].getCouleur() != atout && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison))
            {
                if(mainJoueur[indexCarteNonAtoutPlusFaible].getValeurNonAtout() > mainJoueur[i].getValeurNonAtout())
                {
                    indexCarteNonAtoutPlusFaible = i;
                }
            }
        }
        return indexCarteNonAtoutPlusFaible;
}

int Joueur::botCarteForte( std::vector<Carte> mainJoueur, Couleur atout, std::vector<Carte> CartesSurTable, std::string &raison)
{
    int indexCarteNonAtoutPlusForte=0;
        for(int i = 0; i < mainJoueur.size(); i++)
        {
            if(mainJoueur[i].getCouleur() != atout && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison))
            {
                if(mainJoueur[indexCarteNonAtoutPlusForte].getValeurNonAtout() < mainJoueur[i].getValeurNonAtout())
                {
                    indexCarteNonAtoutPlusForte = i;
                }
            }
        }
        return indexCarteNonAtoutPlusForte;

}

int Joueur::botAction(std::vector<Carte> CartesSurTable, Couleur atout, std::vector<Carte> mainJoueur, std::string &raison)
{
    Carte carteJouee;
    std::vector<Carte> cartesValides;
    
    for(int i = 0; i < mainJoueur.size(); i++)
    {
        if(mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison))
        {
            cartesValides.push_back(mainJoueur[i]);
        }
    }

    if(mainJoueur.size() == 8)
    {
        for(int i = 0; i < mainJoueur.size(); i++)
        {
            if(mainJoueur[i].getChiffreStr() == "valet" && mainJoueur[i].getCouleur() == atout && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison))
            {
                std::cout<<std::endl;
                std::cout<<"Le bot a joué le valet d'atout"<<std::endl;
                return i+1;
            }
            else if(mainJoueur[i].getChiffreStr() == "as" && mainJoueur[i].getCouleur() != atout && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison))
            {
                std::cout<<std::endl;
                std::cout<<"Le bot a joué un as de "<<mainJoueur[i].getCouleurStr()<<std::endl;
                return i+1;
            }
            carteJouee=mainJoueur[i];
        }
        
        // Si le bot n'a ni valet d'atout, ni d'as alors jouer la carte non atout la plus faible
        int index = botCarteFaible(mainJoueur, atout, CartesSurTable, raison);
        carteJouee=mainJoueur[index];
        return index;
    }
    else if(mainJoueur.size() == 7)
    {
        for(int i = 0; i < mainJoueur.size(); i++)
        {
            if(carteJouee.getChiffreStr() == "valet" && carteJouee.getCouleur() == atout && mainJoueur[i].getChiffreStr() == "neuf" && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison))
            {
                std::cout<<std::endl;
                std::cout<<"Le bot a joué le neuf d'atout"<<std::endl;
                return i+1;
            }
            else if(carteJouee.getChiffreStr() == "as" && mainJoueur[i].getCouleur()!= atout && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison) && mainJoueur[i].getChiffreStr() == "as")
            {
                std::cout<<std::endl;
                std::cout<<"Le bot a joué un as de "<<carteJouee.getCouleurStr()<<std::endl;
                return i+1;
            }
        }
        int index = botCarteFaible(mainJoueur, atout, CartesSurTable, raison);
        carteJouee=mainJoueur[index];
        return index;
    }
    else if(mainJoueur.size() == 6)
    {
        return 0;
    }
    else if(mainJoueur.size() == 5)
    {
        return 0;
    }
    else if(mainJoueur.size() == 4)
    {
      return 0;
    }
    else if(mainJoueur.size() == 3)
    {
        return 0;
    }
    else if(mainJoueur.size() == 2)
    {
        return 0;
    }
    else if(mainJoueur.size() == 1)
    {
       return 0;
    }
    return 0;
}
