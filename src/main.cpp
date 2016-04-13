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
	fstream myfile("input.txt", ios_base::in);
	myfile.open("input", ios_base::in);
	if (myfile.is_open()) {
		//Lê do arquivo e retorna os valores das variaveis.
		stringstream ss;
		int param[10], i = 0;
		string temp;
		while (getline(myfile, temp, '\n')) {
			if (stringstream(temp) >> param[i]) {
				i++;
			}
			param[i] = 145142; //significa o fim do parametro
		}

		vector<pair<float, float>> genes;
		pair<float, float> auxGenes;
		i = 7; //a partir daqui é os genes

		while (param[i] != 145142) {
			auxGenes.first = param[i];
			i++;
			auxGenes.second = param[i];
			i++;
			genes.push_back(auxGenes);
		}
		/*Individuo indiv(genes, param[3]);

		Populacao pop(param[0], genes, param[2], param[3], param[4]);
		Populacao newPop(param[0], genes, param[2], param[3], param[4]);
		for (int numExecucoes = 0; numExecucoes < param[6]; ++numExecucoes) {
			for (int i = 0; i < param[5]; ++i) {
				pop.mutacaoPopulacao();
				switch (param[1]) {
				case 1:
					newPop = pop.rollet();
					break;
				case 2:
					newPop = pop.tournament(2);
					break;
				default:
					break;
				}
				pop.setPopulacao(newPop.getPopulacao());
			}
			cout << pop.getBestIndividuo().getFuncaoObjetivo() << endl;
		}*/
		myfile.close();
	} else
		cout << "Erro para abrir o arquivo de entrada";

	return 0;
}

