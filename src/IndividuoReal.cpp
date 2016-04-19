/*
 * IndividuoReal.cpp
 *
 *  Created on: 16 de abr de 2016
 *      Author: deko
 */

#include "IndividuoReal.hpp"

namespace std {

IndividuoReal::IndividuoReal() {
	static mt19937 mt(time(NULL));
	pair<double, double> auxGenesIniciais;
	openJson();
	for (int var = 0; var < this->entrada["qtdVariaveis"]; ++var) {
		static uniform_real_distribution<double> bit(this->entrada["variaveis"][var]["min"],
				this->entrada["variaveis"][var]["max"]);
		this->genes.push_back(bit(mt));
		auxGenesIniciais.first = this->entrada["variaveis"][var]["min"];
		auxGenesIniciais.second = this->entrada["variaveis"][var]["max"];
		this->genesFInicial.push_back(auxGenesIniciais);
	}
	this->probMutacao = this->entrada["chanceMutacao"];
	this->fitness = 0.0;
	calculoFitness();
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
	static mt19937 mt(time(NULL));
	pair<double, double> genesIniciais = this->genesFInicial[0];
	static uniform_real_distribution<double> numRandomDelta(genesIniciais.first,
			genesIniciais.second);
	double delta = numRandomDelta(mt)/100;
	static uniform_int_distribution<int> numRandom(0, 100);
	int numRand = numRandom(mt);
	if (numRand < this->probMutacao) {
		static uniform_real_distribution<double> numDelta(-delta, delta);
		//cout << this->genes[0] << endl;
		this->genes[0] = this->genes[0] + numDelta(mt);
		//cout << this->genes[0] << endl;
	}

}

const vector<double>& IndividuoReal::getGenes() const {
	return genes;
}

void IndividuoReal::setGenes(const vector<double>& genes) {
	this->genes = genes;
}

void IndividuoReal::openJson() {
	using json = nlohmann::json;
	ifstream texto("entrada.json");

	stringstream buffer;
	buffer << texto.rdbuf();

	this->entrada = json::parse(buffer.str());
}

} /* namespace std */