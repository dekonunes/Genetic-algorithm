/*
 * Populacao.hpp
 *
 *  Created on: 15 de mar de 2016
 *      Author: deko
 */

#ifndef POPULACAO_HPP_
#define POPULACAO_HPP_

class Populacao {
protected:
	int chanceCrossover;
	int tipoCrossover;
	int qtdIndividuos;
	int k; //valor do tournament
	int gap;
	bool eletismo;
	bool fitnessEscalonado;
	float C; //Para o calculo do fitness escalonado;
};

#endif /* POPULACAO_HPP_ */
