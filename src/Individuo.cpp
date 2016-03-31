/*
 * Individuo.cpp
 *
 *  Created on: 14 de mar de 2016
 *      Author: deko
 */

#include "Individuo.hpp"

Individuo::Individuo(vector<float> genes) {
	// TODO Auto-generated constructor stub
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 1);
	string aux;
	string cromossomo;

	this->qtdBits[0] = getNumeroBits(24, 0, 0); //Para radios ST
	this->qtdBits[1] = getNumeroBits(32, 0, 0); //Para radios LX

	for (int var = 0; var < genes.size(); ++var) {
		for (int i = 0; i < this->qtdBits[var]; i++) {
			aux =
					static_cast<ostringstream*>(&(ostringstream() << bit(mt)))->str();
			this->cromossomo = this->cromossomo + aux;
		}
	}
	this->genes = genes;
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

float Individuo::getFitness() {
	calculoFitness();
	return this->fitness;
}

float Individuo::calculoFitness() {
	int ST, LX, qtdFunc, maxExtrapolaFunc, maxExtrapolaFO;
	float penalidade, aux, r = -1.0;
	string stringGene[10];
	for (int var2 = 0; var2 < this->genes.size(); ++var2) {
		for (int var = 0; var < this->qtdBits[var2]; ++var) {
			stringGene[var2] = stringGene[var2]
					+ this->cromossomo[posGeneNoCromosso(var2) + var];
		}

	}
	ST = (int) decodificaCromossomo(24, 0, stringGene[0]);
	LX = (int) decodificaCromossomo(16, 0, stringGene[1]);
	qtdFunc = ST + (2 * LX);
	maxExtrapolaFunc = (24 + 32) - 40;
	maxExtrapolaFO = 24 * 30 + 16 * 40;

	if (qtdFunc <= 40)
		penalidade = 0;
	else
		penalidade = (float) (qtdFunc - 40) / (float) maxExtrapolaFunc;

	aux = calculoFucaoObjetivo() / maxExtrapolaFO + (r * penalidade);
	if (aux < 0)
		this->fitness = 0;
	else
		this->fitness = aux;

	return this->fitness;
}

float Individuo::calculoFucaoObjetivo() {
	int ST, LX;
	string stringGene[10];
	for (int var2 = 0; var2 < this->genes.size(); ++var2) {
		for (int var = 0; var < this->qtdBits[var2]; ++var) {
			stringGene[var2] = stringGene[var2]
					+ this->cromossomo[posGeneNoCromosso(var2) + var];
		}

	}
	ST = (int) decodificaCromossomo(24, 0, stringGene[0]);
	LX = (int) decodificaCromossomo(16, 0, stringGene[1]);

	this->funcaoObjetivo = ST * 30 + LX * 40;
	return this->funcaoObjetivo;
}

void Individuo::mutacao() {
	int numRand, probabilidade = 1;
	static mt19937 mt(time(NULL));
	string oldCromossomo = getCromossomo(), newCromossomo = getCromossomo();

	for (int loopCromossomos = 0; loopCromossomos < this->cromossomo.size();
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

const float Individuo::decodificaCromossomo(int max, int min, string gene) {
	int l = getNumeroBits(max, min, 0);
	int decimal, x, x_max = max, x_min = min;
	decimal = binToDec(gene);
	x = x_min + (((x_max - x_min) / (pow(2, l) - 1)) * decimal);
	return x;
}

float Individuo::getFuncaoObjetivo() {
	calculoFucaoObjetivo();
	return this->funcaoObjetivo;
}

int Individuo::getNumeroBits(float x_max, float x_min, int precisao) {
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
