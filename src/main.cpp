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
	//cout << a << endl;
	Individuo indiv(1, 16);
	//indiv.decodificaCromossomo();

	Populacao pop(20, 1, 16);

	Populacao newpop(20, 1, 16);

	int i = 0;
	for (i = 0; i < 500; ++i) {
		//for (i = 0; pop.getBestIndividuo().getFitness() != 19; ++i) {
		//cout << "--------- Geração: " << i << endl;
		//pop.print_populacao();
		pop.mutacaoPopulacao();
		newpop = pop.crossoverRollet();
		pop.setPopulacao(newpop.getPopulacao());
		//cout << "Obj:" << pop.getBestIndividuo().getFuncaoObjetivo() << endl;
	}
	pop.print_populacao();
	cout << "Obj:" << pop.getBestIndividuo().getFuncaoObjetivo() << endl;
	cout << "fit:" << pop.getBestIndividuo().getFitness() << endl;

	return 0;
}

