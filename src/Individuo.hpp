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
	Individuo(vector<float> genes);
	Individuo();
	virtual ~Individuo();
	const string& getCromossomo() const;
	void setCromossomo(const string& cromossomo);
	float getFitness();
	void calculoFitness();
	void calculoFucaoObjetivo();
	void mutacao();
	string decToBin(int number);
	int binToDec(string number);
	const float decodificaCromossomo();
	float getFuncaoObjetivo();
	int getNumeroBits(float x_max, float x_min, int precisao);
	const int restricaoMaiorIgual(int posGene, int valorRestricao);
	const int posGeneNoCromosso(int posGene);

private:
	string cromossomo;
	vector<float> genes;
	int qtdBits[100];
	float fitness;
	float funcaoObjetivo;
};

#endif /* INDIVIDUO_HPP_ */
