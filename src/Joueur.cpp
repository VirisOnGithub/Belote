#include <iostream>
#include "Joueur.h"


Joueur::Joueur()
{
    nom = "Joueur";
    rang = 0;
    main = MainJoueur();
    estBot = false;
    aPris = false;
}

Joueur::Joueur(bool estUnBot, int unRang)
{
    nom = "Joueur";
    rang = unRang;
    main = MainJoueur();
    estBot = estUnBot;
    aPris = false;
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

bool Joueur::getEstBot() const
{
    return estBot;
}

void Joueur::setEstBot(bool estBot)
{
    this->estBot = estBot;
}

bool Joueur::getAPris() const
{
    return aPris;
}

void Joueur::setAPris(bool aPris)
{
    this->aPris = aPris;
}

void Joueur::afficherJoueur()
{
    std::cout << "Nom: " << nom << std::endl;
    std::cout << "Rang: " << rang << std::endl;
}

int Joueur::demanderCarte(int indice,std::vector<Carte> CartesSurTable, Couleur atout, std::vector<Carte> mainJoueur,std::vector<Joueur> Joueurs, std::string &raison)
{
    int index;
    std::cout << "Entrez l'index de la carte que vous voulez jouer: ";
    if(estBot)
    {
        return botAction(indice,CartesSurTable, atout, mainJoueur, Joueurs, raison);
        std::cout << std::endl << std::endl;
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
    int indexCartePlusFaible = -1;
    bool hasAtout = false;
    bool hasCouleur = false;
    for(int i = 0; i < mainJoueur.size();i++)
    {
        if(mainJoueur[i].getCouleur() == atout)
        {
            hasAtout = true;
        }
        if(CartesSurTable.size() == 1)
        {
            if(mainJoueur[i].getCouleur() == CartesSurTable[0].getCouleur())
            {
                hasCouleur = true;
            }
        }
    }
    for(int i = 0; i < mainJoueur.size(); i++)
    {
        if(mainJoueur[i].getCouleur() != atout && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison))
        {
            if(indexCartePlusFaible == -1 || mainJoueur[indexCartePlusFaible].getValeurNonAtout() > mainJoueur[i].getValeurNonAtout())
            {
                indexCartePlusFaible = i;
            }
        }
    }
    std::cout<<std::endl<<"CarteFaible index "<<indexCartePlusFaible+1<<std::endl;
    if(hasAtout && indexCartePlusFaible == -1)
    {
        return botCarteForteAtout(mainJoueur,atout,CartesSurTable,raison);
    }
    else
    {
        return indexCartePlusFaible+1;
    }
    
}

int Joueur::botCarteFaibleAtout(std::vector<Carte> mainJoueur, Couleur atout, std::vector<Carte> CartesSurTable, std::string &raison)
{
    int indexCartePlusFaibleAtout = -1;
    for(int i = 0; i < mainJoueur.size(); i++)
    {
        if(mainJoueur[i].getCouleur() == atout && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison))
        {
            if(indexCartePlusFaibleAtout == -1 || mainJoueur[indexCartePlusFaibleAtout].getValeurAtout() > mainJoueur[i].getValeurAtout())
            {
                indexCartePlusFaibleAtout = i;
            }
        }
    }
    std::cout<<std::endl<<"CarteFaibleAtout index "<<indexCartePlusFaibleAtout+1<<std::endl;
    return indexCartePlusFaibleAtout+1;
}

