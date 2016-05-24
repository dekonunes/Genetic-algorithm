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
	float C; //Para o calculo do fitness escalonado;
	int chanceCrossover;
	int cCrowding;
	bool elitismo;
	bool fitnessEscalonado;
	bool fitnessSharing;
	float gap;
	int k; //valor do tournament
	int qtdIndividuos;
	float sharingAlpha;
	float sharingSigma;
	int tipoCrossover;
};

#endif /* POPULACAO_HPP_ */
