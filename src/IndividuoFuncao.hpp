/*
 * IndividuoFuncao.hpp
 *
 *  Created on: 21 de mar de 2016
 *      Author: deko
 */

#ifndef SRC_INDIVIDUOFUNCAO_HPP_
#define SRC_INDIVIDUOFUNCAO_HPP_

#include <math.h>
#include <iostream>
#include <ctime>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <sys/types.h>
#include <unistd.h>
#include <random>

namespace std {

class IndividuoFuncao {
public:
	IndividuoFuncao(int qtdgenes, int qtdBits);
	virtual ~IndividuoFuncao();
	const string& getCromossomo() const;
	void setCromossomo(const string& cromossomo);
	int getFitness() const;
	void setFitness(int fitness);
	int getQtdBits() const;
	int getQtdgenes() const;
	int calculoFitness();
	string decToBin(int number);
	int binToDec(string number);

private:
	string cromossomo;
	int qtdgenes;
	int qtdBits;
	int fitness;
};

} /* namespace std */

#endif /* SRC_INDIVIDUOFUNCAO_HPP_ */
