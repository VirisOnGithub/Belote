all: compile

compile: Carte.o Carte.h main.o PaquetDeCarte.o PaquetDeCarte.h Main.h Main.o Joueur.o Joueur.h Equipe.o Equipe.h Table.o Table.h
	g++ -g -Wall -o main Carte.o main.o PaquetDeCarte.o Main.o Joueur.o Equipe.o Table.o

main.o: main.cpp Carte.h Carte.cpp PaquetDeCarte.h PaquetDeCarte.cpp Main.h Main.cpp Joueur.h Joueur.cpp Equipe.h Equipe.cpp Table.h Table.cpp
	g++ -g -Wall -c main.cpp

Carte.o: Carte.cpp Carte.h
	g++ -g -Wall -c Carte.cpp

PaquetDeCartes.o: PaquetDeCarte.cpp PaquetDeCarte.h Carte.h Carte.cpp
	g++ -g -Wall -c PaquetDeCarte.cpp

Main.o: Main.cpp Main.h Carte.h Carte.cpp PaquetDeCarte.h PaquetDeCarte.cpp
	g++ -g -Wall -c Main.cpp

Joueur.o: Joueur.cpp Joueur.h Main.h Main.cpp Carte.h Carte.cpp PaquetDeCarte.h PaquetDeCarte.cpp
	g++ -g -Wall -c Joueur.cpp

Equipe.o: Equipe.cpp Equipe.h Joueur.h Joueur.cpp Main.h Main.cpp Carte.h Carte.cpp PaquetDeCarte.h PaquetDeCarte.cpp
	g++ -g -Wall -c Equipe.cpp

Table.o: Table.cpp Table.h Equipe.h Equipe.cpp Joueur.h Joueur.cpp Main.h Main.cpp Carte.h Carte.cpp PaquetDeCarte.h PaquetDeCarte.cpp 
	g++ -g -Wall -c Table.cpp

clean:
	rm -f main

mrproper: clean
	rm -f *.o

m: mrproper 