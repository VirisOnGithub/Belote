all: compile

compile: Carte.o Carte.h main.o PaquetDeCarte.o PaquetDeCarte.h Main.h Main.o
	g++ -g -Wall -o main Carte.o main.o PaquetDeCarte.o Main.o

main.o: main.cpp Carte.h Carte.cpp PaquetDeCarte.h PaquetDeCarte.cpp Main.h Main.cpp
	g++ -g -Wall -c main.cpp

Carte.o: Carte.cpp Carte.h
	g++ -g -Wall -c Carte.cpp

PaquetDeCartes.o: PaquetDeCarte.cpp PaquetDeCarte.h Carte.h Carte.cpp
	g++ -g -Wall -c PaquetDeCarte.cpp

Main.o: Main.cpp Main.h Carte.h Carte.cpp PaquetDeCarte.h PaquetDeCarte.cpp
	g++ -g -Wall -c Main.cpp

clean:
	rm -f main

mrproper: clean
	rm -f *.o

m: mrproper 