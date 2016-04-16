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
		this->genesF.push_back(bit(mt));
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
	for (int var = 0; var < this->genesF.size(); ++var) {
		this->fitness = 25.0 - (this->genesF[var] * this->genesF[var]);
	}
	if (this->fitness < 0)
		this->fitness = 0;
	return this->fitness;
}

double IndividuoReal::calculoFucaoObjetivo() {
	this->funcaoObjetivo = (this->genesF[0] * this->genesF[0]);
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
		this->genesF[0] = this->genesF[0] + numDelta(mt);
	}

}

const vector<double>& IndividuoReal::getGenesF() const {
	return genesF;
}

void IndividuoReal::setGenesF(const vector<double>& genesF) {
	this->genesF = genesF;
}

} /* namespace std */
