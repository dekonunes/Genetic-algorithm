//============================================================================
// Name        : Genetic-algorithm.cpp
// Author      : Deko
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "main.hpp"

using namespace std;
using json = nlohmann::json;

int main() {
	ifstream texto("entrada.json");

	stringstream buffer;
	buffer << texto.rdbuf();

	auto entrada = json::parse(buffer.str());

	Gnuplot gp;
	vector<double> vectorPlot;
	if (entrada["codificacao"] == "binaria") {
		vector<pair<int, int>> genes;
		pair<int, int> auxGenes;
		IndividuoBinario ind;
		PopulacaoBinario pop;
		PopulacaoBinario newPop;
		int aux;
		for (int i = 0; i < entrada["geracoes"]; ++i) {
			pop.mutacaoPopulacao();
			aux = entrada["selecao"];
			switch (aux) {
			case 1:
				newPop = pop.rollet();
				break;
			case 2:
				newPop = pop.tournament(entrada["tournament"]);
				break;
			default:
				break;
			}
			pop.setPopulacao(newPop.getPopulacao());

			if (pop.getBestIndividuo().getFitness() > ind.getFitness()) {
				ind = pop.getBestIndividuo(); //best indiv ever
			}
		}
		cout << ind.getFuncaoObjetivo() << endl;
	}
	if (entrada["codificacao"] == "real") {
		vector<pair<double, double>> genes;
		pair<double, double> auxGenes;
		IndividuoReal ind;
		PopulacaoReal pop;
		PopulacaoReal newPop;
		int aux;

		for (int i = 0; i < entrada["geracoes"]; ++i) {
			pop.mutacaoPopulacao();
			aux = entrada["selecao"];
			switch (aux) {
			case 1:
				newPop = pop.rollet();
				break;
			case 2:
				newPop = pop.tournament(entrada["tournament"]);
				break;
			default:
				break;
			}

			pop.setPopulacao(newPop.getPopulacao());
			//cout << ind.getFitness() << "  " << i<< endl;
			if (pop.getBestIndividuo().getFitness() > ind.getFitness()) {
				ind = pop.getBestIndividuo(); //best indiv ever
				cout << ind.getFuncaoObjetivo() << "  " << i << endl;
			}
		}

	}
	/* Plot */

//gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
//gp << "plot" << gp.file1d(vectorPlot) << "with points title 'circle'" << endl;
	return 0;
}
