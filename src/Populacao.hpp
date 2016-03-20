/*
 * Populacao.hpp
 *
 *  Created on: 15 de mar de 2016
 *      Author: deko
 */

#ifndef POPULACAO_HPP_
#define POPULACAO_HPP_
#include "Individuo.hpp"
#include <vector>
#include <iostream>
#include <random>

namespace std {

class Populacao {
public:
	Populacao(int qtdIndividuos, int qtdGenes, int qtdBits);
	Populacao();
	virtual ~Populacao();
	void resetPopulacao();
	const vector<Individuo>& getPopulacao() const;
	void setPopulacao(const vector<Individuo>& populacao);
	void print_populacao();
	void print_individuo(int id);
	void insertIndividuo(Individuo newIndividuo);
	const Individuo getIndividuo(int index);
	const Individuo getBestIndividuo();
	const vector<Individuo>& crossover(int,int) const;
	const Populacao crossoverRollet();
	int getQtdIndividuos() const;

private:
	vector<Individuo> populacao;
	Individuo bestIndividuo;
	int qtdIndividuos;
	int qtdBits;
	int qtdGenes;
};

} /* namespace std */

#endif /* POPULACAO_HPP_ */
