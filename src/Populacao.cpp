/*
 * Populacao.cpp
 *
 *  Created on: 15 de mar de 2016
 *      Author: deko
 */

#include "Populacao.hpp"

namespace std {

Populacao::Populacao(int qtdIndividuos, vector<pair<int, int>> genes, int chanceCrossover, int probMutacao, int eletismo) :
		bestIndividuo(genes, probMutacao), worseIndividuo(genes, probMutacao) {
	// TODO Auto-generated constructor stub
	for (int var = 0; var < qtdIndividuos; ++var) {
		this->populacao.push_back(Individuo(genes,probMutacao));
	}
	this->qtdIndividuos = qtdIndividuos;
	this->chanceCrossover = chanceCrossover;
	this->eletismo = eletismo;
}

Populacao::Populacao(int qtdIndividuos, vector<pair<float, float>> genes, int chanceCrossover, int probMutacao, int eletismo) :
		bestIndividuo(genes, probMutacao), worseIndividuo(genes, probMutacao) {
	// TODO Auto-generated constructor stub
	for (int var = 0; var < qtdIndividuos; ++var) {
		this->populacao.push_back(Individuo(genes,probMutacao));
	}
	this->qtdIndividuos = qtdIndividuos;
	this->chanceCrossover = chanceCrossover;
	this->eletismo = eletismo;
}

Populacao::Populacao() :
		bestIndividuo() {
}

Populacao::~Populacao() {
	// TODO Auto-generated destructor stub
}

void Populacao::resetPopulacao() {
	//this->~Populacao();
	this->populacao.clear();
}

void Populacao::print_populacao() {
	for (int i = 0; i < this->populacao.size(); ++i)
		cout << this->populacao[i].getCromossomo() << endl;
}

void Populacao::print_individuo(int id) {
	cout << this->populacao[id].getCromossomo() << endl;
}

void Populacao::insertIndividuo(Individuo newIndividuo) {
	this->populacao.push_back(newIndividuo);
}

const vector<Individuo>& Populacao::getPopulacao() const {
	return populacao;
}

void Populacao::setPopulacao(const vector<Individuo>& populacao) {
	this->populacao = populacao;
}

const Individuo Populacao::getIndividuo(int index) {
	return this->populacao[index];
}

Individuo Populacao::getBestIndividuo() {
	this->bestIndividuo = this->populacao[0];
	for (int var = 0; var < this->populacao.size(); ++var) {
		if (this->bestIndividuo.getFitness() < this->populacao[var].getFitness()) {
			this->bestIndividuo = this->populacao[var];
		}
	}
	return this->bestIndividuo;
}

const Individuo Populacao::getWorseIndividuo() {
	this->worseIndividuo = this->populacao[0];
	for (int var = 0; var < this->populacao.size(); ++var) {
		if (this->worseIndividuo.getFitness() > this->populacao[var].getFitness()) {
			this->worseIndividuo = this->populacao[var];
		}
	}
	return this->worseIndividuo;
}

const pair<Individuo, Individuo> Populacao::crossover(int individuo1, int individuo2) {
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 100);
	int var, a = bit(mt);
	int qtdBits = this->populacao[individuo1].getCromossomo().size();
	pair<Individuo, Individuo> newIndividuosCrossover;
	Individuo newIndividuo1 = this->populacao[individuo1];
	Individuo newIndividuo2 = this->populacao[individuo2];

	if (this->chanceCrossover > a) {

		string cromossomoNewInviduio1;
		string cromossomoNewInviduio2;

		static uniform_int_distribution<int> numRandon(0, qtdBits - 1);
		a = numRandon(mt);

		for (var = 0; var < a; ++var) {
			cromossomoNewInviduio1 = cromossomoNewInviduio1
					+ this->populacao[individuo1].getCromossomo()[var];
			cromossomoNewInviduio2 = cromossomoNewInviduio2
					+ this->populacao[individuo2].getCromossomo()[var];

		}
		for (; var < qtdBits; ++var) {
			cromossomoNewInviduio1 = cromossomoNewInviduio1
					+ this->populacao[individuo2].getCromossomo()[var];
			cromossomoNewInviduio2 = cromossomoNewInviduio2
					+ this->populacao[individuo1].getCromossomo()[var];
		}
		newIndividuo1.setCromossomo(cromossomoNewInviduio1);
		newIndividuo2.setCromossomo(cromossomoNewInviduio2);
	}
	newIndividuosCrossover = make_pair(newIndividuo1, newIndividuo2);

	return newIndividuosCrossover;
}

