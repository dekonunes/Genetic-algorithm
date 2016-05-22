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
	this->funcaoObjetivo = 0.0;
	this->fitness = 0.0;
	calculoFitness();
}

IndividuoReal::~IndividuoReal() {
	// TODO Auto-generated destructor stub
}

double IndividuoReal::calculoFitness() {
	this->fitness = 1000 - calculoFucaoObjetivo();
	//cout << "===" << this->funcaoObjetivo << endl;
	if (this->fitness < 0)
		this->fitness = 0;

	return this->fitness;
}

double IndividuoReal::calculoFucaoObjetivo() {
	this->funcaoObjetivo = 0.0;
	/*for (int var = 0; var < this->genes.size() - 1; ++var) {
	 this->funcaoObjetivo += (this->genes[var] * this->genes[var]);
	 }*/
	/*for (int var = 0; var < this->genes.size() - 1; ++var) {
	 this->funcaoObjetivo += pow(
	 cos((double) (2 * this->genes[var] * this->genes[var])) - 0.11e1, 0.2e1)
	 + pow(sin(0.5e0 * (double) this->genes[var]) - 0.12e1, 0.2e1)
	 - pow(cos((double) (2 * this->genes[var + 1] * this->genes[var + 1])) - 0.11e1,
	 0.2e1) + pow(sin(0.5e0 * (double) this->genes[var + 1]) - 0.12e1, 0.2e1);
	 }*/
	//this->funcaoObjetivo = cos(20 * this->genes[0]) - (abs(this->genes[0]) / 2) + ((this->genes[0] * this->genes[0] * this->genes[0]) / 4);
	for (int var = 0; var < this->genes.size() - 1; ++var) {
		this->funcaoObjetivo += pow(pow(this->genes[var], 2) + pow(this->genes[var + 1], 2), 0.25)
				* (pow(
						sin(
								50.0
										* pow(
												pow(this->genes[var], 2)
														+ pow(this->genes[var + 1], 2),
												(double) 0.1)), 2)
						* (pow(
								sin(
										50.0
												* pow(
														pow(this->genes[var], 2)
																+ pow(this->genes[var + 1], 2),
														(double) 0.1)), 2) + 1));
	}
	//cout << "++" << this->funcaoObjetivo << endl;
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
	double delta = numRandomDelta(mt) / 100;
	static uniform_int_distribution<int> numRandom(0, 100);
	int numRand = numRandom(mt);
	if (numRand < this->probMutacao) {
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

void IndividuoReal::openJson() {
	using json = nlohmann::json;
	ifstream texto("entrada.json");

	stringstream buffer;
	buffer << texto.rdbuf();

	this->entrada = json::parse(buffer.str());
}

} /* namespace std */
