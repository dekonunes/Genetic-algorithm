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

	/*
	 Populacao pop(20, 1, 16);
	 Populacao newpop(20, 1, 16);
	 for (int i = 0; i < 500; ++i) {
	 pop.mutacaoPopulacao();
	 newpop = pop.crossoverRollet();
	 pop.setPopulacao(newpop.getPopulacao());
	 //cout << pop.getBestIndividuo().getFuncaoObjetivo() << endl;
	 }	*/

	return 0;
}

