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

float Individuo::getFitness() const {
	return fitness;
}

void Individuo::setFitness(int fitness) {
	this->fitness = fitness;
}

float Individuo::calculoFitness() {
	this->fitness = 4.0;
	float x = decodificaCromossomo();

	this->fitness += cos(20 * x) - (abs(x) / 2) + ((x * x * x) / 4);
	return this->fitness;
}

float Individuo::calculoFucaoObjetivo() {
	this->fitness = 0.0;
	float x = decodificaCromossomo();

	this->fitness += cos(20 * x) - (abs(x) / 2) + ((x * x * x) / 4);
	return this->fitness;
}

void Individuo::mutacao() {
	int numRand, probabilidade = 1;
	static mt19937 mt(time(NULL));
	string oldCromossomo = getCromossomo(), newCromossomo = getCromossomo();

	for (int loopCromossomos = 0; loopCromossomos < this->qtdBits - 1;
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
	int result = 0, pow = 1;
	for (int i = number.length() - 1; i >= 0; --i, pow <<= 1)
		result += (number[i] - '0') * pow;

	return result;
}

const float Individuo::decodificaCromossomo() {
	int l = 16;
	float decimal, x, x_max = 2, x_min = -2;

	decimal = binToDec(this->cromossomo) * 0.0001;
	x = x_min + ((x_max - x_min) / (2 ^ (l) - 1)) * decimal;
	//cout << decimal << "  " << x << endl;
	return x;
}
