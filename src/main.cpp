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
	ifstream texto("entrada.json"); //mudar pra argv

	stringstream buffer;
	buffer << texto.rdbuf();

	auto entrada = json::parse(buffer.str());
	//cout << entrada["codificacao"][0]["max"];

	Gnuplot gp;
	vector<double> vectorPlot;
	if (entrada["codificacao"] == "binaria") {
		vector<pair<int, int>> genes;
		pair<int, int> auxGenes;
		IndividuoBinario ind;
		PopulacaoBinario pop;
		pop.print_populacao();
		//PopulacaoBinario newPop(entrada["tamPop"], genes, entrada["chanceCrossover"], entrada["eletismo"]);
	}
	/*vector<pair<double, double>> genesF;

	 pair<double, double> auxGeneF;


	 IndividuoReal ind(genesF, 1);
	 PopulacaoReal pop(param[0], genesF, param[2], param[3], param[4]);
	 PopulacaoReal newPop(param[0], genesF, param[2], param[3], param[4]);
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

	 if (pop.getBestIndividuo().getFitness() > ind.getFitness()) {
	 ind = pop.getBestIndividuo(); //best indiv ever
	 }
	 //vectorPlot.push_back(ind.getFitness());
	 //cout << ind = pop.getBestIndividuo() << endl;
	 }
	 cout << ind.getFuncaoObjetivo() << endl;
	 }*/

	/* Plot */

//gp << "set xrange [-2:2]\nset yrange [-2:2]\n";
//gp << "plot" << gp.file1d(vectorPlot) << "with points title 'circle'" << endl;
	return 0;
}

