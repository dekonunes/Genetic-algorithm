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
	Populacao pop(10, 1, 10);
	Populacao newpop(10, 1, 10);
	int i = 0;
	int a;
	pop.mutacaoPopulacao();
	pop.print_populacao();
	for (i = 0; i < 3; ++i) {
		cout << "--------- Geração: " << i << endl;
		newpop = pop.crossoverRollet();
		newpop.print_populacao();
		cout << "---" << endl;
		pop.resetPopulacao();
		pop.setPopulacao(newpop.getPopulacao());
		pop.print_populacao();
	}

	return 0;
}
