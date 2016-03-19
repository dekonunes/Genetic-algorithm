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
	Individuo indv2(5,10);
	int a;
	pop.print_populacao();
	//cout << "oi" << endl;
	pop.getBestIndividuo().getFitness();
	indv.setCromossomo("1111111111");
	indv2.setCromossomo("0000000000");
	pop.crossoverRollet();


	return 0;
}
