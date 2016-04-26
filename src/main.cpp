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
	vector<double> vectorPlotAuxFO, vectorPlotFO, vectorPlotAuxFIT, vectorPlotFIT, bestInd;
	vector<vector<double>> vectorPlotGeracoesFO, vectorPlotGeracoesFIT;
	int geracoes = entrada["geracoes"];
	int execucoes = entrada["execucoes"];
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
					auxGenes = ind.getGenes();
					cout << auxGenes.at(0) << "   " << auxGenes.at(1) << endl;
					cout << ind.getFuncaoObjetivo() << endl;
				}
				/*ind = pop.getBestIndividuo();
				 bestInd.push_back(ind.getFuncaoObjetivo());
				 vectorPlotAuxFO.push_back(ind.getFuncaoObjetivo());
				 for (int var = 0; var < pop.getQtdIndividuos(); ++var) {
				 ind = pop.getIndividuo(var);
				 mediaFITCadaGeracao += ind.getFitness();
				 }*/
			}
			vectorPlotFIT.push_back(mediaFITCadaGeracao / geracoes);
			mediaFITCadaGeracao = 0;
			vectorPlotGeracoesFO.push_back(vectorPlotAuxFO);
		}
	}
	/*double aux = 0;

	 for (int var = 0; var < entrada["geracoes"]; ++var) {
	 for (int execucoes = 0; execucoes < entrada["execucoes"]; ++execucoes) {
	 aux += vectorPlotGeracoesFO[execucoes].at(var);
	 }
	 aux = aux / execucoes;
	 vectorPlotFO.push_back(aux);
	 aux = 0;
	 }

	 gp << "plot" << gp.file1d(vectorPlotFO)
	 << "title 'Media Geracoes' with lines linecolor rgb 'red' ," << gp.file1d(bestInd) <<"title 'Melhor execucoes' with lines linecolor rgb 'blue'" << endl;
	 */
	return 0;
}
