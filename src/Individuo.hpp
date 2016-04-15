/*
 * Individuo.h
 *
 *  Created on: 14 de mar de 2016
 *      Author: deko
 */

#ifndef INDIVIDUO_HPP_
#define INDIVIDUO_HPP_
#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include <random>

using namespace std;

class Individuo {

public:
	Individuo(vector<pair<int, int>> genes, int probMutacao);
	Individuo(vector<pair<float, float>> genes, int probMutacao);
	Individuo();
	virtual ~Individuo();
	const string& getCromossomo() const;
	void setCromossomo(const string& cromossomo);
	float getFitness();
	float calculoFitness();
	float calculoFucaoObjetivo();
	void mutacao();
	string decToBin(int number);
	int binToDec(string number);
	const float decodificaCromossomo(int max, int min, string gene);
	float getFuncaoObjetivo();
	int getNumeroBits(float x_max, float x_min, int precisao);
	const int posGeneNoCromosso(int posGene);

private:
	string cromossomo;
	vector<pair<int, int>> genesB;
	vector<pair<float, float>> genesF;
	int qtdBits[100];
	float fitness;
	int probMutacao;
	float funcaoObjetivo;
};

#endif /* INDIVIDUO_HPP_ */
