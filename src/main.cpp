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
	double mediaFITCadaGeracao = 0;
	int geracoes = entrada["geracoes"];
	int execucoes = entrada["execucoes"];
	vector<double> vectorPlotFIT(geracoes, 0);
	for (int execucoes = 0; execucoes < entrada["execucoes"]; ++execucoes) {
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
			vector<double> auxGenes;
			IndividuoReal ind;
			PopulacaoReal pop;
			PopulacaoReal newPop;
			int aux;

			for (int i = 0; i < geracoes; ++i) {
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
					//cout << ind.getFuncaoObjetivo() << endl;
				}
				ind = pop.getBestIndividuo();

				vectorPlotFIT.at(i) += ind.getFitness();
			}
			mediaFITCadaGeracao = 0;
		}
	}
	double aux = 0;
	for (int var = 0; var < geracoes; var++) {
		vectorPlotFIT.at(var) /= execucoes;
		//cout << vectorPlotFIT.at(var) << endl;
	}

	gp << "plot" << gp.file1d(vectorPlotFIT)
			<< "title 'Media Geracoes' with lines linecolor rgb 'red'" << endl;
	//gp << "plot" << gp.file1d(vectorPlotFIT) << endl;
	return 0;
}
