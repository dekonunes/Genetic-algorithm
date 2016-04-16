/*
 * Populacao.cpp
 *
 *  Created on: 15 de mar de 2016
 *      Author: deko
 */

#include "PopulacaoReal.hpp"

namespace std {

PopulacaoReal::PopulacaoReal(int qtdIndividuos, vector<pair<double, double>> genes, int chanceCrossover,
		int probMutacao, int eletismo) {
	// TODO Auto-generated constructor stub
	for (int var = 0; var < qtdIndividuos; ++var) {
		this->populacao.push_back(Individuo(genes, probMutacao));
	}
	this->qtdIndividuos = qtdIndividuos;
	this->chanceCrossover = chanceCrossover;
	this->eletismo = eletismo;
}

PopulacaoReal::PopulacaoReal() {
	// TODO Auto-generated destructor stub
}

PopulacaoReal::~PopulacaoReal() {
	// TODO Auto-generated destructor stub
}

void Populacao::print_populacao() {
	for (int i = 0; i < this->populacao.size(); ++i)
		cout << this->populacao[i].getCromossomo() << endl;
}

void Populacao::print_individuo(int id) {
	cout << this->populacao[id].getCromossomo() << endl;
}

const pair<Individuo, Individuo> PopulacaoReal::crossoverUniforme(int individuo1, int individuo2) {
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 100);
	int var, a = bit(mt);
	int qtdBits = this->populacao[individuo1].getCromossomo().size();
	pair<Individuo, Individuo> newIndividuosCrossover;
	Individuo newIndividuo1 = this->populacao[individuo1];
	Individuo newIndividuo2 = this->populacao[individuo2];

	if (this->chanceCrossover > a) {

		string cromossomoNewInviduio1 = this->populacao[individuo1].getCromossomo();
		string cromossomoNewInviduio2 = this->populacao[individuo2].getCromossomo();
		for (int var = 0; var < this->populacao[individuo1].getCromossomo().size(); ++var) {
			static uniform_int_distribution<int> numRandon(0, 1);
			a = numRandon(mt);

			if (a == 1) {
				cromossomoNewInviduio1[var] = this->populacao[individuo2].getCromossomo()[var];
				cromossomoNewInviduio2[var] = this->populacao[individuo1].getCromossomo()[var];
			}

		}
		newIndividuo1.setCromossomo(cromossomoNewInviduio1);
		newIndividuo2.setCromossomo(cromossomoNewInviduio2);
	}
	if (this->eletismo == true)
		newIndividuosCrossover = make_pair(newIndividuo1, newIndividuo2);

	return newIndividuosCrossover;
}

const pair<Individuo, Individuo> Populacao::crossover(int individuo1, int individuo2) {
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 99);
	int var, a = bit(mt);
	int qtdBits = this->populacao[individuo1].getCromossomo().size();
	pair<Individuo, Individuo> newIndividuosCrossover;
	Individuo newIndividuo1 = this->populacao[individuo1];
	Individuo newIndividuo2 = this->populacao[individuo2];
	vector<double> genesInd1, genesInd2;
	if (this->chanceCrossover > a) {
		static uniform_int_distribution<int> numRandon(0,
				this->populacao[individuo1].getGenesF().size() - 1);
		a = numRandon(mt);
		for (var = 0; var < a; ++var) {
			genesInd1.push_back(this->populacao[individuo2].getGenesF().at(var));
			genesInd2.push_back(this->populacao[individuo1].getGenesF().at(var));
		}
		for (; var < this->populacao[individuo1].getGenesF().size(); ++var) {
			genesInd1.push_back(this->populacao[individuo1].getGenesF().at(var));
			genesInd2.push_back(this->populacao[individuo2].getGenesF().at(var));
		}
	} else {
		newIndividuo1.setGenesF(this->populacao[individuo1].getGenesF());
		newIndividuo2.setGenesF(this->populacao[individuo2].getGenesF());
	}
	newIndividuo1.setGenesF(genesInd1);
	newIndividuo2.setGenesF(genesInd2);
	newIndividuosCrossover = make_pair(newIndividuo1, newIndividuo2);

	return newIndividuosCrossover;
}

const PopulacaoReal PopulacaoReal::rollet() {
	static mt19937 mt(time(NULL));
	pair<Individuo, Individuo> newIndivuos;
	PopulacaoReal newPop;
	int var, valorDaRollet = 0, individuoParaCross[1] { 0 }, auxInsertIndv = 0;
	double valorTotalFitness = 0.0;
	double valorAcumuladoFitness = 0.0;
	for (var = 0; var < this->qtdIndividuos; ++var) {
		valorTotalFitness += this->populacao[var].getFitness();
	}
	for (int loopNovosIndiv = 0; loopNovosIndiv < this->qtdIndividuos / 2; ++loopNovosIndiv) {
		for (int loop = 0; loop < 2; ++loop) {
			static uniform_int_distribution<int> numeroRandom(0, 100);
			valorDaRollet = numeroRandom(mt);
			for (var = 0; var < this->qtdIndividuos - 1; ++var) {

				valorAcumuladoFitness += ((double) this->populacao[var].getFitness()
						/ valorTotalFitness) * 100;
				if (valorDaRollet < valorAcumuladoFitness)
					break;
			}
			valorAcumuladoFitness = 0;
			individuoParaCross[loop] = var;
		}

		newIndivuos = crossover(individuoParaCross[0], individuoParaCross[1]);
		newPop.insertIndividuo(newIndivuos.first);
		newPop.insertIndividuo(newIndivuos.second);
	}
	newPop.atualizaPiorIndvNaPopulacao(this->getBestIndividuo());
	return newPop;
}

const PopulacaoReal PopulacaoReal::tournament(int k) {
	static mt19937 mt(time(NULL));
	pair<Individuo, Individuo> newIndivuos;
	Individuo indRand, indAux;
	PopulacaoReal newPop;
	int individuoParaCross[1] { 0 }, auxInsertIndv = 0, indvDoTournament;

	for (int loopNovosIndiv = 0; loopNovosIndiv < this->qtdIndividuos / 2; ++loopNovosIndiv) {
		for (int qtdIndvParaCross = 0; qtdIndvParaCross < 2; ++qtdIndvParaCross) {
			static uniform_int_distribution<int> numeroRandom(0, this->qtdIndividuos - 1);
			indvDoTournament = numeroRandom(mt);
			indAux = this->populacao[indvDoTournament]; //Já encontra o primeiro indv aleatório, já o primeiro k
			for (int var = 0; var < k - 1; ++var) { //k-1 pois o primeiro individuo veio da linha acima
				static uniform_int_distribution<int> numeroRandom(0, this->qtdIndividuos - 1);
				indvDoTournament = numeroRandom(mt);
				indRand = this->populacao[indvDoTournament];
				if (indRand.getFitness() > indAux.getFitness()) {
					individuoParaCross[qtdIndvParaCross] = indvDoTournament;
				}
			}
		}
		newIndivuos = crossover(individuoParaCross[0], individuoParaCross[1]);
		newPop.insertIndividuo(newIndivuos.first);
		newPop.insertIndividuo(newIndivuos.second);
	}
	newPop.atualizaPiorIndvNaPopulacao(this->getBestIndividuo());
	return newPop;
}


} /* namespace std */
