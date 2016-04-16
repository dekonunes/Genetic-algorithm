/*
 * Populacao.cpp
 *
 *  Created on: 15 de mar de 2016
 *      Author: deko
 */

#include "Populacao.hpp"

namespace std {

void Populacao::insertIndividuo(Individuo newIndividuo) {
	this->populacao.push_back(newIndividuo);
}

const vector<Individuo>& Populacao::getPopulacao() const {
	return populacao;
}

void Populacao::setPopulacao(const vector<Individuo>& populacao) {
	this->populacao = populacao;
}

const Individuo Populacao::getIndividuo(int index) {
	return this->populacao[index];
}

const Individuo Populacao::getBestIndividuo() {
	this->bestIndividuo = this->populacao[0];
	for (int var = 0; var < this->populacao.size(); ++var) {
		if (this->bestIndividuo.getFitness() < this->populacao[var].getFitness()) {
			this->bestIndividuo = this->populacao[var];
		}
	}
	return this->bestIndividuo;
}

const Individuo Populacao::getWorseIndividuo() {
	this->worseIndividuo = this->populacao[0];
	for (int var = 0; var < this->populacao.size(); ++var) {
		if (this->worseIndividuo.getFitness() > this->populacao[var].getFitness()) {
			this->worseIndividuo = this->populacao[var];
		}
	}
	return this->worseIndividuo;
}

int Populacao::getQtdIndividuos() const {
	return this->populacao.size();
}

void Populacao::mutacaoPopulacao() {
	for (int var = 0; var < this->qtdIndividuos; ++var) {
		this->populacao[var].mutacao();
	}
}

void Populacao::atualizaPiorIndvNaPopulacao(const Individuo& newIndividuo) {
	int posicaoDoPiorIndiv = 0;
	this->worseIndividuo = this->populacao[0];
	for (int var = 0; var < this->populacao.size(); ++var) {
		if (this->worseIndividuo.getFitness() > this->populacao[var].getFitness()) {
			posicaoDoPiorIndiv = var;
		}
	}
	this->populacao[posicaoDoPiorIndiv] = newIndividuo;
}

} /* namespace std */
