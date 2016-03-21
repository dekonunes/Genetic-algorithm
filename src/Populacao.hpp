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
#include <utility>
#include <string>


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
	const pair<Individuo,Individuo> crossover(int,int);
	const Populacao crossoverRollet();
	int getQtdIndividuos() const;
	void mutacaoPopulacao();

private:

	vector<Individuo> populacao;
	Individuo bestIndividuo;
	int qtdIndividuos;
	int qtdBits;
	int qtdGenes;
};

} /* namespace std */

#endif /* POPULACAO_HPP_ */
