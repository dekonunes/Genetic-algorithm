/*
 * Populacao.cpp
 *
 *  Created on: 15 de mar de 2016
 *      Author: deko
 */

#include "Populacao.hpp"

namespace std {

Populacao::Populacao(int qtdIndividuos, int qtdGenes, int qtdBits) {
	// TODO Auto-generated constructor stub
	for (int var = 0; var < qtdIndividuos; ++var) {
		this->populacao.push_back(Individuo(qtdGenes, qtdBits));
	}
}

Populacao::~Populacao() {
	// TODO Auto-generated destructor stub
}

void Populacao::Print_populacao() {
	for (int i = 0; i < this->populacao.size(); ++i)
		cout << this->populacao[i].getCromossomo() << endl;
}

void Populacao::Print_individuo(int id) {
	cout << this->populacao[id].getCromossomo() << endl;
}

const vector<Individuo>& Populacao::getPopulacao() const {
	return populacao;
}

void Populacao::setPopulacao(const vector<Individuo>& populacao) {
	this->populacao = populacao;
}

} /* namespace std */