int Joueur::botCarteForte( std::vector<Carte> mainJoueur, Couleur atout, std::vector<Carte> CartesSurTable, std::string &raison)
{
    int indexCarteNonAtoutPlusForte = -1;
    bool hasAtout = false;
    bool hasCouleur = false;
    for(int i = 0; i < mainJoueur.size();i++)
    {
        if(mainJoueur[i].getCouleur() == atout)
        {
            hasAtout = true;
        }
        if(CartesSurTable.size() == 1)
        {
            if(mainJoueur[i].getCouleur() == CartesSurTable[0].getCouleur())
            {
                hasCouleur = true;
            }
        }
    }
    for(int i = 0; i < mainJoueur.size(); i++)
    {
        if(mainJoueur[i].getCouleur() != atout && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison) && hasCouleur)
        {
            if(indexCarteNonAtoutPlusForte == -1 || mainJoueur[indexCarteNonAtoutPlusForte].getValeurNonAtout() < mainJoueur[i].getValeurNonAtout() && hasCouleur)
            {
                indexCarteNonAtoutPlusForte = i;
            }
        }
    }
    if(hasAtout && indexCarteNonAtoutPlusForte == -1)
    {
        return botCarteForteAtout(mainJoueur,atout,CartesSurTable,raison);
    }
    else
    {
        std::cout<<std::endl<<"je suis dans botCarteForte index "<<indexCarteNonAtoutPlusForte<<std::endl;
        return indexCarteNonAtoutPlusForte+1;
    }
    

}

int Joueur::botCarteForteAtout(std::vector<Carte> mainJoueur, Couleur atout, std::vector<Carte> CartesSurTable, std::string &raison)
{
    int indexCarteAtoutPlusForte=-1;
    for(int i = 0; i < mainJoueur.size(); i++)
    {
        if(mainJoueur[i].getCouleur() == atout && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison))
        {
            if(indexCarteAtoutPlusForte == -1 || mainJoueur[indexCarteAtoutPlusForte].getValeurAtout() < mainJoueur[i].getValeurAtout())
            {
                indexCarteAtoutPlusForte = i;
            }
        }
    }
    std::cout<<std::endl<<"CarteForteAtout index "<<indexCarteAtoutPlusForte+1<<std::endl;
    return indexCarteAtoutPlusForte+1;

}

int Joueur::botCarteRandom(std::vector<Carte> mainJoueur, Couleur atout, std::vector<Carte> CartesSurTable, std::string &raison)
{
    for(int i = 0; i < mainJoueur.size(); i++)
    {
        if(mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison))
        {
            return i+1;
        }
    }

    throw std::runtime_error("Aucune carte valide trouvee"); // Pas de carte valide
}

