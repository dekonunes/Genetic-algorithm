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

double calculoMediaIndvReal(PopulacaoReal);
double calculoMediaIndvBinario(PopulacaoBinario);
double desvioPadrao(PopulacaoReal pop, double media, int execucoes);
void plotMedias(vector<double>, vector<double>, int, int);
void plotDiversidade(vector<double>);
void escreverArquivo(vector<double>);

int main() {
	ifstream texto("entrada.json");

	stringstream buffer;
	buffer << texto.rdbuf();

	auto entrada = json::parse(buffer.str());

	int geracoes = entrada["geracoes"];
	int execucoes;
	double fitnessInd1, fitnessInd2, eucli;
	vector<double> vectorPlotFIT(geracoes, 0);
	vector<double> vectorPlotMediaFIT(geracoes, 0);
	vector<double> vectorPlotDiversidade;
	for (int execucoes = 0; execucoes < entrada["execucoes"]; ++execucoes) {
		if (entrada["codificacao"] == "binario") {
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
				pop.mutacaoPopulacao();
				ind = pop.getBestIndividuo();
				vectorPlotFIT.at(i) += ind.getFitness();
				vectorPlotMediaFIT.at(i) += calculoMediaIndvBinario(pop);
				eucli = 0;
				for (int x = 0; x < entrada["tamPop"]; ++x) {
					ind = pop.getIndividuo(x);
					fitnessInd1 = ind.getFitness();
					for (int y = x + 1; y < entrada["tamPop"]; ++y) {
						ind = pop.getIndividuo(y);
						fitnessInd2 = ind.getFitness();
						//cout << fitnessInd1 << "++" << fitnessInd2 << endl;
						//cout << distanciaEuclid(fitnessInd1, fitnessInd2) << endl;
						eucli += distanciaEuclid(fitnessInd1, fitnessInd2);
					}
				}
				//cout << eucli << endl;
				vectorPlotDiversidade.push_back(eucli);
			}
			cout << ind.getFuncaoObjetivo() << endl;
			//pop.print_populacao();
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
				pop.setPopulacao(newPop.getPopulacao());
				pop.mutacaoPopulacao();
				ind = pop.getBestIndividuo();
				vectorPlotFIT.at(i) += ind.getFitness();
				vectorPlotMediaFIT.at(i) += calculoMediaIndvReal(pop);
				eucli = 0;
				for (int x = 0; x < entrada["tamPop"]; ++x) {
					ind = pop.getIndividuo(x);
					fitnessInd1 = ind.getFitness();
					for (int y = x + 1; y < entrada["tamPop"]; ++y) {
						ind = pop.getIndividuo(y);
						fitnessInd2 = ind.getFitness();
						//cout << fitnessInd1 << "++" << fitnessInd2 << endl;
						cout << distanciaEuclid(fitnessInd1, fitnessInd2) << endl;
						eucli += distanciaEuclid(fitnessInd1, fitnessInd2);
					}
				}
				//cout << eucli << endl;
				vectorPlotDiversidade.push_back(eucli);
			}
			cout << "Individuos: " << entrada["tamPop"] << " Gerações: " << entrada["geracoes"]
					<< " Taxa mutação: " << entrada["chanceMutacao"] << endl;
			cout << "Quantidade de dimensões: " << entrada["qtdVariaveis"] << endl;
			cout << "Desvio: " << desvioPadrao(pop, calculoMediaIndvReal(pop), entrada["execucoes"])
					<< endl;
			cout << "FO: " << ind.getFuncaoObjetivo() << " Execução: " << execucoes << endl << endl;
		}

	}
	plotMedias(vectorPlotFIT, vectorPlotMediaFIT, geracoes, entrada["execucoes"]);
	plotDiversidade(vectorPlotDiversidade);
	//escreverArquivo(vectorPlotFIT);
	return 0;
}

void escreverArquivo(vector<double> vector) {
	ofstream in;
	in.open("a.txt");
	for (int var = 0; var < vector.size(); ++var) {
		in << vector.at(var) << endl;
	}
	in.close();
}

void plotDiversidade(vector<double> vectorPlotDiversidade) {
	Gnuplot gp;
	gp << "plot" << gp.file1d(vectorPlotDiversidade) << "with lines title 'Diversidade'" << endl;

}

void plotMedias(vector<double> vectorPlotFIT, vector<double> vectorPlotMediaFIT, int geracoes,
		int execucoes) {
	Gnuplot gp;
	double aux = 0;
	for (int var = 0; var < geracoes; var++) {
		vectorPlotFIT.at(var) /= execucoes;
		vectorPlotMediaFIT.at(var) /= execucoes;
	}
	//gp << "set yrange [3985:4005]\n";
	gp << "plot" << gp.file1d(vectorPlotFIT) << "with lines title 'Média melhor ind',"
			<< gp.file1d(vectorPlotMediaFIT) << "with lines title 'Média das médias'" << endl;

}

double desvioPadrao(PopulacaoReal pop, double media, int execucoes) {
	double valorDesvio = 0;
	int qtdIndiv = pop.getQtdIndividuos();
	IndividuoReal ind;

	for (int var = 0; var < qtdIndiv; ++var) {
		ind = pop.getIndividuo(var);
		valorDesvio += pow((ind.getFitness() - media), 2);
	}
	return sqrt(valorDesvio / execucoes);
}

double calculoMediaIndvBinario(PopulacaoBinario pop) {
	double valorTotal = 0;
	int qtdIndiv = pop.getQtdIndividuos();
	IndividuoBinario ind;
	for (int var = 0; var < qtdIndiv; ++var) {
		ind = pop.getIndividuo(var);
		valorTotal += ind.getFitness();
	}
	return valorTotal / qtdIndiv;
}

double calculoMediaIndvReal(PopulacaoReal pop) {
	double valorTotal = 0;
	int qtdIndiv = pop.getQtdIndividuos();
	IndividuoReal ind;
	for (int var = 0; var < qtdIndiv; ++var) {
		ind = pop.getIndividuo(var);
		valorTotal += ind.getFitness();
	}
	return valorTotal / qtdIndiv;
}
