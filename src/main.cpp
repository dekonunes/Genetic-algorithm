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
	vector<float> genes;
	genes.push_back(10);
	genes.push_back(15);
	Individuo indiv(genes);
	Populacao pop(20, genes);
	Populacao newPop(20, genes);
	for (int i = 0; i < 50; ++i) {
		pop.mutacaoPopulacao();
		newPop = pop.crossoverRollet();
		pop.setPopulacao(newPop.getPopulacao());
		cout << pop.getBestIndividuo().getFuncaoObjetivo() << endl;
	}
	return 0;
}

