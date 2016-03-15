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

namespace std {

class Populacao {
public:
	Populacao(int qtdIndividuos, int qtdGenes, int qtdBits);
	virtual ~Populacao();
	const vector<Individuo>& getPopulacao() const;
	void setPopulacao(const vector<Individuo>& populacao);
	void Print_populacao();
	void Print_individuo(int id);

private:
	vector<Individuo> populacao;
};

;
} /* namespace std */

#endif /* POPULACAO_HPP_ */
