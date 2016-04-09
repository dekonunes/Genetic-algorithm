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
	std::fstream myfile("input.txt", std::ios_base::in);
	myfile.open("input", std::ios_base::in);
	if (myfile.is_open()) {
		//Lê do arquivo e retorna os valores das variaveis.
		stringstream ss;
		int found;
		string temp;
		while (getline(myfile, temp, '\n')) {
			if (stringstream(temp) >> found) {
				cout << found << std::endl;
			}
		}

		vector<float> genes;
		genes.push_back(60); //Computador A
		genes.push_back(50); //Computador B
		Individuo indiv(genes, 1);

		Populacao pop(10, genes, 95, 1, false);
		Populacao newPop(10, genes, 95, 1, false);
		for (int numExecucoes = 0; numExecucoes < 10; ++numExecucoes) {
			for (int i = 0; i < 1000; ++i) {
				pop.mutacaoPopulacao();
				newPop = pop.tournament(2);
				pop.setPopulacao(newPop.getPopulacao());
			}
			//cout << pop.getBestIndividuo().getFuncaoObjetivo() << endl;
		}
		myfile.close();
	} else
		cout << "Erro para abrir o arquivo de entrada";

	return 0;
}

