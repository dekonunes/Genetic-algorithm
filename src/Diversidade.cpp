/*
 * Diversidade.cpp
 *
 *  Created on: 6 de mai de 2016
 *      Author: deko
 */

#include "Diversidade.hpp"

namespace std {

double hamming(string ind1, string ind2) {
	double hamm = 0;
	for (int var = 0; var < ind1.size(); ++var) {
		if (ind1[var] != ind2[var])
			hamm++;
	}
	return hamm;
}

double euclidiana(double x, double y) {
	return sqrt(pow(x - y, 2));
}

double euclidianaNormalizada(double x, double y) {
	return sqrt(pow(x - y, 2));
}

} /* namespace std */
