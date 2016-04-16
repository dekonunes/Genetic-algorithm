/*
 * Individuo.cpp
 *
 *  Created on: 14 de mar de 2016
 *      Author: deko
 */

#include "Individuo.hpp"

Individuo::Individuo(vector<pair<int, int>> genes, int probMutacao) {
	// TODO Auto-generated constructor stub
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 1);
	string aux;
	string cromossomo;
	for (int var = 0; var < genes.size(); ++var) {
		this->qtdBits[var] = getNumeroBits(genes[var].second, genes[var].first, 0);
	}

	for (int var = 0; var < genes.size(); ++var) {
		for (int i = 0; i < this->qtdBits[var]; i++) {
			aux = static_cast<ostringstream*>(&(ostringstream() << bit(mt)))->str();
			this->cromossomo = this->cromossomo + aux;
		}
	}
	this->probMutacao = probMutacao;
	this->genesB = genes;
	this->fitness = 0.0;
	calculoFitness();
}

Individuo::Individuo(vector<pair<double, double>> genesInicial, int probMutacao) {
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

double Individuo::getFitness() {
	calculoFitness();
	return this->fitness;
}

double Individuo::calculoFitness() {
	/*for (int var = 0; var < this->genesF.size(); ++var) {
		this->fitness += 25.0 - (this->genesF[var] * this->genesF[var]);
	}*/
	this->fitness = 25.0 - (this->genesF[0] * this->genesF[0]);
	if(this->fitness < 0)
		this->fitness = 0;
	return this->fitness;
}

double Individuo::calculoFucaoObjetivo() {
	this->funcaoObjetivo = (this->genesF[0] * this->genesF[0]);
	return this->funcaoObjetivo;
}

void Individuo::mutacao() {
	double delta = 0.05;
	int numRand, probabilidade = this->probMutacao;
	static mt19937 mt(time(NULL));

	static uniform_int_distribution<int> numRandom(0, 100);

	numRand = numRandom(mt);
	if (numRand < probabilidade) {
		static uniform_real_distribution<double> numDelta(-delta, delta);
		this->genesF[0] = this->genesF[0] + numDelta(mt);
	}

}

string Individuo::decToBin(int number) {
	if (number == 0)
		return "0";
	if (number == 1)
		return "1";
	if (number % 2 == 0)
		return decToBin(number / 2) + "0";
	else
		return decToBin(number / 2) + "1";
}

int Individuo::binToDec(string number) {
	/*int result = 0, pow = 1;
	 for (int i = number.length() - 1; i >= 0; --i, pow <<= 1)
	 result += (number[i] - '0') * pow;
	 return result;//stoi(number,nullptr,2);*/
	return stoi(number, nullptr, 2);
}

const double Individuo::decodificaCromossomo(int max, int min, string gene) {
	int l = getNumeroBits(max, min, 0);
	int decimal, x, x_max = max, x_min = min;
	decimal = binToDec(gene);
	x = x_min + (((x_max - x_min) / (pow(2, l) - 1)) * decimal);
	return x;
}

double Individuo::getFuncaoObjetivo() {
	calculoFucaoObjetivo();
	return this->funcaoObjetivo;
}

int Individuo::getNumeroBits(double x_max, double x_min, int precisao) {
	int numBits = (x_max - x_min) / pow(10, -precisao);
	return log2(numBits) + 1;
}

const int Individuo::posGeneNoCromosso(int posGene) {
	int posicao = 0;
	for (int var = 0; var < posGene; ++var) {
		posicao += this->qtdBits[var];
	}
	return posicao;
}

const vector<double>& Individuo::getGenesF() const {
	return genesF;
}

void Individuo::setGenesF(const vector<double>& genesF) {
	this->genesF = genesF;
}
