/*
 * Populacao.hpp
 *
 *  Created on: 15 de mar de 2016
 *      Author: deko
 */

#ifndef POPULACAOREAL_HPP_
#define POPULACAOREAL_HPP_

#include <utility>
#include <vector>

#include "IndividuoReal.hpp"
#include "Populacao.hpp"
#include "Diversidade.hpp"

#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

namespace std {

class PopulacaoReal: public Populacao {
public:
	PopulacaoReal();
	virtual ~PopulacaoReal();
	pair<double, double> calculoEscalonadoMenor();
	pair<double, double> calculoEscalonadoMaior();
	double calculoFitnessEscalonado(double);
	double calculoFitnessSharring(int, int);
	const pair<IndividuoReal, IndividuoReal> crossover(int, int);
	const pair<IndividuoReal, IndividuoReal> crossoverArithmetic(int, int);
	const pair<IndividuoReal, IndividuoReal> crossoverBLX(int, int);
	const pair<IndividuoReal, IndividuoReal> crossoverUniformAverage(int, int);
	const IndividuoReal crowding(int);
	double distanciaRealFenotipica();
	IndividuoReal getBestIndividuo();
	const IndividuoReal getIndividuo(int);
	virtual const vector<IndividuoReal>& getPopulacao() const;
	const int getQuantidadeGenes();
	int getQuantidadeIndividuos() const;
	const IndividuoReal getWorseIndividuo();
	void incrementaC();
	void insertIndividuo(IndividuoReal);
	void insertIndividuo(IndividuoReal, int);
	double mediaFitness();
	void mutacaoGaussianaPopulacao();
	void mutacaoPopulacao();
	void openJson();
	const PopulacaoReal rollet();
	pair<IndividuoReal, IndividuoReal> sendCrossover(int, int);
	void setPopulacao(const vector<IndividuoReal>& populacao);
	double summationDistanceFenotipica();
	double summationDistanceGenotipica();
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
