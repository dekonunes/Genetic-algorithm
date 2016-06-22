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
double desvioPadraoBinario(PopulacaoBinario pop, double media, int execucoes);
double desvioPadraoReal(PopulacaoReal pop, double media, int execucoes);
void plot(vector<double>, string);
void plot(vector<double>, vector<double>, string, string);
void plot(vector<double>, vector<double>, vector<double>, string, string, string);
void escreverArquivo(vector<double>);
double distanciaBinario(PopulacaoBinario, int, int);
double distanciaRealGenotipica(PopulacaoReal, int, int);
double distanciaRealFenotipica(PopulacaoReal, int, int);
void imprimiResultados(double, double);
void mostrarDadosFinais(vector<double>, vector<double>);

int main() {
	ifstream texto("entrada.json");

	stringstream buffer;
	buffer << texto.rdbuf();

	auto entrada = json::parse(buffer.str());
	texto.close();
	int geracoes = entrada["geracoes"];
	int execucoesEntrada = entrada["execucoes"];
	vector<double> vectorPlotFIT(geracoes, 0);
	vector<double> vectorPlotMediaFIT(geracoes, 0);
	vector<double> vectorPlotDiversidade(geracoes, 0);
	vector<double> vectorFOCadaExecucoes;
	vector<double> vectorDesvioPadrao;
	for (int execucoes = 0; execucoes < entrada["execucoes"]; ++execucoes) {
		if (entrada["codificacao"] == "binario") {
			IndividuoBinario ind;
			PopulacaoBinario pop;
			int selecao = entrada["selecao"];
			for (int i = 0; i < entrada["geracoes"]; ++i) {
				switch (selecao) {
				case 1:
					if ((i < geracoes * 0.9) && (i > geracoes * 0.1))
						pop.incrementaC();
					if ((i > geracoes * 0.85))
						pop.disableGap();
					pop = pop.rollet();
					break;
				case 2:
					pop = pop.tournament();
					break;
				default:
					break;
				}
				ind = pop.getBestIndividuo();
				//cout << ind.getFuncaoObjetivo() << "  " <<i << endl;
				vectorPlotFIT.at(i) += ind.getFitness() / execucoesEntrada;
				vectorPlotMediaFIT.at(i) += calculoMediaIndvBinario(pop) / execucoesEntrada;
				vectorPlotDiversidade.at(i) += distanciaBinario(pop, 1,
						(geracoes / 100) * pop.getQtdIndividuos()) / execucoesEntrada;
			}
			imprimiResultados(
					desvioPadraoBinario(pop, calculoMediaIndvBinario(pop), entrada["execucoes"]),
					ind.getFuncaoObjetivo());
			vectorFOCadaExecucoes.push_back(ind.getFuncaoObjetivo());
			vectorDesvioPadrao.push_back(
					desvioPadraoBinario(pop, calculoMediaIndvBinario(pop), entrada["execucoes"]));
		}
		if (entrada["codificacao"] == "real") {
			vector<pair<double, double>> genes;
			vector<double> auxGenes;
			PopulacaoReal pop;
			IndividuoReal ind;
			int aux;
			for (int i = 0; i < geracoes; ++i) {
				aux = entrada["selecao"];
				switch (aux) {
				case 1:
					if ((i < geracoes * 0.9) && (i > geracoes * 0.1))
						pop.incrementaC();
					//if ((i > geracoes * 0.85))
					if ((i < geracoes * 0.15) || (i > geracoes * 0.85))
						pop.disableGap();
					else
						pop.enableGap();

					pop = pop.rollet();
					break;
				case 2:
					pop = pop.tournament();
					break;
				default:
					break;
				}
				ind = pop.getBestIndividuo();
				vectorPlotFIT.at(i) += (ind.getFitness() / execucoesEntrada);
				vectorPlotMediaFIT.at(i) += (calculoMediaIndvReal(pop) / execucoesEntrada);
				vectorPlotDiversidade.at(i) += (distanciaRealFenotipica(pop, 1,
						(geracoes / 100) * pop.getQuantidadeIndividuos()) / execucoesEntrada);
			}
			imprimiResultados(
					desvioPadraoReal(pop, calculoMediaIndvReal(pop), entrada["execucoes"]),
					ind.getFuncaoObjetivo());
			vectorFOCadaExecucoes.push_back(ind.getFuncaoObjetivo());
			vectorDesvioPadrao.push_back(
					desvioPadraoReal(pop, calculoMediaIndvReal(pop), entrada["execucoes"]));
		}
	}
	plot(vectorPlotFIT, vectorPlotMediaFIT, "Média do melhor ind", "Média das médias");
	plot(vectorPlotDiversidade, "diversidade");
	mostrarDadosFinais(vectorFOCadaExecucoes, vectorDesvioPadrao);
	//escreverArquivo(vectorPlotFIT);
	return 0;
}

