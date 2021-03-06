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
	this->isCrowding = this->entrada["crowding"];
	this->cCrowding = this->entrada["crowdingQuantidade"];
	this->chanceCrossover = this->entrada["chanceCrossover"];
	this->elitismo = this->entrada["elitismo"];
	this->k = this->entrada["tournament"];
	this->fitnessEscalonado = this->entrada["escalonado"];
	this->fitnessSharing = this->entrada["sharring"];
	this->sharingSigma = this->entrada["sigma"];
	this->sharingAlpha = this->entrada["alpha"];
	this->C = 1.2;
	this->gap = this->entrada["gap"];

	for (int var = 0; var < this->qtdIndividuos; ++var)
		this->populacao.push_back(IndividuoBinario());

}

PopulacaoBinario::~PopulacaoBinario() {
	// TODO Auto-generated destructor stub
}

double PopulacaoBinario::calculoFitnessSharring(int individuo) {
	double distanceIndividuo = 0;
	double maxFitnessPopulacao = this->getBestIndividuo().getFitness();

	for (int count = 0; count < getQtdIndividuos(); ++count)
		distanceIndividuo += euclidiana(
				this->populacao[individuo].getFitness() / maxFitnessPopulacao,
				this->populacao[count].getFitness() / maxFitnessPopulacao);

	double somatorioS = 1 - pow(distanceIndividuo / this->sharingSigma, this->sharingAlpha);
	return this->populacao[individuo].getFitness() / somatorioS;
}

double PopulacaoBinario::calculoTotalFitnessSharring() {
	double valorTotalFitnessSharring = 0.0;
	double maxFitnessPopulacao = this->getBestIndividuo().getFitness();
	for (int count = 0; count < getQtdIndividuos() - 1; ++count) {
		double distanceIndividuos = euclidiana(
				this->populacao[count].getFitness() / maxFitnessPopulacao,
				this->populacao[count + 1].getFitness() / maxFitnessPopulacao);
		double somatorioS = 1 - pow(distanceIndividuos / this->sharingSigma, this->sharingAlpha);
		valorTotalFitnessSharring = this->populacao[count].getFitness() / somatorioS;
	}
	//cout << valorTotalFitnessSharring << endl;
	return valorTotalFitnessSharring;
}

void PopulacaoBinario::disableGap() {
	this->gap = 1.0;
}

void PopulacaoBinario::incrementaC() {
	int geracoes = this->entrada["geracoes"];
	geracoes = geracoes * 0.9;
	this->C += 0.8 / geracoes;
}

void PopulacaoBinario::calculoAlhpaBeta() {
	IndividuoBinario indMin = getWorseIndividuo();
	IndividuoBinario indMax = getBestIndividuo();
	double media = mediaFitness(), max = indMax.getFitness(), min = indMin.getFitness();
	if ((this->C * media - max) / (this->C - 1) > min)
		calculoEscalonadoMaior();
	else
		calculoEscalonadoMenor();
}

double PopulacaoBinario::calculoFitnessEscalonado(double fitness) {
	double fitnessEscalonado = this->alpha * fitness + this->beta;
	if (fitnessEscalonado < 0)
		fitnessEscalonado = 0;

	return fitnessEscalonado;
}

void PopulacaoBinario::calculoEscalonadoMenor() {
	IndividuoBinario indMin = getWorseIndividuo();
	IndividuoBinario indMax = getBestIndividuo();
	double media = mediaFitness(), max = indMax.getFitness(), min =
			indMin.getFitness();

	this->alpha = (media * (this->C - 1)) / (max - media);
	this->beta = (media * (max - this->C * media)) / (max - media);
}

void PopulacaoBinario::calculoEscalonadoMaior() {
	IndividuoBinario indMin = getWorseIndividuo();
	IndividuoBinario indMax = getBestIndividuo();
	double media = mediaFitness(), max = indMax.getFitness(), min = indMin.getFitness();

	this->alpha = media / (media - min);
	this->beta = (-min * media) / (media - min);
}

