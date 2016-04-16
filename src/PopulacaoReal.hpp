/*
 * Populacao.hpp
 *
 *  Created on: 15 de mar de 2016
 *      Author: deko
 */

#ifndef POPULACAOREAL_HPP_
#define POPULACAOREAL_HPP_
#include "Individuo.hpp"
#include "Populacao.hpp"
#include <vector>
#include <iostream>
#include <random>
#include <utility>
#include <string>

namespace std {

class PopulacaoReal: public Populacao {
public:
	PopulacaoReal(int, vector<pair<double, double>>, int, int, int);
	PopulacaoReal();
	virtual ~PopulacaoReal();
	const pair<Individuo, Individuo> crossoverUniforme(int, int);
	const PopulacaoReal rollet();
	const PopulacaoReal tournament(int k);
};

} /* namespace std */

#endif /* POPULACAOREAL_HPP_ */
