DEBUG=-g

all: ga

main.o: main.cpp
	g++ $(DEBUG) -c -lm -Wall main.cpp -pthread
	
ga: main.o mt.o Individuo.o
	g++ -pg main.o mt.o Individuo.o -o ga -lm
	
mersenne.o: mt.cc
	g++ mt.cc -c -w -lm -Wall

individuo.o: Individuo.cpp
	g++ -c Individuo.cpp


clean:
	rm -rf *.gch *.out *.txt *o ga *~; clear;clear;
