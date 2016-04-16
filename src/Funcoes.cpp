/*
 * Funcoes.cpp
 *
 *  Created on: 16 de abr de 2016
 *      Author: deko
 */

#include "Funcoes.hpp"

namespace std {

Funcoes::Funcoes() {
	// TODO Auto-generated constructor stub

}

Funcoes::~Funcoes() {
	// TODO Auto-generated destructor stub
}

string Funcoes::decToBin(int number) {
	if (number == 0)
		return "0";
	if (number == 1)
		return "1";
	if (number % 2 == 0)
		return decToBin(number / 2) + "0";
	else
		return decToBin(number / 2) + "1";
}

int Funcoes::binToDec(string number) {
	/*int result = 0, pow = 1;
	 for (int i = number.length() - 1; i >= 0; --i, pow <<= 1)
	 result += (number[i] - '0') * pow;
	 return result;//stoi(number,nullptr,2);*/
	return stoi(number, nullptr, 2);
}

} /* namespace std */
