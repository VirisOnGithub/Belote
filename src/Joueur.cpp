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

int Joueur::demanderCarte(int indice,std::vector<Carte> CartesSurTable,std::vector<Carte> cartesJouees, Couleur atout, std::vector<Carte> mainJoueur,std::vector<Joueur> Joueurs, std::string &raison)
{
    int index;
    std::cout << "Entrez l'index de la carte que vous voulez jouer: ";
    if(estBot)
    {
        return botAction(indice,CartesSurTable,cartesJouees, atout, mainJoueur, Joueurs, raison);
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
    int nbCarteAtout = 0;
    Couleur CouleurAtout2=rien;

    for(int i = 0; i < mainBot.size(); i++)
    {
        if(mainBot[i].getCouleur() == CarteAtout.getCouleur())
        {
            nbCarteAtout++;

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
    if((hasValet && hasNeuf && !tour2) ||  (CarteAtout.getChiffreStr() == "valet" && !tour2) || (hasValet && hasAs && !tour2) || (hasValet && nbCarteAtout >= 4 && !tour2) || (hasValet2 && hasNeuf2 && tour2))
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
    for(int i = 0; i < mainJoueur.size();i++)
    {
        if(mainJoueur[i].getCouleur() == atout)
        {
            hasAtout = true;
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
    if(indexCartePlusFaibleAtout == -1)
    {
        return botCarteFaible(mainJoueur,atout,CartesSurTable,raison);
    }
    else
    {
        return indexCartePlusFaibleAtout+1;
    }
}

int Joueur::botCarteForte( std::vector<Carte> mainJoueur, Couleur atout, std::vector<Carte> CartesSurTable, std::string &raison)
{
    int indexCarteNonAtoutPlusForte = -1;
    bool hasAtout = false;
    for(int i = 0; i < mainJoueur.size();i++)
    {
        if(mainJoueur[i].getCouleur() == atout)
        {
            hasAtout = true;
        }
    }

    for(int i = 0; i < mainJoueur.size(); i++)
    {
        if(mainJoueur[i].getCouleur() != atout && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison))
        {
            if(indexCarteNonAtoutPlusForte == -1 || mainJoueur[indexCarteNonAtoutPlusForte].getValeurNonAtout() < mainJoueur[i].getValeurNonAtout())
            {
                indexCarteNonAtoutPlusForte = i;
            }
        }
    }

    std::cout<<std::endl<<"je suis dans botCarteForte index "<<indexCarteNonAtoutPlusForte<<std::endl;

    if(hasAtout && indexCarteNonAtoutPlusForte == -1)
    {
        return botCarteForteAtout(mainJoueur,atout,CartesSurTable,raison);
    }
    else
    {
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

    if(indexCarteAtoutPlusForte == -1)
    {
        return botCarteForte(mainJoueur,atout,CartesSurTable,raison);
    }
    else
    {
        return indexCarteAtoutPlusForte+1;
    }
}

int Joueur::botCarteMaitre(std::vector<Carte> mainJoueur, Couleur atout, std::vector<Carte> CartesSurTable, std::string &raison, bool const equipeEstMaitre, Carte carteMaitre)
{
    int index = 0;

    std::cout<<std::endl;
    std::cout<<"je suis dans botCarteMaitre"<<std::endl;
    std::cout<<"equipeEstMaitre "<<equipeEstMaitre<<std::endl;

    if(equipeEstMaitre && carteMaitre.getCouleur() == atout)
        {
            index = botCarteForteAtout(mainJoueur, atout, CartesSurTable, raison);
            return index;
        }
        else if(equipeEstMaitre && carteMaitre.getCouleur() != atout)
        {
            index = botCarteForte(mainJoueur, atout, CartesSurTable, raison);
            return index;
        }
        else if(!equipeEstMaitre && carteMaitre.getCouleur() == atout)
        {
            index = botCarteFaibleAtout(mainJoueur, atout, CartesSurTable, raison);
            return index;
        }
        else if(!equipeEstMaitre && carteMaitre.getCouleur() != atout)
        {
            index = botCarteFaible(mainJoueur, atout, CartesSurTable, raison);
            return index;
        }

        return index;
}




int Joueur::botAction(int indice,std::vector<Carte> CartesSurTable,std::vector<Carte> cartesJouees, Couleur atout, std::vector<Carte> mainJoueur,std::vector<Joueur> Joueurs, std::string &raison)
{
    Couleur couleurMaitre;
    
    Carte carteJouee = mainJoueur[0];
    Carte carteMaitre;

    bool EquipeAPris = false;
    bool equipeEstMaitre = false;
    bool hasAs = false;
    bool aCoupe = false;
    bool hasMeilleureCarte = false;

    int nbCarteAtoutJouee = 0;
    int indexCoupe = 0;
    int indexMeilleureCarte = 0;
    int indexAs = 0;
    int indexMaitre = 0;
    int index = 0;

    for(int i = 0; i < mainJoueur.size(); i++) // verifie si le joueur a un as
    {
        if(mainJoueur[i].getChiffreStr() == "as" && mainJoueur[i].getCouleur() != atout)
        {
            hasAs = true;
            indexAs = i;
        }
    } 

    for(int i = 0; i < cartesJouees.size(); i++) // verifie le nombre de carte atout jouee
    {
        if(cartesJouees[i].getCouleur() == atout)
        {
            nbCarteAtoutJouee++;
        }
    }

    if(Joueurs[(indice+2) % 4].getAPris() == true) // verifie si l'equipe du joueur entrain de jouer a pris
    {
        EquipeAPris = true;
    }

    if(CartesSurTable.size() >= 1) //verifie si une carte a ete jouee pour pouvoir initialiser la carte maitre et les comparer
    {
        carteMaitre = CartesSurTable[0];
        couleurMaitre = CartesSurTable[0].getCouleur();
        
        for(int i = 0; i < CartesSurTable.size();i++)
        {
            if (mainJoueur[i].getCouleur() != atout && couleurMaitre != atout && mainJoueur[i].getCouleur() == couleurMaitre && mainJoueur[i].getValeurNonAtout() > carteMaitre.getValeurNonAtout() && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison))
            {
                hasMeilleureCarte = true;
                indexMeilleureCarte = i;
            }    
    
            if(CartesSurTable[i].getCouleur() == atout && CartesSurTable[0].getCouleur() != atout) //verifie si un joueur a coupe
            {
                aCoupe = true;
                indexCoupe = i;
            }

            if(carteMaitre.getCouleur() != atout && !aCoupe) //tour sans atout
            {
                if (carteMaitre.getCouleur() == CartesSurTable[i].getCouleur() && carteMaitre.getValeurNonAtout() < CartesSurTable[i].getValeurNonAtout())
                {
                    carteMaitre = CartesSurTable[i];
                    indexMaitre = i;
                }           
            }
            else if(carteMaitre.getCouleur() != atout && aCoupe) //tour avec coupe
            {
                for(int j = indexCoupe; j < CartesSurTable.size(); j++)
                {
                    if(CartesSurTable[j].getCouleur() == atout && CartesSurTable[j].getValeurAtout() > CartesSurTable[indexCoupe].getValeurAtout())
                    {
                        carteMaitre = CartesSurTable[j];
                        indexMaitre = j;
                    }
                    else
                    {
                        carteMaitre = CartesSurTable[indexCoupe];
                        indexMaitre = indexCoupe;
                    }
                }
                
            }
            else if(carteMaitre.getCouleur() == atout) //tour avec atout
            {
                if(carteMaitre.getValeurAtout() < CartesSurTable[i].getValeurAtout())
                {
                    carteMaitre = CartesSurTable[i];
                    indexMaitre = i;
                }
            }
        }
        for(int k = 0; k < CartesSurTable.size(); k++)
        {
            if(k >= 1 && indexMaitre == k-1)
            {
                equipeEstMaitre = true;
            }
            
        }
      

    }
    if(CartesSurTable.size() >= 1) //verifie si une carte a ete jouee pour pouvoir initialiser la carte maitre et les comparer
    {
        couleurMaitre = carteMaitre.getCouleur();
        
        for(int i = 0; i < CartesSurTable.size();i++)
        {
            if (mainJoueur[i].getCouleur() != atout && couleurMaitre != atout && mainJoueur[i].getCouleur() == couleurMaitre && mainJoueur[i].getValeurNonAtout() > carteMaitre.getValeurNonAtout() && mainJoueur[i].estValide(CartesSurTable, atout, mainJoueur, raison))
            {
                hasMeilleureCarte = true;
                indexMeilleureCarte = i;
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
        
         
        if(hasAs && mainJoueur[indexAs].estValide(CartesSurTable, atout, mainJoueur, raison) && !aCoupe)
        {
            std::cout<<std::endl;
            std::cout<<"Le bot a joué un as de "<<mainJoueur[indexAs].getCouleurStr()<<std::endl;
            carteJouee=mainJoueur[indexAs];
            return indexAs+1;
        }
        
        if(CartesSurTable.size() >= 1)
        {
            if(hasMeilleureCarte && !aCoupe && mainJoueur[indexMeilleureCarte].estValide(CartesSurTable, atout, mainJoueur, raison))
            {
                std::cout<<std::endl;
                std::cout<<"Le bot a joué une carte plus forte que la carte maitre"<<std::endl;
                carteJouee=mainJoueur[indexMeilleureCarte];
                return indexMeilleureCarte+1;
            }
            else
            {
                return botCarteMaitre(mainJoueur, atout, CartesSurTable, raison, equipeEstMaitre, carteMaitre);
            }
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
                else if(hasAs && mainJoueur[indexAs].estValide(CartesSurTable, atout, mainJoueur, raison))
                {
                    std::cout<<std::endl;
                    std::cout<<"Le bot a joué un as de "<<mainJoueur[indexAs].getCouleurStr()<<std::endl;
                    carteJouee=mainJoueur[indexAs];
                    return indexAs+1;
                }
            }
            else if(EquipeAPris && CartesSurTable.size() == 0)
            {
                index = botCarteFaibleAtout(mainJoueur, atout, CartesSurTable, raison);
                carteJouee=mainJoueur[index];
                return index;
            }
            else if(hasAs && mainJoueur[indexAs].estValide(CartesSurTable, atout, mainJoueur, raison) && !aCoupe)
            {
                if(CartesSurTable.size() == 1 && CartesSurTable[0].getCouleur() != atout)
                {
                    std::cout<<std::endl;
                    std::cout<<"Le bot a joué un as de "<<mainJoueur[indexAs].getCouleurStr()<<std::endl;
                    carteJouee=mainJoueur[indexAs];
                    return indexAs+1;
                }
            }
        }

        if(CartesSurTable.size() >= 1)
        {
            if(hasMeilleureCarte && !aCoupe && mainJoueur[indexMeilleureCarte].estValide(CartesSurTable, atout, mainJoueur, raison))
            {
                std::cout<<std::endl;
                std::cout<<"Le bot a joué une carte plus forte que la carte maitre"<<std::endl;
                carteJouee=mainJoueur[indexMeilleureCarte];
                return indexMeilleureCarte+1;
            }
            else
            {
                return botCarteMaitre(mainJoueur, atout, CartesSurTable, raison, equipeEstMaitre, carteMaitre);
            }
        }  
        else
        {
            index = botCarteFaible(mainJoueur, atout, CartesSurTable, raison);
            carteJouee=mainJoueur[index];
            return index;
        }
    }

    if(CartesSurTable.size() >= 1)
    {
        if(hasMeilleureCarte && !aCoupe && mainJoueur[indexMeilleureCarte].estValide(CartesSurTable, atout, mainJoueur, raison))
        {
            std::cout<<std::endl;
            std::cout<<"Le bot a joué une carte plus forte que la carte maitre"<<std::endl;
            carteJouee=mainJoueur[indexMeilleureCarte];
            return indexMeilleureCarte+1;
        }
        else
        {
            return botCarteMaitre(mainJoueur, atout, CartesSurTable, raison, equipeEstMaitre, carteMaitre);
        }
    }
    else
    {
        index = botCarteFaible(mainJoueur, atout, CartesSurTable, raison);
        carteJouee=mainJoueur[index];
        return index;
    }
}
