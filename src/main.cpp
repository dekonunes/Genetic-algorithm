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
	genes.push_back(60); //Computador A
	genes.push_back(50); //Computador B
	Individuo indiv(genes);

	Populacao pop(10, genes);
	Populacao newPop(10, genes);
	for (int numExecucoes = 0; numExecucoes < 10; ++numExecucoes) {
		for (int i = 0; i < 1000; ++i) {
			pop.mutacaoPopulacao();
			newPop = pop.tournament(2);
			pop.setPopulacao(newPop.getPopulacao());
		}
		cout << pop.getBestIndividuo().getFuncaoObjetivo() << endl;
	}

	return 0;
}

