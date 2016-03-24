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
	Individuo indiv(1, 16);
	Populacao pop(20, 1, 16);
	Populacao newpop(20, 1, 16);

	int i = 0;
	for (i = 0; i < 500; ++i) {
		pop.mutacaoPopulacao();
		newpop = pop.crossoverRollet();
		pop.setPopulacao(newpop.getPopulacao());
		cout << pop.getBestIndividuo().getFuncaoObjetivo() << endl;
	}
	cout << indiv.getNumeroBits(2,-2,4) << endl;

	return 0;
}

