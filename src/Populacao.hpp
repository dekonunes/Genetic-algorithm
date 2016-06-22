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
	bool elitismo;
	bool fitnessEscalonado;
	bool fitnessSharing;
	bool isCrowding;
	int cCrowding;
	float gap;
	int k; //valor do tournament
	int qtdIndividuos;
	float sharingAlpha;
	float sharingSigma;
	int tipoCrossover;
	double alpha;
	double beta;
};

#endif /* POPULACAO_HPP_ */