void mostrarDadosFinais(vector<double> vectorFO, vector<double> vectorDesvioPadrao) {
	double mediaFO = 0, mediaDesvio = 0;
	int execucoes = vectorFO.size();
	for (int var = 0; var < execucoes; ++var) {
		mediaFO += vectorFO.at(var) / execucoes;
		mediaDesvio += vectorDesvioPadrao.at(var) / execucoes;
	}
	cout << "----- Resultado final -----" << endl;
	imprimiResultados(mediaDesvio, mediaFO);
}

void imprimiResultados(double desvioPadrao, double funcaoObjetivo) {
	ifstream texto("entrada.json");
	stringstream buffer;
	buffer << texto.rdbuf();
	auto entrada = json::parse(buffer.str());
	cout << "Individuos: " << entrada["tamPop"] << " Gerações: " << entrada["geracoes"]
			<< " Taxa mutação: " << entrada["chanceMutacao"] << endl;
	cout << "Quantidade de dimensões: " << entrada["qtdVariaveis"] << endl;
	cout << "Tipo Crossover:" << entrada["crossover"] << endl;
	cout << "Desvio: " << desvioPadrao << endl;
	cout << "FO: " << funcaoObjetivo << endl;
	cout << "Execução: " << entrada["execucoes"] << endl;
	cout << "Elitismo: " << entrada["elitismo"] << endl;
	cout << "GAP: " << entrada["gap"] << endl;
	cout << "Fitness Escalonado: " << entrada["escalonado"] << endl;
	cout << "Fitness Crowding: " << entrada["crowding"] << endl;
	cout << "Fitness Sharring: " << entrada["sharring"] << endl << endl;
}

double distanciaBinario(PopulacaoBinario pop, int tipoDistancia, int divisorDasGeracoes) {
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
			case 3:
				dist += euclidianaNormalizada(fitnessInd1, fitnessInd2);
				break;
			default:
				break;
			}

		}
	}
	return dist / divisorDasGeracoes;
}

double distanciaRealGenotipica(PopulacaoReal pop, int tipoDistancia, int divisorDasGeracoes) {
	IndividuoReal ind1, ind2;
	vector<double> genesIndividuo1, genesIndividuo2;
	double dist = 0;
	for (int x = 0; x < pop.getQuantidadeIndividuos(); ++x) {
		ind1 = pop.getIndividuo(x);
		genesIndividuo1 = ind1.getGenes();
		for (int y = x + 1; y < pop.getQuantidadeIndividuos(); ++y) {
			ind2 = pop.getIndividuo(y);
			genesIndividuo2 = ind2.getGenes();
			switch (tipoDistancia) {
			case 1:
				for (int var = 0; var < pop.getQuantidadeGenes(); ++var) {
					dist +=
							(euclidiana(genesIndividuo1.at(var), genesIndividuo2.at(var)) / (x * y));
				}
				break;
			case 2:
				//dist += euclidianaNormalizada(fitnessInd1, fitnessInd2);
				break;
			default:
				break;
			}

		}
	}
	return dist / divisorDasGeracoes;
}

double distanciaRealFenotipica(PopulacaoReal pop, int tipoDistancia, int divisorDasGeracoes) {
	IndividuoReal ind1, ind2;
	double fitnessInd1, fitnessInd2, dist = 0;
	for (int x = 0; x < pop.getQuantidadeIndividuos(); ++x) {
		ind1 = pop.getIndividuo(x);
		fitnessInd1 = ind1.getFitness();
		for (int y = x + 1; y < pop.getQuantidadeIndividuos(); ++y) {
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
	return dist / divisorDasGeracoes;
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

void plot(vector<double> vectorPlot1, vector<double> vectorPlot2, vector<double> vectorPlot3,
		string titulo1, string titulo2, string titulo3) {
	Gnuplot gp;
	gp << "plot" << gp.file1d(vectorPlot1) << "with lines title '" << titulo1 << "',"
			<< gp.file1d(vectorPlot2) << "with lines title '" << titulo2 << "',"
			<< gp.file1d(vectorPlot3) << "with lines title '" << titulo3 << "'" << endl;
}

double desvioPadraoBinario(PopulacaoBinario pop, double media, int execucoes) {
	double valorDesvio = 0;
	int qtdIndiv = pop.getQtdIndividuos();
	IndividuoBinario ind;

	for (int var = 0; var < qtdIndiv; ++var) {
		ind = pop.getIndividuo(var);
		valorDesvio += pow((ind.getFitness() - media), 2);
	}
	return sqrt(valorDesvio / execucoes);
}

double desvioPadraoReal(PopulacaoReal pop, double media, int execucoes) {
	double valorDesvio = 0;
	int qtdIndiv = pop.getQuantidadeIndividuos();
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
	int qtdIndiv = pop.getQuantidadeIndividuos();
	IndividuoReal ind;
	for (int var = 0; var < qtdIndiv; ++var) {
		ind = pop.getIndividuo(var);
		valorTotal += ind.getFitness();
	}
	return valorTotal / qtdIndiv;
}
