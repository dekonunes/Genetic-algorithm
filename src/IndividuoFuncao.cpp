/*
 * IndividuoFuncao.cpp
 *
 *  Created on: 21 de mar de 2016
 *      Author: deko
 */

#include "IndividuoFuncao.hpp"

namespace std {

IndividuoFuncao::IndividuoFuncao(int qtdgenes, int qtdBits) {
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

IndividuoFuncao::~IndividuoFuncao() {
	// TODO Auto-generated destructor stub
}

const string& IndividuoFuncao::getCromossomo() const {
	return cromossomo;
}

void IndividuoFuncao::setCromossomo(const string& cromossomo) {
	this->cromossomo = cromossomo;
}

int IndividuoFuncao::getFitness() const {
	return fitness;
}

void IndividuoFuncao::setFitness(int fitness) {
	this->fitness = fitness;
}

int IndividuoFuncao::getQtdBits() const {
	return qtdBits;
}

int IndividuoFuncao::getQtdgenes() const {
	return qtdgenes;
}

int IndividuoFuncao::calculoFitness() {
	cout << this->cromossomo << endl;
	int x = binToDec(this->cromossomo);
	float y = x*0.0001;
	cout << x << endl;
	cout << y << endl;
	this->fitness = 4 + cos(20*x) - (abs(x)/2) + (x*x*x/4);

	return this->fitness;
}


string IndividuoFuncao::decToBin(int number) {
	if (number == 0)
		return "0";
	if (number == 1)
		return "1";

	if (number % 2 == 0)
		return decToBin(number / 2) + "0";
	else
		return decToBin(number / 2) + "1";
}

int IndividuoFuncao::binToDec(string number) {
	int result = 0, pow = 1;
	for (int i = number.length() - 1; i >= 0; --i, pow <<= 1)
		result += (number[i] - '0') * pow;

	return result;
}

} /* namespace std */
