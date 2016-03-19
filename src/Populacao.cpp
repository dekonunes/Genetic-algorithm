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
	this->qtdBits = qtdBits;
	this->qtdGenes = qtdGenes;
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

const Individuo Populacao::crossover(Individuo individuo1,
		Individuo individuo2) {
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 100);
	int var, a= bit(mt), chanceCrossover = 80;
	Individuo newIndividuo1(this->qtdGenes, this->qtdBits);
	Individuo newIndividuo2(this->qtdGenes, this->qtdBits);
	newIndividuo1 = individuo1;
	newIndividuo2 = individuo2;
	if (chanceCrossover > a) {
		string cromossomoInviduio1 = individuo1.getCromossomo();
		string cromossomoInviduio2 = individuo2.getCromossomo();
		string cromossomoNewInviduio1;
		string cromossomoNewInviduio2;

		static uniform_int_distribution<int> bit(0, this->qtdBits - 1);
		a = bit(mt);
		cout << bit(mt) << "  " << a << endl;
		for (var = 0; var < a; ++var) {
			//cout <<  cromossomoInviduio1[var] << endl;

			cromossomoNewInviduio1 = cromossomoNewInviduio1
					+ cromossomoInviduio1[var];
			//cout << "a" <<cromossomoNewInviduio1 << endl;
		}
		cout << endl;
		for (; var < this->qtdBits; ++var) {
			cromossomoNewInviduio1 = cromossomoNewInviduio1
					+ cromossomoInviduio2[var];
		}
		newIndividuo1.setCromossomo(cromossomoNewInviduio1);
	}
	return newIndividuo1;
}

} /* namespace std */
