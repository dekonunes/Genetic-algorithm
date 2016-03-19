//============================================================================
// Name        : Genetic-algorithm.cpp
// Author      : Deko
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "main.hpp"

using namespace std;

int main() {
	Populacao pop(10,1,10);
	Individuo indv(5,10);
	//Individuo bestIndividuo(5,100);
	//pop.print_populacao();
	cout << pop.getBestIndividuo().getFitness() << endl;
	//cout << pop.crossover() << endl;


	return 0;
}
