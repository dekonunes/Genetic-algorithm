/*
 * IndividuoReal.hpp
 *
 *  Created on: 16 de abr de 2016
 *      Author: deko
 */

#ifndef SRC_INDIVIDUOREAL_HPP_
#define SRC_INDIVIDUOREAL_HPP_

#include "Individuo.hpp"
#include <iostream>
#include <ctime>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include <random>

namespace std {

class IndividuoReal: public Individuo {
public:
	IndividuoReal(vector<pair<double, double>> genesInicial, int probMutacao);
	IndividuoReal();
	virtual ~IndividuoReal();
	double calculoFitness();
	double calculoFucaoObjetivo();
	double getFitness();
	double getFuncaoObjetivo();
	void mutacao();
	const vector<double>& getGenes() const;
	void setGenes(const vector<double>& genes);

private:
	vector<pair<double, double>> genesFInicial;
	vector<double> genes;
};

} /* namespace std */

#endif /* SRC_INDIVIDUOREAL_HPP_ */
