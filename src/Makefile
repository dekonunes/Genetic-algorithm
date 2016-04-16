CC=g++
OBJ=main.o Individuo.o Populacao.o PopulacaoReal.o 
LIBS=-lm -Wall -Wextra -lboost_iostreams -lboost_system -lboost_filesystem
CPP11=-std=c++11 
DEBUG=-g

all: ga

ga: $(OBJ) 
	$(CC) $(DEBUG) $(OBJ) -o ga $(LIBS)
	
main.o: main.cpp
	$(CC) $(CPP11) -c main.cpp 
	
Individuo.o: Individuo.cpp
	$(CC) $(CPP11) -c Individuo.cpp


Populacao.o: Populacao.cpp
	$(CC) $(CPP11) -c Populacao.cpp
	
PopulacaoReal.o: PopulacaoReal.cpp
	$(CC) $(CPP11) -c PopulacaoReal.cpp  

clean:
	rm -rf *.gch *.out *.txt *o ga *~; clear;

	