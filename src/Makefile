CC=g++
OBJ=main.o Individuo.o Populacao.o
LIBS=-lm -Wall
CPP11=-std=c++11

all: ga

ga: $(OBJ) 
	$(CC) main.o Individuo.o Populacao.o -o ga 
	
main.o: main.cpp
	$(CC) $(CPP11) -c main.cpp 
	
Individuo.o: Individuo.cpp
	$(CC) $(CPP11) -c Individuo.cpp 

Populacao.o: Populacao.cpp
	$(CC) $(CPP11) -c Populacao.cpp 

clean:
	rm -rf *.gch *.out *.txt *o ga *~; clear;
