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

double calculoMediaIndv(PopulacaoReal);

int main() {
	ifstream texto("entrada.json");

	stringstream buffer;
	buffer << texto.rdbuf();

	auto entrada = json::parse(buffer.str());

	Gnuplot gp;
	int geracoes = entrada["geracoes"];
	int execucoes = entrada["execucoes"];
	vector<double> vectorPlotFIT(geracoes, 0);
	vector<double> vectorPlotMediaFIT(geracoes, 0);
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
			pop.print_populacao();
		}
		if (entrada["codificacao"] == "real") {
			vector<pair<double, double>> genes;
			vector<double> auxGenes;
			IndividuoReal ind;
			PopulacaoReal pop;
			PopulacaoReal newPop;
			int aux;

			for (int i = 0; i < geracoes; ++i) {

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
				ind = pop.getIndividuo(0);
				cout << ind.getFuncaoObjetivo() << "  ";
				ind = newPop.getIndividuo(0);
				cout << ind.getFuncaoObjetivo() << endl;

				pop.setPopulacao(newPop.getPopulacao());
				//pop.mutacaoPopulacao();
				/*if (pop.getBestIndividuo().getFitness() > ind.getFitness()) {
				 ind = pop.getBestIndividuo(); //best indiv ever

				 }*/
				ind = pop.getBestIndividuo();
				//cout << "---" <<ind.getFuncaoObjetivo() << endl;
				vectorPlotFIT.at(i) += ind.getFitness();

				vectorPlotMediaFIT.at(i) += calculoMediaIndv(pop);
				//cout << calculoMediaIndv(pop) << endl;

			}
		}

	}

	double aux = 0;
	for (int var = 0; var < geracoes; var++) {
		vectorPlotFIT.at(var) /= execucoes;
		vectorPlotMediaFIT.at(var) /= execucoes;
		//cout << vectorPlotFIT.at(var) << endl;
		//cout << vectorPlotMediaFIT.at(var) << endl;
	}
	//gp << "set yrange [0:6]\n";
	gp << "plot" << gp.file1d(vectorPlotFIT) << "with lines title 'Média melhor ind',"
			<< gp.file1d(vectorPlotMediaFIT) << "with lines title 'Media das medias'" << endl;

	return 0;
}

double calculoMediaIndv(PopulacaoReal pop) {
	double valorTotal = 0;
	int qtdIndiv = pop.getQtdIndividuos();
	IndividuoReal ind;

	for (int var = 0; var < qtdIndiv; ++var) {
		ind = pop.getIndividuo(var);
		valorTotal += ind.getFitness();
		//cout << "===" << ind.getFitness() << "   " << valorTotal << "pop:" << qtdIndiv << endl;
	}
	//cout << "===" << ind.getFitness() << "   " << valorTotal << "pop:" << qtdIndiv << endl;
	return valorTotal / qtdIndiv;
}