int Joueur::botAction(int indice,std::vector<Carte> CartesSurTable, Couleur atout, std::vector<Carte> mainJoueur,std::vector<Joueur> Joueurs, std::string &raison)
{
    Carte carteJouee = mainJoueur[0];
    Carte carteMaitre;
    std::vector<Carte> cartesValides;
    bool EquipeAPris = false;
    bool equipeEstMaitre = false;
    int indexMaitre = 0;
    int index = 0;

    if(Joueurs[(indice+2) % 4].getAPris() == true)
    {
        EquipeAPris = true;
    }

    if(CartesSurTable.size() == 1)
    {
        carteMaitre = CartesSurTable[0];
        for(int i = 0; i < CartesSurTable.size();i++)
        {
            if(carteMaitre.getValeurNonAtout() < CartesSurTable[i].getValeurNonAtout())
            {
                carteMaitre = CartesSurTable[i];
                indexMaitre = i;
            }
            else
            {
                carteMaitre = CartesSurTable[0];
                indexMaitre = 0;
            }
            if(i >= 1 && indexMaitre == i-1)
            {
                equipeEstMaitre = true;
                break;
            }
            
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
                carteJouee=mainJoueur[i];
                return i+1;
            }
            else if(EquipeAPris && CartesSurTable.size() == 0)
            {
                std::cout<<std::endl;
                index = botCarteFaibleAtout(mainJoueur, atout, CartesSurTable, raison);
                carteJouee=mainJoueur[index];
                return index;
            }
        }
        
        for(int i = 0; i < mainJoueur.size(); i++)
        {  
            if(mainJoueur[i].getChiffreStr() == "as" && mainJoueur[i].getCouleur() != atout && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison))
            {
                std::cout<<std::endl;
                std::cout<<"Le bot a joué un as de "<<mainJoueur[i].getCouleurStr()<<std::endl;
                carteJouee=mainJoueur[i];
                return i+1;
            }
        }
        
        // Si le bot n'a ni valet d'atout, ni d'as alors jouer la carte non atout la plus faible
        if(equipeEstMaitre && carteMaitre.getCouleur() == atout)
        {
            index = botCarteForteAtout(mainJoueur, atout, CartesSurTable, raison);
            carteJouee=mainJoueur[index];
            return index;
        }
        else if(equipeEstMaitre && carteMaitre.getCouleur() != atout)
        {
            index = botCarteForte(mainJoueur, atout, CartesSurTable, raison);
            carteJouee=mainJoueur[index];
            return index;
        }
        else if(carteMaitre.getCouleur() == atout)
        {
            index = botCarteFaibleAtout(mainJoueur, atout, CartesSurTable, raison);
            carteJouee=mainJoueur[index];
            return index;
        }
        else
        {
            index = botCarteFaible(mainJoueur, atout, CartesSurTable, raison);
            carteJouee=mainJoueur[index];
            return index;
        }
    }

    else if(mainJoueur.size() == 7)
    {
        for(int i = 0; i < mainJoueur.size(); i++)
        {
            if(carteJouee.getChiffreStr() == "valet" && carteJouee.getCouleur() == atout)
            {
                if(mainJoueur[i].getChiffreStr() == "neuf" && mainJoueur[i].getCouleur() == atout && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison))
                {
                    std::cout<<std::endl;
                    std::cout<<"Le bot a joué le neuf d'atout"<<std::endl;
                    carteJouee=mainJoueur[i];
                    return i+1;
                }
            }
            else if(EquipeAPris && CartesSurTable.size() == 0)
            {
                index = botCarteFaibleAtout(mainJoueur, atout, CartesSurTable, raison);
                carteJouee=mainJoueur[index];
                return index;
            }
        }
        for(int i = 0; i < mainJoueur.size(); i++)
        {
            if(carteJouee.getChiffreStr() == "as" && mainJoueur[i].getCouleur()!= atout && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison) && mainJoueur[i].getChiffreStr() == "as")
            {
                std::cout<<std::endl;
                carteJouee=mainJoueur[i];
                std::cout<<"Le bot a joué un as de "<<carteJouee.getCouleurStr()<<std::endl;
                return i+1;
            }
        }
        if(equipeEstMaitre && carteMaitre.getCouleur() == atout)
        {
            index = botCarteForteAtout(mainJoueur, atout, CartesSurTable, raison);
            carteJouee=mainJoueur[index];
            return index;
        }
        else if(equipeEstMaitre && carteMaitre.getCouleur() != atout)
        {
            index = botCarteForte(mainJoueur, atout, CartesSurTable, raison);
            carteJouee=mainJoueur[index];
            return index;
        }
        else if(carteMaitre.getCouleur() == atout)
        {
            index = botCarteFaibleAtout(mainJoueur, atout, CartesSurTable, raison);
            carteJouee=mainJoueur[index];
            return index;
        }
        else
        {
            index = botCarteFaible(mainJoueur, atout, CartesSurTable, raison);
            carteJouee=mainJoueur[index];
            return index;
        }
    }

    if(equipeEstMaitre && carteMaitre.getCouleur() == atout)
    {
        index = botCarteForteAtout(mainJoueur, atout, CartesSurTable, raison);
        carteJouee=mainJoueur[index];
        return index;
    }
    else if(equipeEstMaitre && carteMaitre.getCouleur() != atout)
    {
        index = botCarteForte(mainJoueur, atout, CartesSurTable, raison);
        carteJouee=mainJoueur[index];
        return index;
    }
    else if(carteMaitre.getCouleur() == atout)
    {
        index = botCarteFaibleAtout(mainJoueur, atout, CartesSurTable, raison);
        carteJouee=mainJoueur[index];
        return index;
    }
    else
    {
        index = botCarteFaible(mainJoueur, atout, CartesSurTable, raison);
        carteJouee=mainJoueur[index];
        return index;
    }
}
