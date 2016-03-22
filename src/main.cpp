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

	float x = 0;
	float a = cos(20 * x) - (abs(x) / 2) + (x * x * x / 4);
	cout << a << endl;
	IndividuoFuncao indiv(1,16);
	//ind.calculoFitness();

	/*Populacao pop(10, 1, 20);
	 Populacao newpop(10, 1, 20);
	 int i = 0;

	 for (i = 0; i < 50000; ++i) {
	 //for (i = 0; pop.getBestIndividuo().getFitness() != 19; ++i) {
	 cout << "--------- Geração: " << i << endl;
	 pop.mutacaoPopulacao();
	 newpop = pop.crossoverRollet();
	 pop.setPopulacao(newpop.getPopulacao());
	 }
	 cout << pop.getBestIndividuo().getFitness() << endl;*/
	return 0;
}

