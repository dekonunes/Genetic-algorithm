/*
 * Populacao.hpp
 *
 *  Created on: 15 de mar de 2016
 *      Author: deko
 */

#ifndef POPULACAOREAL_HPP_
#define POPULACAOREAL_HPP_
#include "IndividuoReal.hpp"
#include "Populacao.hpp"
#include <vector>
#include <iostream>
#include <random>
#include <utility>

namespace std {

class PopulacaoReal: public Populacao {
public:
	PopulacaoReal(int, vector<pair<double, double>>, int, int, int);
	PopulacaoReal();
	virtual ~PopulacaoReal();
	const PopulacaoReal rollet();
	const PopulacaoReal tournament(int k);
	virtual const vector<IndividuoReal>& getPopulacao() const;
	void setPopulacao(const vector<IndividuoReal>& populacao);
	void insertIndividuo(IndividuoReal newIndividuo);
	int getQtdIndividuos() const;
	void mutacaoPopulacao();
	const IndividuoReal getIndividuo(int index);
	IndividuoReal getBestIndividuo();
	const IndividuoReal getWorseIndividuo();
	const pair<IndividuoReal, IndividuoReal> crossover(int, int);
	void atualizaPiorIndvNaPopulacao(const IndividuoReal& newIndividuo);
private:
	vector<IndividuoReal> populacao;
	IndividuoReal bestIndividuo;
	IndividuoReal worseIndividuo;
};

} /* namespace std */

#endif /* POPULACAOREAL_HPP_ */
