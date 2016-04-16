CC=g++
OBJ=main.o IndividuoReal.o PopulacaoReal.o 
LIBS=-lm -Wall -Wextra -lboost_iostreams -lboost_system -lboost_filesystem
CPP11=-std=c++11 
DEBUG=-g

all: ga

ga: $(OBJ) 
	$(CC) $(DEBUG) $(OBJ) -o ga $(LIBS)
	
main.o: main.cpp
	$(CC) $(CPP11) -c main.cpp 
	
IndividuoReal.o: IndividuoReal.cpp
	$(CC) $(CPP11) -c IndividuoReal.cpp

PopulacaoReal.o: PopulacaoReal.cpp
	$(CC) $(CPP11) -c PopulacaoReal.cpp  

clean:
	rm -rf *.gch *.out *.txt *o ga *~; clear;

	