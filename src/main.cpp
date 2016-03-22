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
	Populacao pop(10, 1, 20);
	Populacao newpop(10, 1, 20);
	int i = 0;
	int a;

	pop.print_populacao();
	for (i = 0; i < 50000; ++i) {
	//for (i = 0; pop.getBestIndividuo().getFitness() != 19; ++i) {
		cout << "--------- Geração: " << i << endl;
		pop.mutacaoPopulacao();
		newpop = pop.crossoverRollet();
		//newpop.print_populacao();


		//cout << pop.getBestIndividuo().getCromossomo() << endl;
		//pop.print_populacao();
		pop.setPopulacao(newpop.getPopulacao());
		cout << pop.getBestIndividuo().getFitness() << endl;
	}

	return 0;
}
