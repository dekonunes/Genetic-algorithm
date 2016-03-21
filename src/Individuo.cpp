/*
 * Individuo.cpp
 *
 *  Created on: 14 de mar de 2016
 *      Author: deko
 */

#include "Individuo.hpp"

Individuo::Individuo(int qtdgenes, int qtdBits) {
	// TODO Auto-generated constructor stub

	this->qtdgenes = qtdgenes;
	this->qtdBits = qtdBits;
	this->fitness = 0;
	string aux;
	string cromossomo;

	static mt19937 mt(time(NULL));

	static uniform_int_distribution<int> bit(0, 1);

	//cout << bit(mt) << endl;
	for (int i = 0; i < qtdBits; i++) {
		aux = static_cast<ostringstream*>(&(ostringstream() << bit(mt)))->str();
		this->cromossomo = this->cromossomo + aux;
	}
	calculoFitness();
}

Individuo::Individuo() {
	// TODO Auto-generated destructor stub
}

Individuo::~Individuo() {
	// TODO Auto-generated destructor stub
}

const string& Individuo::getCromossomo() const {
	return cromossomo;
}

void Individuo::setCromossomo(const string& cromossomo) {
	this->cromossomo = cromossomo;
}

int Individuo::getQtdgenes() const {
	return qtdgenes;
}

int Individuo::getQtdBits() const {
	return qtdBits;
}

int Individuo::getFitness() const {
	return fitness;
}

void Individuo::setFitness(int fitness) {
	this->fitness = fitness;
}

int Individuo::calculoFitness() {
	this->fitness = 0;
	for (int var = 1; var < this->qtdBits; ++var) {
		if (this->cromossomo[var] != this->cromossomo[var - 1])
			this->fitness++;
	}
	return this->fitness;
}

void Individuo::mutacao() {
	int numRand, probabilidade = 2;
	static mt19937 mt(time(NULL));
	string oldCromossomo = getCromossomo(), newCromossomo = getCromossomo();

	for (int loopCromossomos = 0; loopCromossomos < this->qtdBits;
			++loopCromossomos) {

		static uniform_int_distribution<int> numRandom(0, 100);

		numRand = numRandom(mt);

		if (numRand < probabilidade) {
			if (this->cromossomo[loopCromossomos] == '1') {
				this->cromossomo[loopCromossomos] = '0';
			} else
				this->cromossomo[loopCromossomos] = '1';
		}
	}

}
