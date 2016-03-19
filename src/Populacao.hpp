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
	//const Individuo crossover();

private:
	vector<Individuo> populacao;
	Individuo* bestIndividuo;
	//static Individuo* newIndividuo;
	int qtdBits;
};

} /* namespace std */

#endif /* POPULACAO_HPP_ */
