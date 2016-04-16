/*
 * Populacao.cpp
 *
 *  Created on: 15 de mar de 2016
 *      Author: deko
 */

#include "PopulacaoReal.hpp"

namespace std {

PopulacaoReal::PopulacaoReal(int qtdIndividuos, vector<pair<double, double>> genes, int chanceCrossover, int eletismo) {
	// TODO Auto-generated constructor stub
	for (int var = 0; var < qtdIndividuos; ++var) {
		//this->populacao.push_back(IndividuoReal(genes, probMutacao));
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

const pair<IndividuoReal, IndividuoReal> PopulacaoReal::crossover(int individuo1, int individuo2) {
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 99);
	int var, a = bit(mt);
	pair<IndividuoReal, IndividuoReal> newIndividuosCrossover;
	IndividuoReal newIndividuo1 = this->populacao[individuo1];
	IndividuoReal newIndividuo2 = this->populacao[individuo2];
	vector<double> genesInd1, genesInd2;
	if (this->chanceCrossover > a) {
		static uniform_int_distribution<int> numRandon(0,
				this->populacao[individuo1].getGenes().size() - 1);
		a = numRandon(mt);
		for (var = 0; var < a; ++var) {
			genesInd1.push_back(this->populacao[individuo2].getGenes().at(var));
			genesInd2.push_back(this->populacao[individuo1].getGenes().at(var));
		}
		for (; var < this->populacao[individuo1].getGenes().size(); ++var) {
			genesInd1.push_back(this->populacao[individuo1].getGenes().at(var));
			genesInd2.push_back(this->populacao[individuo2].getGenes().at(var));
		}
	} else {
		newIndividuo1.setGenes(this->populacao[individuo1].getGenes());
		newIndividuo2.setGenes(this->populacao[individuo2].getGenes());
	}
	newIndividuo1.setGenes(genesInd1);
	newIndividuo2.setGenes(genesInd2);
	newIndividuosCrossover = make_pair(newIndividuo1, newIndividuo2);

	return newIndividuosCrossover;
}

const PopulacaoReal PopulacaoReal::rollet() {
	static mt19937 mt(time(NULL));
	pair<IndividuoReal, IndividuoReal> newIndivuos;
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
	pair<IndividuoReal, IndividuoReal> newIndivuos;
	IndividuoReal indRand, indAux;
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

int PopulacaoReal::getQtdIndividuos() const {
	return this->populacao.size();
}

void PopulacaoReal::mutacaoPopulacao() {
	for (int var = 0; var < this->qtdIndividuos; ++var) {
		this->populacao[var].mutacao();
	}
}

const vector<IndividuoReal>& PopulacaoReal::getPopulacao() const {
	return this->populacao;
}

void PopulacaoReal::setPopulacao(const vector<IndividuoReal>& populacao) {
	this->populacao = populacao;
}

void PopulacaoReal::insertIndividuo(IndividuoReal newIndividuo) {
	this->populacao.push_back(newIndividuo);
}

const IndividuoReal PopulacaoReal::getIndividuo(int index) {
	return this->populacao[index];
}

IndividuoReal PopulacaoReal::getBestIndividuo() {
	this->bestIndividuo = this->populacao[0];
	for (int var = 0; var < this->populacao.size(); ++var) {
		if (this->bestIndividuo.getFitness() < this->populacao[var].getFitness()) {
			this->bestIndividuo = this->populacao[var];
		}
	}
	return this->bestIndividuo;
}

const IndividuoReal PopulacaoReal::getWorseIndividuo() {
	this->worseIndividuo = this->populacao[0];
	for (int var = 0; var < this->populacao.size(); ++var) {
		if (this->worseIndividuo.getFitness() > this->populacao[var].getFitness()) {
			this->worseIndividuo = this->populacao[var];
		}
	}
	return this->worseIndividuo;
}

void PopulacaoReal::atualizaPiorIndvNaPopulacao(const IndividuoReal& newIndividuo) {
	int posicaoDoPiorIndiv = 0;
	this->worseIndividuo = this->populacao[0];
	for (int var = 0; var < this->populacao.size(); ++var) {
		if (this->worseIndividuo.getFitness() > this->populacao[var].getFitness()) {
			posicaoDoPiorIndiv = var;
		}
	}
	this->populacao[posicaoDoPiorIndiv] = newIndividuo;
}


} /* namespace std */
