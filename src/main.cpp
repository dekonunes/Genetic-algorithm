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
	string str1 = "111111111111", str2 = "000000000000";

	genes.push_back(60); //Computador A
	genes.push_back(50); //Computador B
	Individuo indiv(genes);

	Populacao pop(30, genes);
	Populacao newPop(30, genes);
	/*for (int i = 0; i < 1000; ++i) {
		pop.mutacaoPopulacao();
		newPop = pop.crossoverRollet();
		pop.setPopulacao(newPop.getPopulacao());
		cout << pop.getBestIndividuo().getFuncaoObjetivo() << endl;
	}*/
	indiv.setCromossomo(str1);
	pop.insertIndividuo(indiv);
	indiv.setCromossomo(str2);
	pop.insertIndividuo(indiv);
	cout << pop.getIndividuo(30).getCromossomo() << endl;
	cout << pop.getIndividuo(31).getCromossomo() << endl;
	pair<Individuo, Individuo> newIndividuosCrossover;
	newIndividuosCrossover = pop.crossoverUniforme(30,31);
	cout << newIndividuosCrossover.first.getCromossomo() << endl;
	cout << newIndividuosCrossover.second.getCromossomo() << endl;


	return 0;
}

