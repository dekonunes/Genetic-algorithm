/*
 * IndividuoReal.cpp
 *
 *  Created on: 16 de abr de 2016
 *      Author: deko
 */

#include "IndividuoReal.hpp"

namespace std {

IndividuoReal::IndividuoReal(vector<pair<double, double>> genesInicial, int probMutacao) {
	// TODO Auto-generated constructor stub
	static mt19937 mt(time(NULL));

	for (int var = 0; var < genesInicial.size(); ++var) {
		static uniform_real_distribution<double> bit(genesInicial[var].first,
				genesInicial[var].second);
		this->genes.push_back(bit(mt));
	}
	this->probMutacao = probMutacao;
	this->fitness = 0.0;
	calculoFitness();
}

IndividuoReal::IndividuoReal() {
	// TODO Auto-generated destructor stub
}

IndividuoReal::~IndividuoReal() {
	// TODO Auto-generated destructor stub
}

double IndividuoReal::calculoFitness() {
	for (int var = 0; var < this->genes.size(); ++var) {
		this->fitness = 25.0 - (this->genes[var] * this->genes[var]);
	}
	if (this->fitness < 0)
		this->fitness = 0;
	return this->fitness;
}

double IndividuoReal::calculoFucaoObjetivo() {
	this->funcaoObjetivo = (this->genes[0] * this->genes[0]);
	return this->funcaoObjetivo;
}

double IndividuoReal::getFitness() {
	calculoFitness();
	return this->fitness;
}

double IndividuoReal::getFuncaoObjetivo() {
	calculoFucaoObjetivo();
	return this->funcaoObjetivo;
}

void IndividuoReal::mutacao() {
	double delta = 0.005;
	int numRand, probabilidade = this->probMutacao;
	static mt19937 mt(time(NULL));

	static uniform_int_distribution<int> numRandom(0, 100);

	numRand = numRandom(mt);
	if (numRand < probabilidade) {
		static uniform_real_distribution<double> numDelta(-delta, delta);
		this->genes[0] = this->genes[0] + numDelta(mt);
	}

}

const vector<double>& IndividuoReal::getGenes() const {
	return genes;
}

void IndividuoReal::setGenes(const vector<double>& genes) {
	this->genes = genes;
}

} /* namespace std */
