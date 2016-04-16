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
	virtual const vector<Individuo>& getPopulacao() const;
	void setPopulacao(const vector<Individuo>& populacao);
	virtual void print_populacao();
	virtual void print_individuo(int id);
	void insertIndividuo(Individuo newIndividuo);
	const Individuo getIndividuo(int index);
	const Individuo getBestIndividuo();
	const Individuo getWorseIndividuo();
	virtual const pair<Individuo,Individuo> crossover(int,int);

	int getQtdIndividuos() const;
	void mutacaoPopulacao();
	void atualizaPiorIndvNaPopulacao(const Individuo& newIndividuo);


protected:
	vector<Individuo> populacao;
	Individuo bestIndividuo;
	Individuo worseIndividuo;
	int chanceCrossover;
	int eletismo;
	int qtdIndividuos;
};

} /* namespace std */

#endif /* POPULACAO_HPP_ */
