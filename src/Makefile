CC=g++
OBJ=main.o Individuo.o Populacao.o IndividuoFuncao.o
LIBS=-lm -Wall -Wextra
CPP11=-std=c++11 
DEBUG=-g

all: ga

ga: $(OBJ) 
	$(CC) $(DEBUG) main.o Individuo.o Populacao.o IndividuoFuncao.o -o ga 
	
main.o: main.cpp
	$(CC) $(CPP11) -c main.cpp 
	
Individuo.o: Individuo.cpp
	$(CC) $(CPP11) -c Individuo.cpp
	
IndividuoFuncao.o: IndividuoFuncao.cpp
	$(CC) $(CPP11) -c IndividuoFuncao.cpp  

Populacao.o: Populacao.cpp
	$(CC) $(CPP11) -c Populacao.cpp 

clean:
	rm -rf *.gch *.out *.txt *o ga *~; clear;
