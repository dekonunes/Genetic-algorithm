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
	this->fitness = 2000 - calculoFucaoObjetivo();
	//cout << "===" << this->funcaoObjetivo << endl;
	if (this->fitness < 0)
		this->fitness = 0;

	return this->fitness;
}

double IndividuoReal::calculoFucaoObjetivo() {
	this->funcaoObjetivo = 0.0;
	/*for (int var = 0; var < this->genes.size(); ++var) {
	 this->funcaoObjetivo += (this->genes[var] * this->genes[var]);
	 }*/
	//this->funcaoObjetivo = schaffer();
	this->funcaoObjetivo = ackley();
	//cout << this->genes[1] << endl;
	//this->funcaoObjetivo = rastrigin();
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
	double delta = numRandomDelta(mt) / 10;
	static uniform_int_distribution<int> numRandom(0, 100);
	int numRand = numRandom(mt);
	if (numRand < this->probMutacao) {
		for (int count = 0; count < this->genes.size(); ++count) {
			static uniform_real_distribution<double> numDelta(-delta, delta);
			this->genes[count] = this->genes[count] + numDelta(mt);
		}
	}
}

void IndividuoReal::gaussianMutation() {
	static mt19937 mt(time(NULL));
	static uniform_real_distribution<double> numRandon(0, 1);
	static uniform_int_distribution<int> numRandomProbabilidade(1, 100);
	double y1, x1, x2, sigma = 1;

	if (numRandomProbabilidade(mt) < this->probMutacao) {
		for (int count = 0; count < this->genes.size(); ++count) {
			x1 = numRandon(mt);
			x2 = numRandon(mt);

			if (x1 == 0)
				x1 = 1;
			if (x2 == 0)
				x2 = 1;

			y1 = sqrt(-2.0 * log(x1)) * cos(2.0 * M_PI * x2);

			this->genes[count] = y1 * sigma + this->genes[count];
		}
	}
}

const vector<double>& IndividuoReal::getGenes() const {
	return genes;
}

void IndividuoReal::setGenes(const vector<double>& genes) {
	this->genes = genes;
}

double IndividuoReal::schaffer() {
	double resultado = 0;
	for (int var = 0; var < this->genes.size() - 1; ++var)
		resultado += pow(pow(this->genes[var], 2) + pow(this->genes[var + 1], 2), 0.25)
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
	return resultado;
}

double IndividuoReal::ackley() {
	double aux = 0, aux1 = 0;
	for (int var = 0; var < this->genes.size(); ++var) {
		aux += this->genes[var] * this->genes[var];
		aux1 += cos(2.0 * M_PI * this->genes[var]);
	}
	return (-20.0 * (exp(-0.2 * sqrt(1.0 / (double) this->genes.size() * aux)))
			- exp(1.0 / (double) this->genes.size() * aux1) + 20.0 + exp(1));
}

double IndividuoReal::rastrigin() {
	double resultado = 0;
	for (int var = 0; var < this->genes.size() - 1; ++var)
		resultado +=
				(pow(this->genes[var], (double) 2) - 10 * cos(2 * M_PI * this->genes[var]) + 10);
	return resultado;
}

void IndividuoReal::testBolds() {
	for (int count = 0; count < this->genes.size(); ++count) {
		if (this->genes[count] < this->entrada["variaveis"][0]["min"])
			this->genes[count] = this->entrada["variaveis"][0]["min"];

		if (this->genes[count] > this->entrada["variaveis"][0]["max"])
			this->genes[count] = this->entrada["variaveis"][0]["max"];
	}

}

void IndividuoReal::openJson() {
	using json = nlohmann::json;
	ifstream texto("entrada.json");
	stringstream buffer;
	buffer << texto.rdbuf();
	this->entrada = json::parse(buffer.str());
	texto.close();
}

} /* namespace std */
