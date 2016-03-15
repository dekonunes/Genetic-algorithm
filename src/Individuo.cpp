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

	double ran;
	int bit;
	string aux;
	string cromossomo;
	static MersenneTwister mt;
	static bool mt_started;

	if(!mt_started){	
		mt.init_genrand(time(NULL));
		mt_started = true;
	}

	for (int i = 0; i < qtdBits; i++) {
		ran = mt.random();
		//cout << ran << endl;
		if (ran < 0.5) {
			bit = 0;
		} else
			bit = 1;
		//cout << bit << endl;
		aux = static_cast<ostringstream*>( &(ostringstream() << bit) )->str();
		this->cromossomo = this->cromossomo + aux;

	}
	//cout << this->cromossomo << endl;

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
