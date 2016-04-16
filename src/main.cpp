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
	Gnuplot gp;
	vector<double> vectorPlot;
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

		vector<pair<int, int>> genesB;
		vector<pair<double, double>> genesF;
		pair<int, int> auxGenes;
		pair<double, double> auxGeneF;
		i = 7; //a partir daqui é os genes

		while (param[i] != 145142) {
			auxGenes.first = param[i];
			i++;
			auxGenes.second = param[i];
			i++;
			genesF.push_back(auxGenes);
		}
		Individuo ind(genesF, 1);
		PopulacaoReal pop(param[0], genesF, param[2], param[3], param[4]);
		PopulacaoReal newPop(param[0], genesF, param[2], param[3], param[4]);
		for (int numExecucoes = 0; numExecucoes < param[6]; ++numExecucoes) {
			for (int i = 0; i < param[5]; ++i) {
				pop.mutacaoPopulacao();
				ind = pop.getBestIndividuo(); //best indiv ever
				/*switch (param[1]) {
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
				 */
				//if (pop.getBestIndividuo().getFitness() > ind.getFitness()) {

				//}
				//vectorPlot.push_back(ind.getFitness());
				//cout << ind = pop.getBestIndividuo() << endl;
			}
			cout << ind.getFuncaoObjetivo() << endl;
		}
		myfile.close();
	} else
		cout << "Erro para abrir o arquivo de entrada";

	/* Plot */

	//gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
	//gp << "plot" << gp.file1d(vectorPlot) << "with points title 'circle'" << endl;
	return 0;
}