const pair<Individuo, Individuo> Populacao::crossoverUniforme(int individuo1, int individuo2) {
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 100);
	int var, a = bit(mt);
	int qtdBits = this->populacao[individuo1].getCromossomo().size();
	pair<Individuo, Individuo> newIndividuosCrossover;
	Individuo newIndividuo1 = this->populacao[individuo1];
	Individuo newIndividuo2 = this->populacao[individuo2];

	if (this->chanceCrossover > a) {

		string cromossomoNewInviduio1 = this->populacao[individuo1].getCromossomo();
		string cromossomoNewInviduio2 = this->populacao[individuo2].getCromossomo();
		for (int var = 0; var < this->populacao[individuo1].getCromossomo().size(); ++var) {
			static uniform_int_distribution<int> numRandon(0, 1);
			a = numRandon(mt);

			if (a == 1) {
				cromossomoNewInviduio1[var] = this->populacao[individuo2].getCromossomo()[var];
				cromossomoNewInviduio2[var] = this->populacao[individuo1].getCromossomo()[var];
			}

		}
		newIndividuo1.setCromossomo(cromossomoNewInviduio1);
		newIndividuo2.setCromossomo(cromossomoNewInviduio2);
	}
	if (this->eletismo == true)
		newIndividuosCrossover = make_pair(newIndividuo1, newIndividuo2);

	return newIndividuosCrossover;
}

const Populacao Populacao::tournament(int k) {
	static mt19937 mt(time(NULL));
	pair<Individuo, Individuo> newIndivuos;
	Individuo indRand, indAux;
	Populacao newPop;
	int individuoParaCross[1] { 0 }, auxInsertIndv = 0, indvDoTournament;

	for (int loopNovosIndiv = 0; loopNovosIndiv < this->qtdIndividuos / 2; ++loopNovosIndiv) {
		for (int qtdIndvParaCross = 0; qtdIndvParaCross < 2; ++qtdIndvParaCross) {
			static uniform_int_distribution<int> numeroRandom(0, this->qtdIndividuos - 1);
			indvDoTournament = numeroRandom(mt);
			indAux = this->populacao[indvDoTournament]; //Já encontra o primeiro indv aleatório, já o primeiro k
			for (int var = 0; var < k - 1; ++var) { //k-1 pois o primeiro individuo veio da linha acima
				static uniform_int_distribution<int> numeroRandom(0, this->qtdIndividuos - 1);
				indvDoTournament = numeroRandom(mt);
				indRand = this->populacao[indvDoTournament];
				//cout << indvDoTournament << endl;
				if (indRand.getFitness() > indAux.getFitness()) {
					individuoParaCross[qtdIndvParaCross] = indvDoTournament;
				}
				//cout << individuoParaCross[qtdIndvParaCross] << endl;
			}
		}
		//cout << individuoParaCross[0] << "  " << individuoParaCross[1] << endl;
		newIndivuos = crossoverUniforme(individuoParaCross[0], individuoParaCross[1]);
		newPop.insertIndividuo(newIndivuos.first);
		newPop.insertIndividuo(newIndivuos.second);
	}
	newPop.atualizaPiorIndvNaPopulacao(this->getBestIndividuo());
	return newPop;
}

const Populacao Populacao::rollet() {
	static mt19937 mt(time(NULL));
	pair<Individuo, Individuo> newIndivuos;
	Populacao newPop;
	int var, valorDaRollet = 0, individuoParaCross[1] { 0 }, auxInsertIndv = 0;
	float valorTotalFitness = 0.0;
	float valorAcumuladoFitness = 0.0;
	for (var = 0; var < this->qtdIndividuos; ++var) {
		valorTotalFitness += this->populacao[var].getFitness();
	}

	for (int loopNovosIndiv = 0; loopNovosIndiv < this->qtdIndividuos / 2; ++loopNovosIndiv) {

		for (int loop = 0; loop < 2; ++loop) {
			static uniform_int_distribution<int> numeroRandom(0, 100);
			valorDaRollet = numeroRandom(mt);
			for (var = 0; var < this->qtdIndividuos - 1; ++var) {
				valorAcumuladoFitness += ((float) this->populacao[var].getFitness()
						/ valorTotalFitness) * 100;
				if (valorDaRollet < valorAcumuladoFitness)
					break;
			}

			valorAcumuladoFitness = 0;
			individuoParaCross[loop] = var;
		}
		newIndivuos = crossoverUniforme(individuoParaCross[0], individuoParaCross[1]);
		newPop.insertIndividuo(newIndivuos.first);
		newPop.insertIndividuo(newIndivuos.second);
	}
	newPop.atualizaPiorIndvNaPopulacao(this->getBestIndividuo());
	return newPop;
}

int Populacao::getQtdIndividuos() const {
	return this->populacao.size();
}

void Populacao::mutacaoPopulacao() {
	for (int var = 0; var < this->qtdIndividuos; ++var) {
		this->populacao[var].mutacao();
	}
}

void Populacao::atualizaPiorIndvNaPopulacao(const Individuo& newIndividuo) {
	int posicaoDoPiorIndiv = 0;
	this->worseIndividuo = this->populacao[0];
	for (int var = 0; var < this->populacao.size(); ++var) {
		if (this->worseIndividuo.getFitness() > this->populacao[var].getFitness()) {
			posicaoDoPiorIndiv = var;
		}
	}
	this->populacao[posicaoDoPiorIndiv] = newIndividuo;
}

} /* namespace std */
