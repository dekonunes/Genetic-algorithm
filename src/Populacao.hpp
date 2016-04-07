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
	Populacao(int qtdIndividuos,vector<float> genes);
	Populacao();
	virtual ~Populacao();
	void resetPopulacao();
	const vector<Individuo>& getPopulacao() const;
	void setPopulacao(const vector<Individuo>& populacao);
	void print_populacao();
	void print_individuo(int id);
	void insertIndividuo(Individuo newIndividuo);
	const Individuo getIndividuo(int index);
	Individuo getBestIndividuo();
	const Individuo getWorseIndividuo();
	const pair<Individuo,Individuo> crossover(int,int);
	const pair<Individuo,Individuo> crossoverUniforme(int,int);
	const Populacao rollet();
	const Populacao tournament(int k);
	int getQtdIndividuos() const;
	void mutacaoPopulacao();
	void atualizaPiorIndvNaPopulacao(const Individuo& newIndividuo);


private:
	vector<Individuo> populacao;
	Individuo bestIndividuo;
	Individuo worseIndividuo;
	int qtdIndividuos;
};

} /* namespace std */

#endif /* POPULACAO_HPP_ */
