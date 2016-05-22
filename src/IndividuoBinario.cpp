/*
 * IndividuoBinario.cpp
 *
 *  Created on: 16 de abr de 2016
 *      Author: deko
 */

#include "IndividuoBinario.hpp"

namespace std {

IndividuoBinario::IndividuoBinario() {
	// TODO Auto-generated constructor stub
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 1);
	string aux;
	openJson();
	pair<int, int> auxGenes;

	for (int i = 0; i < entrada["qtdVariaveis"]; i++) {
		auxGenes.first = this->entrada["variaveis"][i]["min"];
		auxGenes.second = this->entrada["variaveis"][i]["max"];
		this->genes.push_back(auxGenes);
	}

	for (int var = 0; var < genes.size(); ++var) {
		this->qtdBits[var] = getNumeroBits(this->entrada["variaveis"][var]["max"],
				this->entrada["variaveis"][var]["min"],
				this->entrada["variaveis"][var]["precisao"]);
	}

	for (int var = 0; var < genes.size(); ++var) {
		for (int i = 0; i < this->qtdBits[var]; i++) {
			aux = static_cast<ostringstream*>(&(ostringstream() << bit(mt)))->str();
			this->cromossomo = this->cromossomo + aux;
		}
	}
	this->probMutacao = this->entrada["chanceMutacao"];
	this->funcaoObjetivo = 0.0;
	this->fitness = 0.0;
	calculoFitness();
}

IndividuoBinario::~IndividuoBinario() {
	// TODO Auto-generated constructor stub
}

const string& IndividuoBinario::getCromossomo() const {
	return cromossomo;
}

void IndividuoBinario::setCromossomo(const string& cromossomo) {
	this->cromossomo = cromossomo;
}

double IndividuoBinario::getFitness() {
	calculoFitness();
	return this->fitness;
}

double IndividuoBinario::calculoFitness() {
	/*int A, B, qtdDisco, maxExtrapolaFunc;
	 double penalidade, aux, r = -1.0, maxExtrapolaFO;
	 string stringGene[10];
	 for (int var2 = 0; var2 < this->genes.size(); ++var2) {
	 for (int var = 0; var < this->qtdBits[var2]; ++var) {
	 stringGene[var2] = stringGene[var2] + this->cromossomo[posGeneNoCromosso(var2) + var];
	 }

	 }
	 A = (int) decodificaCromossomo(60, 0, stringGene[0]);
	 B = (int) decodificaCromossomo(50, 0, stringGene[1]);
	 qtdDisco = A + (2 * B);
	 maxExtrapolaFunc = 40;
	 maxExtrapolaFO = 60 * 180 + 50 * 300;

	 if (qtdDisco <= 120)
	 penalidade = 0;
	 else {
	 penalidade = (double) (qtdDisco - 120) / (double) maxExtrapolaFunc;
	 //cout << "Valor de A: " << A << " Valor de B:" << B << endl;
	 //cout << "valor penalidade: " << penalidade << endl;
	 }

	 this->fitness = calculoFucaoObjetivo() / (double) maxExtrapolaFO + (r * penalidade);*/
	this->fitness = calculoFucaoObjetivo();
	if (this->fitness < 0)
		this->fitness = 0;
	return this->fitness;
}

double IndividuoBinario::calculoFucaoObjetivo() {
	this->funcaoObjetivo = 0.0;
	/*int A, B;
	string stringGene[10];
	for (int var2 = 0; var2 < this->genes.size(); ++var2) {
		for (int var = 0; var < this->qtdBits[var2]; ++var) {
			stringGene[var2] = stringGene[var2] + this->cromossomo[posGeneNoCromosso(var2) + var];
		}

	}
	A = (int) decodificaCromossomo(60, 0, stringGene[0]);
	B = (int) decodificaCromossomo(50, 0, stringGene[1]);

	this->funcaoObjetivo = A * 180 + B * 300;*/

	for (int var = 1; var < this->qtdBits[0]; ++var) {
		if (this->cromossomo[var] != this->cromossomo[var - 1])
			this->funcaoObjetivo++;
	}
	return this->funcaoObjetivo;
}

void IndividuoBinario::mutacao() {
	int numRand;
	static mt19937 mt(time(NULL));
	string oldCromossomo = getCromossomo(), newCromossomo = getCromossomo();

	for (int loopCromossomos = 0; loopCromossomos < this->cromossomo.size(); ++loopCromossomos) {

		static uniform_int_distribution<int> numRandom(0, 100);

		numRand = numRandom(mt);

		if (numRand < this->probMutacao) {
			if (this->cromossomo[loopCromossomos] == '1') {
				this->cromossomo[loopCromossomos] = '0';
			} else
				this->cromossomo[loopCromossomos] = '1';
		}
	}
}

const double IndividuoBinario::decodificaCromossomo(int max, int min, string gene) {
	int l = getNumeroBits(max, min, 0);
	int decimal, x, x_max = max, x_min = min;
	decimal = binToDec(gene);
	x = x_min + (((x_max - x_min) / (pow(2, l) - 1)) * decimal);
	return x;
}

double IndividuoBinario::getFuncaoObjetivo() {
	calculoFucaoObjetivo();
	return this->funcaoObjetivo;
}

int IndividuoBinario::getNumeroBits(double x_max, double x_min, int precisao) {
	int numBits = (x_max - x_min) / pow(10, -precisao);
	return log2(numBits) + 1;
}

const int IndividuoBinario::posGeneNoCromosso(int posGene) {
	int posicao = 0;
	for (int var = 0; var < posGene; ++var) {
		posicao += this->qtdBits[var];
	}
	return posicao;
}

string IndividuoBinario::decToBin(int number) {
	if (number == 0)
		return "0";
	if (number == 1)
		return "1";
	if (number % 2 == 0)
		return decToBin(number / 2) + "0";
	else
		return decToBin(number / 2) + "1";
}

int IndividuoBinario::binToDec(string number) {
	return stoi(number, nullptr, 2);
}

void IndividuoBinario::openJson() {
	using json = nlohmann::json;
	ifstream texto("entrada.json");

	stringstream buffer;
	buffer << texto.rdbuf();

	this->entrada = json::parse(buffer.str());
}

} /* namespace std */
