/*
 * IndividuoBinario.h
 *
 *  Created on: 16 de abr de 2016
 *      Author: deko
 */

#ifndef INDIVIDUOBINARIO_H_
#define INDIVIDUOBINARIO_H_

#include "Individuo.hpp"
#include <iostream>
#include <vector>
#include <iostream>
#include <unistd.h>
#include <cstring>
#include <cstdio>
#include <random>
#include <ctime>
#include <sstream>
#include <sys/types.h>
#include "json.hpp"
#include <fstream>

using json = nlohmann::json;
namespace std {

class IndividuoBinario: public Individuo {
public:
	IndividuoBinario();
	virtual ~IndividuoBinario();
	string getCromossomo() const;
	void setCromossomo(string cromossomo);
	double getFitness();
	double calculoFitness();
	double calculoFucaoObjetivo();
	int fullyDeceptiveF3(string);
	int deceptive(string);
	void mutacao();
	const double decodificaCromossomo(int max, int min, string gene);
	double getFuncaoObjetivo();
	int getNumeroBits(double x_max, double x_min, int precisao);
	const int getNumeroBitsTotal();
	const int posGeneNoCromosso(int posGene);
	string decToBin(int number);
	int binToDec(string number);
	void openJson();
private:
	vector<pair<int, int>> genes;
	string cromossomo;
	vector<int> quantidadeBitsCadaGene;
	json entrada;
};

} /* namespace std */

#endif /* INDIVIDUOBINARIO_H_ */
