/*
 * IndividuoReal.hpp
 *
 *  Created on: 16 de abr de 2016
 *      Author: deko
 */

#ifndef SRC_INDIVIDUOREAL_HPP_
#define SRC_INDIVIDUOREAL_HPP_

#include "Individuo.hpp"
#include "json.hpp"
#include <iostream>
#include <fstream>
#include <ctime>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include <random>

using json = nlohmann::json;
namespace std {

class IndividuoReal: public Individuo {
public:
	IndividuoReal();
	virtual ~IndividuoReal();
	double calculoFitness();
	double calculoFucaoObjetivo();
	double getFitness();
	double getFuncaoObjetivo();
	void mutacao(int);
	const vector<double>& getGenes() const;
	void setGenes(const vector<double>& genes);
	void openJson();

private:
	vector<pair<double, double>> genesFInicial;
	vector<double> genes;
	json entrada;
};

} /* namespace std */

#endif /* SRC_INDIVIDUOREAL_HPP_ */
