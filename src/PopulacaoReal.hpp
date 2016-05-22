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
#include "json.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <random>
#include <utility>

namespace std {

class PopulacaoReal: public Populacao {
public:
	PopulacaoReal();
	virtual ~PopulacaoReal();
	pair<double, double> calculoEscalonadoMenor();
	pair<double, double> calculoEscalonadoMaior();
	double calculoFitnessEscalonado(double);
	const pair<IndividuoReal, IndividuoReal> crossover(int, int);
	const pair<IndividuoReal, IndividuoReal> crossoverArithmetic(int, int);
	const pair<IndividuoReal, IndividuoReal> crossoverBLX(int, int);
	const pair<IndividuoReal, IndividuoReal> crossoverUniformAverage(int, int);
	IndividuoReal getBestIndividuo();
	const IndividuoReal getIndividuo(int index);
	virtual const vector<IndividuoReal>& getPopulacao() const;
	const int getQuantidadeGenes();
	int getQuantidadeIndividuos() const;
	const IndividuoReal getWorseIndividuo();
	void incrementaC();
	void insertIndividuo(IndividuoReal newIndividuo);
	void insertIndividuo(IndividuoReal newIndividuo, int posicao);
	double mediaFitness();
	void mutacaoPopulacao();
	void openJson();
	const PopulacaoReal rollet();
	pair<IndividuoReal, IndividuoReal> sendCrossover(int, int);
	void setPopulacao(const vector<IndividuoReal>& populacao);
	const PopulacaoReal tournament();
private:
	vector<IndividuoReal> populacao;
	vector<pair<double, double>> genesInicial;
	IndividuoReal bestIndividuo;
	IndividuoReal worseIndividuo;
	json entrada;
};

} /* namespace std */

#endif /* POPULACAOREAL_HPP_ */
