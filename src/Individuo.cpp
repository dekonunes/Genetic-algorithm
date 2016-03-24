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
	this->qtdBits[1] = getNumeroBits(16, 0, 0); //Para radios LX

	for (int var = 0; var < genes.size(); ++var) {
		for (int i = 0; i < this->qtdBits[var]; i++) {
			aux =
					static_cast<ostringstream*>(&(ostringstream() << bit(mt)))->str();
			this->cromossomo = this->cromossomo + aux;
		}
	}
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

void Individuo::calculoFitness() {
	float x = decodificaCromossomo();
	this->fitness = (cos(20 * x) - (abs(x) / 2) + ((x * x * x) / 4)) + 4;
}

void Individuo::calculoFucaoObjetivo() {
	this->funcaoObjetivo = 0.0;
	float x = decodificaCromossomo();

	this->funcaoObjetivo = cos(20 * x) - (abs(x) / 2) + ((x * x * x) / 4);
}

void Individuo::mutacao() {

	int numRand, probabilidade = 1;
	static mt19937 mt(time(NULL));
	string oldCromossomo = getCromossomo(), newCromossomo = getCromossomo();
	for (int var = 0; var < genes.size(); ++var) {
		for (int loopCromossomos = 0; loopCromossomos < this->qtdBits[var] - 1;
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
	float decimal, x, x_max = 2.0, x_min = -2.0;

	decimal = binToDec(this->cromossomo);
	x = x_min + (((x_max - x_min) / (pow(2, 16) - 1)) * decimal);
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

const int Individuo::restricaoMaiorIgual(int posGene, int valorRestricao) {
	int valorGeneInt;
	string stringGene;

	for (int var = 0; var < this->qtdBits[posGene]; ++var) {
		stringGene = stringGene
				+ this->cromossomo[posGeneNoCromosso(posGene) + var];
	}
	cout << binToDec(stringGene) << endl;
	if (binToDec(stringGene) >= valorRestricao)
		return 1; //atingiu a restrição
	return 0; //não atingiu a restrição
}

const int Individuo::posGeneNoCromosso(int posGene) {
	int posicao = 0;
	for (int var = 0; var < posGene; ++var) {
		posicao += this->qtdBits[var];
	}
	return posicao;
}
