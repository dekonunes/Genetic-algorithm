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
void plot(vector<double>, string);
void plot(vector<double>, vector<double>, string, string);
void escreverArquivo(vector<double>);
double distanciaBinario(PopulacaoBinario, int);
double distanciaReal(PopulacaoReal pop, int tipoDistancia);

int main() {
	ifstream texto("entrada.json");

	stringstream buffer;
	buffer << texto.rdbuf();

	auto entrada = json::parse(buffer.str());

	int geracoes = entrada["geracoes"];
	int execucoesEntrada = entrada["execucoes"];
	vector<double> vectorPlotFIT(geracoes, 0);
	vector<double> vectorPlotMediaFIT(geracoes, 0);
	vector<double> vectorPlotDiversidade(geracoes, 0);
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
					if (i < geracoes * 0.9)
						pop.incrementaC();
					newPop = pop.rollet();
					break;
				case 2:
					newPop = pop.tournament(entrada["tournament"]);
					break;
				default:
					break;
				}
				pop.setPopulacao(newPop.getPopulacao());
				ind = pop.getBestIndividuo();
				vectorPlotFIT.at(i) += ind.getFitness() / execucoesEntrada;
				vectorPlotMediaFIT.at(i) += calculoMediaIndvBinario(pop) / execucoesEntrada;
				vectorPlotDiversidade.at(i) += distanciaBinario(pop, 1) / execucoesEntrada;
			}
			cout << ind.getFuncaoObjetivo() << endl;
			//pop.print_populacao();
		}
		if (entrada["codificacao"] == "real") {
			vector<pair<double, double>> genes;
			vector<double> auxGenes;
			PopulacaoReal pop;
			IndividuoReal ind;
			PopulacaoReal newPop;
			int aux;
			for (int i = 0; i < geracoes; ++i) {
				pop.mutacaoPopulacao();
				aux = entrada["selecao"];
				switch (aux) {
				case 1:
					if (i < geracoes * 0.9)
						pop.incrementaC();
					newPop = pop.rollet();
					break;
				case 2:
					newPop = pop.tournament(entrada["tournament"]);
					break;
				default:
					break;
				}
				pop.setPopulacao(newPop.getPopulacao());
				ind = pop.getBestIndividuo();
				vectorPlotFIT.at(i) += (ind.getFitness() / execucoesEntrada);
				vectorPlotMediaFIT.at(i) += (calculoMediaIndvReal(pop) / execucoesEntrada);
				vectorPlotDiversidade.at(i) += (distanciaReal(pop, 1) / execucoesEntrada);
			}
			cout << "Individuos: " << entrada["tamPop"] << " Gerações: " << entrada["geracoes"]
					<< " Taxa mutação: " << entrada["chanceMutacao"] << endl;
			cout << "Quantidade de dimensões: " << entrada["qtdVariaveis"] << endl;
			cout << "Tipo Crossover:" << entrada["crossover"] << endl;
			cout << "Desvio: " << desvioPadrao(pop, calculoMediaIndvReal(pop), entrada["execucoes"])
					<< endl;
			cout << "FO: " << ind.getFuncaoObjetivo() << endl;
			cout << "Execução: " << execucoes << endl;
			cout << "Elitismo: " << entrada["elitismo"] << endl;
			cout << "Fitness Escalonado: " << entrada["escalonado"] << endl << endl;
		}

	}
	plot(vectorPlotFIT, vectorPlotMediaFIT, "Média do melhor ind", "Média das médias");
	plot(vectorPlotDiversidade, "diversidade");
	//escreverArquivo(vectorPlotFIT);
	return 0;
}

double distanciaBinario(PopulacaoBinario pop, int tipoDistancia) {
	IndividuoBinario ind1, ind2;
	double fitnessInd1, fitnessInd2, dist = 0;
	for (int x = 0; x < pop.getQtdIndividuos(); ++x) {
		ind1 = pop.getIndividuo(x);
		fitnessInd1 = ind1.getFitness();
		for (int y = x + 1; y < pop.getQtdIndividuos(); ++y) {
			ind2 = pop.getIndividuo(y);
			fitnessInd2 = ind2.getFitness();
			switch (tipoDistancia) {
			case 1:
				dist += hamming(ind1.getCromossomo(), ind2.getCromossomo());
				break;
			case 2:
				dist += euclidiana(fitnessInd1, fitnessInd2);
				break;
			default:
				break;
			}

		}
	}
	return dist;
}

double distanciaReal(PopulacaoReal pop, int tipoDistancia) {
	IndividuoReal ind1, ind2;
	double fitnessInd1, fitnessInd2, dist = 0;
	for (int x = 0; x < pop.getQtdIndividuos(); ++x) {
		ind1 = pop.getIndividuo(x);
		fitnessInd1 = ind1.getFitness();
		for (int y = x + 1; y < pop.getQtdIndividuos(); ++y) {
			ind2 = pop.getIndividuo(y);
			fitnessInd2 = ind2.getFitness();
			switch (tipoDistancia) {
			case 1:
				dist += euclidiana(fitnessInd1, fitnessInd2);
				break;
			case 2:
				dist += euclidianaNormalizada(fitnessInd1, fitnessInd2);
				break;
			default:
				break;
			}

		}
	}
	return dist;
}

void escreverArquivo(vector<double> vector) {
	ofstream in;
	in.open("a.txt");
	for (int var = 0; var < vector.size(); ++var) {
		in << vector.at(var) << endl;
	}
	in.close();
}

void plot(vector<double> vectorPlot, string titulo) {
	Gnuplot gp;
	gp << "plot" << gp.file1d(vectorPlot) << "with lines title '" << titulo << "'" << endl;

}

void plot(vector<double> vectorPlot1, vector<double> vectorPlot2, string titulo1, string titulo2) {
	Gnuplot gp;
	gp << "plot" << gp.file1d(vectorPlot1) << "with lines title '" << titulo1 << "',"
			<< gp.file1d(vectorPlot2) << "with lines title '" << titulo2 << "'" << endl;

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
