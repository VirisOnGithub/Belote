all: compile

compile: Carte.o Carte.h main.o
	g++ -g -Wall -o main Carte.o main.o

main.o: main.cpp Carte.h Carte.cpp
	g++ -g -Wall -c main.cpp

Carte.o: Carte.cpp Carte.h
	g++ -g -Wall -c Carte.cpp

clean:
	rm -f main

mrproper: clean
	rm -f *.o

m: mrproper 