double PopulacaoBinario::mediaFitness() {
	double media = 0;
	IndividuoBinario ind;
	for (int var = 0; var < this->populacao.size(); ++var) {
		ind = this->populacao[var];
		media += ind.getFitness();
	}
	return media / this->populacao.size();
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

void PopulacaoBinario::insertIndividuo(IndividuoBinario newIndividuo, int posicao) {
	this->populacao[posicao] = newIndividuo;
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
	static uniform_int_distribution<int> bit(1, 99);
	int var, a = bit(mt);

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

	newIndividuosCrossover = make_pair(newIndividuo1, newIndividuo2);
	return newIndividuosCrossover;
}

const PopulacaoBinario PopulacaoBinario::rollet() {
	pair<IndividuoBinario, IndividuoBinario> newIndivuos;
	static mt19937 mt(time(NULL));
	static PopulacaoBinario newPop;
	newPop.populacao.clear();
	int var, valorDaRollet = 0, individuoParaCross[1] { 0 }, auxInsertIndv = 0;
	double valorTotalFitness = 0.0, valorAcumuladoFitness = 0.0;
	calculoAlhpaBeta();
	for (var = 0; var < this->qtdIndividuos; ++var) {
		if (this->fitnessEscalonado)
			valorTotalFitness += calculoFitnessEscalonado(this->populacao[var].getFitness());
		if (this->fitnessSharing)
			valorTotalFitness += calculoTotalFitnessSharring();
		else
			valorTotalFitness += this->populacao[var].getFitness();
	}

	for (int loopNovosIndiv = 0; loopNovosIndiv < (this->qtdIndividuos * this->gap) / 2;
			++loopNovosIndiv) {
		for (int loop = 0; loop < 2; ++loop) {
			static uniform_int_distribution<int> numeroRandom(0, 100);

			valorDaRollet = numeroRandom(mt);

			for (var = 0; var < this->qtdIndividuos - 1; ++var) {
				if (this->fitnessEscalonado)
					valorAcumuladoFitness += ((double) calculoFitnessEscalonado(
							this->populacao[var].getFitness()) / valorTotalFitness) * 100;
				if (this->fitnessSharing)
					valorAcumuladoFitness += (calculoFitnessSharring(var)) * 100;
				else
					valorAcumuladoFitness += ((double) this->populacao[var].getFitness()
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

	for (int count = newPop.getQtdIndividuos(); count < this->qtdIndividuos; ++count)
		newPop.insertIndividuo(this->populacao[count]);

	newPop.mutacaoPopulacao();

	if (this->elitismo == true)
		newPop.insertIndividuo(this->getBestIndividuo(), 1);

	return newPop;
}

const PopulacaoBinario PopulacaoBinario::tournament() {
	static mt19937 mt(time(NULL));
	pair<IndividuoBinario, IndividuoBinario> newIndivuos;
	IndividuoBinario indRand, indAux, ind;
	PopulacaoBinario newPop;
	newPop.populacao.clear();
	int individuoParaCross[1] { 0 }, auxInsertIndv = 0, indvDoTournament;
	calculoAlhpaBeta();
	for (int loopNovosIndiv = 0; loopNovosIndiv < (this->qtdIndividuos * this->gap);
			++loopNovosIndiv) {
		for (int qtdIndvParaCross = 0; qtdIndvParaCross < 2; ++qtdIndvParaCross) {
			static uniform_int_distribution<int> numeroRandom(0, this->qtdIndividuos - 1);
			indvDoTournament = numeroRandom(mt);
			indAux = this->populacao[indvDoTournament]; //Já encontra o primeiro indv aleatório, já o primeiro k
			for (int var = 0; var < this->k - 1; ++var) { //k-1 pois o primeiro individuo veio da linha acima
				static uniform_int_distribution<int> numeroRandom(0, this->qtdIndividuos - 1);
				indvDoTournament = numeroRandom(mt);
				indRand = this->populacao[indvDoTournament];
				if (indRand.getFitness() > indAux.getFitness()) {
					individuoParaCross[qtdIndvParaCross] = indvDoTournament;
				}
			}
		}
		newIndivuos = crossover(individuoParaCross[0], individuoParaCross[1]);
		newPop.insertIndividuo(newIndivuos.first);
		newPop.insertIndividuo(newIndivuos.second);
	}
	for (int count = newPop.getQtdIndividuos(); count < this->qtdIndividuos; ++count)
		newPop.insertIndividuo(this->populacao[count]);
	newPop.mutacaoPopulacao();
	if (this->elitismo == true)
		newPop.insertIndividuo(this->getBestIndividuo(), 1);
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
	texto.close();
}

} /* namespace std */
