DEBUG=-g

all: ga

main.o: main.cpp
	g++ $(DEBUG) -c -lm -Wall main.cpp -pthread -std=c++11
	
ga: main.o mt.o Individuo.o populacao.o
	g++ main.o mt.o Individuo.o populacao.o -o ga -lm
	
mt.o: mt.cc
	g++ mt.cc -c -w -lm -Wall

individuo.o: Individuo.cpp
	g++ -c Individuo.cpp

populacao.o: Populacao.cpp
	g++ -c Populacao.cpp

clean:
	rm -rf *.gch *.out *.txt *o ga *~; clear;clear;
