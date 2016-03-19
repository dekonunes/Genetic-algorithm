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
