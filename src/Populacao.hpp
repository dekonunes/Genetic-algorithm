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
	virtual ~Populacao();
	const vector<Individuo>& getPopulacao() const;
	void setPopulacao(const vector<Individuo>& populacao);
	void print_populacao();
	void print_individuo(int id);
	const Individuo getIndividuo(int index);
	const Individuo getBestIndividuo();
	const Individuo crossover(Individuo individuo1,Individuo individuo2);

private:
	vector<Individuo> populacao;
	Individuo bestIndividuo;
	int qtdBits;
	int qtdGenes;
};

} /* namespace std */

#endif /* POPULACAO_HPP_ */
