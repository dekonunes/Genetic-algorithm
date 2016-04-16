/*
 * Funcoes.hpp
 *
 *  Created on: 16 de abr de 2016
 *      Author: deko
 */

#ifndef SRC_FUNCOES_HPP_
#define SRC_FUNCOES_HPP_
#include <iostream>
#include<string>

namespace std {

class Funcoes {
public:
	Funcoes();
	virtual ~Funcoes();
	string decToBin(int number);
	int binToDec(string number);
};

} /* namespace std */

#endif /* SRC_FUNCOES_HPP_ */
