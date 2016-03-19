/*
 * Populacao.cpp
 *
 *  Created on: 15 de mar de 2016
 *      Author: deko
 */

#include "Populacao.hpp"

namespace std {

Populacao::Populacao(int qtdIndividuos, int qtdGenes, int qtdBits) :
		bestIndividuo(qtdGenes, qtdBits) {
	// TODO Auto-generated constructor stub
	for (int var = 0; var < qtdIndividuos; ++var) {
		this->populacao.push_back(Individuo(qtdGenes, qtdBits));
	}
	this->qtdIndividuos = qtdIndividuos;
	this->qtdBits = qtdBits;
	this->qtdGenes = qtdGenes;
}

Populacao::Populacao() :
		bestIndividuo(qtdGenes, qtdBits) {
}

Populacao::~Populacao() {
	// TODO Auto-generated destructor stub
}

void Populacao::print_populacao() {
	for (int i = 0; i < this->populacao.size(); ++i)
		cout << this->populacao[i].getCromossomo() << endl;
}

void Populacao::print_individuo(int id) {
	cout << this->populacao[id].getCromossomo() << endl;
}

void Populacao::insertIndividuo(Individuo newIndividuo) {
	this->populacao.push_back(newIndividuo);
}

const vector<Individuo>& Populacao::getPopulacao() const {
	return populacao;
}

void Populacao::setPopulacao(const vector<Individuo>& populacao) {
	this->populacao = populacao;
}

const Individuo Populacao::getIndividuo(int index) {
	return this->populacao[index];
}

const Individuo Populacao::getBestIndividuo() {
	for (int var = 0; var < this->populacao.size(); ++var) {
		if (this->bestIndividuo.getFitness()
				< this->populacao[var].calculoFitness()) {
			this->bestIndividuo = this->populacao[var];
		}
	}
	return this->bestIndividuo;
}

const vector<Individuo>& Populacao::crossover(int individuo1,int individuo2) const {
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 100);
	int var, a = bit(mt), chanceCrossover = 90;
	vector<Individuo> newIndividuos;
	Individuo newIndividuo1(this->qtdGenes, this->qtdBits);
	Individuo newIndividuo2(this->qtdGenes, this->qtdBits);
	if (chanceCrossover > a) {
		string cromossomoInviduio1 = this->populacao[individuo1].getCromossomo();
		string cromossomoInviduio2 = this->populacao[individuo2].getCromossomo();
		string cromossomoNewInviduio1;
		string cromossomoNewInviduio2;

		static uniform_int_distribution<int> bit(0, this->qtdBits - 1);
		a = bit(mt);
		cout << a << endl;
		for (var = 0; var < a; ++var) {
			cromossomoNewInviduio1 = cromossomoNewInviduio1
					+ cromossomoInviduio1[var];
			cromossomoNewInviduio2 = cromossomoNewInviduio2
					+ cromossomoInviduio2[var];

		}
		for (; var < this->qtdBits; ++var) {
			cromossomoNewInviduio1 = cromossomoNewInviduio1
					+ cromossomoInviduio2[var];
			cromossomoNewInviduio2 = cromossomoNewInviduio2
					+ cromossomoInviduio1[var];
		}
		newIndividuo1.setCromossomo(cromossomoNewInviduio1);
		newIndividuo2.setCromossomo(cromossomoNewInviduio2);
	}
	cout << newIndividuo1.getCromossomo() << endl;
	cout << newIndividuo2.getCromossomo() << endl;

	return newIndividuos;
}

const Populacao Populacao::crossoverRollet() {
	static mt19937 mt(time(NULL));
	vector<Individuo> newIndivuos;
	Populacao newPop(this->qtdIndividuos, this->qtdGenes, this->qtdBits);
	int valorTotalFitness = 0, var, valorDaRollet,individuoParaCross[1];
	float valorAcumuladoFitness = 0.0;
	//Individuo individuoParaCross1(this->qtdGenes,this->qtdBits),individuoParaCross2(this->qtdGenes,this->qtdBits);

	for (var = 0; var < this->qtdIndividuos; ++var) {
		valorTotalFitness += this->getIndividuo(var).getFitness();
	}

	cout << valorTotalFitness << endl;

	for (int loop = 0; loop < 2; ++loop) {
		static uniform_int_distribution<int> numeroRandom(0, 100);
		valorDaRollet = numeroRandom(mt);
		for (var = 0; var < this->qtdIndividuos; ++var) {
			valorAcumuladoFitness +=
					((float) this->getIndividuo(var).getFitness()
							/ valorTotalFitness) * 100;
			//cout << valorAcumuladoFitness << endl;
			if (valorDaRollet < valorAcumuladoFitness)
				break;
		}
		cout << valorDaRollet << " fitnes: " << valorAcumuladoFitness << endl;
		valorAcumuladoFitness = 0;
		individuoParaCross[loop] = var;
		cout << var << endl;
	}
	newIndivuos = crossover(individuoParaCross[0],individuoParaCross[1]);
	newPop.insertIndividuo(newIndivuos[0]);
	newPop.insertIndividuo(newIndivuos[1]);
	return newPop;
}

} /* namespace std */
