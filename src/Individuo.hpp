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
	Individuo(vector<pair<double, double>> genes, int probMutacao);
	Individuo();
	virtual ~Individuo();
	const string& getCromossomo() const;
	void setCromossomo(const string& cromossomo);
	double getFitness();
	double calculoFitness();
	double calculoFucaoObjetivo();
	void mutacao();
	string decToBin(int number);
	int binToDec(string number);
	const double decodificaCromossomo(int max, int min, string gene);
	double getFuncaoObjetivo();
	int getNumeroBits(double x_max, double x_min, int precisao);
	const int posGeneNoCromosso(int posGene);
	const vector<double>& getGenesF() const;
	void setGenesF(const vector<double>& genesF);

private:
	string cromossomo;
	vector<pair<int, int>> genesB;
	vector<pair<double, double>> genesFInicial;
	vector<double> genesF;
	int qtdBits[100];
	double fitness;
	int probMutacao;
	double funcaoObjetivo;
};

#endif /* INDIVIDUO_HPP_ */
