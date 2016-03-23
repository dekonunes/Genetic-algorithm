//============================================================================
// Name        : Genetic-algorithm.cpp
// Author      : Deko
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "main.hpp"

using namespace std;

int main() {

	float x = 0;
	float a = cos(20 * x) - (abs(x) / 2) + (x * x * x / 4);
	//cout << a << endl;
	Individuo indiv(1, 16);
	//indiv.decodificaCromossomo();
	cout << "fit:" << indiv.calculoFucaoObjetivo() << endl;
	Populacao pop(10,1,16);
	Populacao newPop;

	return 0;
}

