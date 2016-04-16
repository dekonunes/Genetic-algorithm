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
#include <ctime>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include <random>

namespace std {

class IndividuoBinario: public Individuo {
public:
	IndividuoBinario(vector<pair<int, int>> genes, int probMutacao);
	IndividuoBinario();
	virtual ~IndividuoBinario();
	const string& getCromossomo() const;
	void setCromossomo(const string& cromossomo);
	double getFitness();
	double calculoFitness();
	double calculoFucaoObjetivo();
	void mutacao();
	const double decodificaCromossomo(int max, int min, string gene);
	double getFuncaoObjetivo();
	int getNumeroBits(double x_max, double x_min, int precisao);
	const int posGeneNoCromosso(int posGene);
	string decToBin(int number);
	int binToDec(string number);
private:
	string cromossomo;
	vector<pair<int, int>> genes;
	int qtdBits[100];
};

} /* namespace std */

#endif /* INDIVIDUOBINARIO_H_ */
