/*
 * IndividuoBinario.cpp
 *
 *  Created on: 16 de abr de 2016
 *      Author: deko
 */

#include "IndividuoBinario.hpp"

namespace std {

IndividuoBinario::IndividuoBinario() {
	// TODO Auto-generated constructor stub
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 1);
	string aux;
	pair<int, int> auxGenes;

	openJson();
	this->cromossomo.clear();
	for (int count = 0; count < this->entrada["qtdVariaveis"]; ++count) {
		auxGenes.first = this->entrada["variaveis"][count]["min"];
		auxGenes.second = this->entrada["variaveis"][count]["max"];
		this->genes.push_back(auxGenes);
	}

	for (int count = 0; count < this->genes.size(); ++count) {
		this->quantidadeBitsCadaGene.push_back(
				getNumeroBits(this->entrada["variaveis"][count]["max"],
						this->entrada["variaveis"][count]["min"],
						this->entrada["variaveis"][count]["precisao"]));
	}

	for (int var = 0; var < this->genes.size(); ++var) {
		for (int i = 0; i < this->quantidadeBitsCadaGene.at(var); i++) {
			this->cromossomo += static_cast<ostringstream*>(&(ostringstream() << bit(mt)))->str();
		}
	}

	this->probMutacao = this->entrada["chanceMutacao"];
	this->funcaoObjetivo = 0.0;
	this->fitness = 0.0;
	calculoFitness();
}

IndividuoBinario::~IndividuoBinario() {
	// TODO Auto-generated constructor stub
}

string IndividuoBinario::getCromossomo() const {
	return this->cromossomo;
}

void IndividuoBinario::setCromossomo(string cromossomo) {
	this->cromossomo = cromossomo;
}

double IndividuoBinario::getFitness() {
	calculoFitness();
	return this->fitness;
}

double IndividuoBinario::calculoFitness() {
	this->fitness = calculoFucaoObjetivo();
	if (this->fitness < 0)
		this->fitness = 0;
	return this->fitness;
}

double IndividuoBinario::calculoFucaoObjetivo() {
	int var2 = 0;
	this->funcaoObjetivo = 0.0;
	string gene;

	for (int count = 0; count < this->genes.size(); ++count) {
		for (int var = 0; var < this->quantidadeBitsCadaGene.at(count); ++var) {
			gene = gene + this->cromossomo[var2];
			var2++;
		}
		//this->funcaoObjetivo += fullyDeceptiveF3(gene);
		this->funcaoObjetivo += deceptive(gene);

		gene.clear();
	}

	return this->funcaoObjetivo;
}

int IndividuoBinario::fullyDeceptiveF3(string bits) {
	if (bits == "000") {
		return 28;
	}
	if (bits == "001") {
		return 26;
	}
	if (bits == "010") {
		return 22;
	}
	if (bits == "011") {
		return 0;
	}
	if (bits == "100") {
		return 14;
	}
	if (bits == "101") {
		return 0;
	}
	if (bits == "110") {
		return 0;
	}
	if (bits == "111") {
		return 30;
	}
	return 0;
}

int IndividuoBinario::deceptive(string bits) {
	int resultado = 0;
	for (int count = 0; count < 4; ++count)
		if (bits[count] == '1')
			resultado++;
	if (resultado == 0)
		resultado = 5;
	return resultado;
}

void IndividuoBinario::mutacao() {
	int numRand;
	static mt19937 mt(time(NULL));
	for (int loopCromossomos = 0; loopCromossomos < this->cromossomo.size(); ++loopCromossomos) {
		static uniform_int_distribution<int> numRandom(0, 100);
		numRand = numRandom(mt);
		if (numRand < this->probMutacao) {
			if (this->cromossomo[loopCromossomos] == '1')
				this->cromossomo[loopCromossomos] = '0';
			else
				this->cromossomo[loopCromossomos] = '1';
		}
	}
}

const double IndividuoBinario::decodificaCromossomo(int max, int min, string gene) {
	int l = getNumeroBits(max, min, 0);
	int decimal, x, x_max = max, x_min = min;
	decimal = binToDec(gene);
	x = x_min + (((x_max - x_min) / (pow(2, l) - 1)) * decimal);
	return x;
}

double IndividuoBinario::getFuncaoObjetivo() {
	calculoFucaoObjetivo();
	return this->funcaoObjetivo;
}

int IndividuoBinario::getNumeroBits(double x_max, double x_min, int precisao) {
	int numBits = (x_max - x_min) / pow(10, -precisao);
	return log2(numBits) + 1;
}

const int IndividuoBinario::posGeneNoCromosso(int posGene) {
	int posicao = 0;
	for (int var = 0; var < posGene; ++var) {
		posicao += this->quantidadeBitsCadaGene.at(var);
	}
	return posicao;
}

string IndividuoBinario::decToBin(int number) {
	if (number == 0)
		return "0";
	if (number == 1)
		return "1";
	if (number % 2 == 0)
		return decToBin(number / 2) + "0";
	else
		return decToBin(number / 2) + "1";
}

int IndividuoBinario::binToDec(string number) {
	return stoi(number, nullptr, 2);
}

const int IndividuoBinario::getNumeroBitsTotal() {
	int quantidadeTotalBits = 0;
	for (int count = 0; count < this->genes.size(); ++count)
		quantidadeTotalBits += this->quantidadeBitsCadaGene.at(count);
	return quantidadeTotalBits;
}

void IndividuoBinario::openJson() {
	using json = nlohmann::json;
	ifstream texto("entrada.json");
	if (!texto)
		cout << "dont open" << endl;
	stringstream buffer;
	buffer << texto.rdbuf();
	this->entrada = json::parse(buffer.str());
	texto.close();
}

} /* namespace std */
