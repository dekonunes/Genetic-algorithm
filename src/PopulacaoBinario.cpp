/*
 * PopulacaoBinario.cpp
 *
 *  Created on: 16 de abr de 2016
 *      Author: deko
 */

#include "PopulacaoBinario.hpp"

namespace std {

PopulacaoBinario::PopulacaoBinario() {
	openJson();

	this->qtdIndividuos = this->entrada["tamPop"];
	this->chanceCrossover = this->entrada["chanceMutacao"];
	this->eletismo = this->entrada["elitismo"];

	for (int var = 0; var < this->qtdIndividuos; ++var)
		this->populacao.push_back(IndividuoBinario());

}

PopulacaoBinario::~PopulacaoBinario() {
	// TODO Auto-generated destructor stub
}

void PopulacaoBinario::print_populacao() {
	for (int i = 0; i < this->populacao.size(); ++i)
		cout << this->populacao[i].getCromossomo() << endl;
}

void PopulacaoBinario::print_individuo(int id) {
	cout << this->populacao[id].getCromossomo() << endl;
}

void PopulacaoBinario::insertIndividuo(IndividuoBinario newIndividuo) {
	this->populacao.push_back(newIndividuo);
}

const vector<IndividuoBinario>& PopulacaoBinario::getPopulacao() const {
	return populacao;
}

void PopulacaoBinario::setPopulacao(const vector<IndividuoBinario>& populacao) {
	this->populacao = populacao;
}

const IndividuoBinario PopulacaoBinario::getIndividuo(int index) {
	return this->populacao[index];
}

IndividuoBinario PopulacaoBinario::getBestIndividuo() {
	this->bestIndividuo = this->populacao[0];
	for (int var = 0; var < this->populacao.size(); ++var) {
		if (this->bestIndividuo.getFitness() < this->populacao[var].getFitness()) {
			this->bestIndividuo = this->populacao[var];
		}
	}
	return this->bestIndividuo;
}

const IndividuoBinario PopulacaoBinario::getWorseIndividuo() {
	this->worseIndividuo = this->populacao[0];
	for (int var = 0; var < this->populacao.size(); ++var) {
		if (this->worseIndividuo.getFitness() > this->populacao[var].getFitness()) {
			this->worseIndividuo = this->populacao[var];
		}
	}
	return this->worseIndividuo;
}

const pair<IndividuoBinario, IndividuoBinario> PopulacaoBinario::crossover(int individuo1,
		int individuo2) {
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 100);
	int var, a = bit(mt);
	int qtdBits = this->populacao[individuo1].getCromossomo().size();
	pair<IndividuoBinario, IndividuoBinario> newIndividuosCrossover;
	IndividuoBinario newIndividuo1 = this->populacao[individuo1];
	IndividuoBinario newIndividuo2 = this->populacao[individuo2];

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

const pair<IndividuoBinario, IndividuoBinario> PopulacaoBinario::crossoverUniforme(int individuo1,
		int individuo2) {
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 100);
	int var, a = bit(mt);
	int qtdBits = this->populacao[individuo1].getCromossomo().size();
	pair<IndividuoBinario, IndividuoBinario> newIndividuosCrossover;
	IndividuoBinario newIndividuo1 = this->populacao[individuo1];
	IndividuoBinario newIndividuo2 = this->populacao[individuo2];

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

const PopulacaoBinario PopulacaoBinario::tournament(int k) {
	static mt19937 mt(time(NULL));
	pair<IndividuoBinario, IndividuoBinario> newIndivuos;
	IndividuoBinario indRand, indAux;
	PopulacaoBinario newPop;
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
				if (indRand.getFitness() > indAux.getFitness()) {
					individuoParaCross[qtdIndvParaCross] = indvDoTournament;
				}
			}
		}
		newIndivuos = crossoverUniforme(individuoParaCross[0], individuoParaCross[1]);
		newPop.insertIndividuo(newIndivuos.first);
		newPop.insertIndividuo(newIndivuos.second);
	}
	if (this->eletismo == true)
		newPop.atualizaPiorIndvNaPopulacao(this->getBestIndividuo());
	return newPop;
}

const PopulacaoBinario PopulacaoBinario::rollet() {
	static mt19937 mt(time(NULL));
	pair<IndividuoBinario, IndividuoBinario> newIndivuos;
	PopulacaoBinario newPop;
	int var, valorDaRollet = 0, individuoParaCross[1] { 0 }, auxInsertIndv = 0;
	double valorTotalFitness = 0.0;
	double valorAcumuladoFitness = 0.0;
	for (var = 0; var < this->qtdIndividuos; ++var) {
		valorTotalFitness += this->populacao[var].getFitness();
	}
	for (int loopNovosIndiv = 0; loopNovosIndiv < this->qtdIndividuos / 2; ++loopNovosIndiv) {
		for (int loop = 0; loop < 2; ++loop) {
			static uniform_int_distribution<int> numeroRandom(0, 100);
			valorDaRollet = numeroRandom(mt);
			for (var = 0; var < this->qtdIndividuos - 1; ++var) {

				valorAcumuladoFitness += ((double) this->populacao[var].getFitness()
						/ valorTotalFitness) * 100;
				if (valorDaRollet < valorAcumuladoFitness)
					break;
			}
			valorAcumuladoFitness = 0;
			individuoParaCross[loop] = var;
		}
		newIndivuos = crossover(individuoParaCross[0], individuoParaCross[1]);
		newPop.insertIndividuo(newIndivuos.first);
		newPop.insertIndividuo(newIndivuos.second);
	}
	newPop.atualizaPiorIndvNaPopulacao(this->getBestIndividuo());
	return newPop;
}

int PopulacaoBinario::getQtdIndividuos() const {
	return this->populacao.size();
}

void PopulacaoBinario::mutacaoPopulacao() {
	for (int var = 0; var < this->qtdIndividuos; ++var) {
		this->populacao[var].mutacao();
	}
}

void PopulacaoBinario::openJson() {
	using json = nlohmann::json;
	ifstream texto("entrada.json");

	stringstream buffer;
	buffer << texto.rdbuf();

	this->entrada = json::parse(buffer.str());
}

void PopulacaoBinario::atualizaPiorIndvNaPopulacao(const IndividuoBinario& newIndividuo) {
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