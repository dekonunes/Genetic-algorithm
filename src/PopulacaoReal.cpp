/*
 * Populacao.cpp
 *
 *  Created on: 15 de mar de 2016
 *      Author: deko
 */

#include "PopulacaoReal.hpp"

namespace std {

PopulacaoReal::PopulacaoReal() {
	// TODO Auto-generated constructor stub
	openJson();
	this->qtdIndividuos = this->entrada["tamPop"];
	this->cCrowding = this->entrada["crowding"];
	this->chanceCrossover = this->entrada["chanceCrossover"];
	this->elitismo = this->entrada["elitismo"];
	this->k = this->entrada["tournament"];
	this->fitnessEscalonado = this->entrada["escalonado"];
	this->fitnessSharing = this->entrada["sharring"];
	this->sharingSigma = this->entrada["sigma"];
	this->sharingAlpha = this->entrada["alpha"];

	this->gap = this->entrada["gap"];
	this->C = 1.2;

	for (int var = 0; var < this->qtdIndividuos; ++var)
		this->populacao.push_back(IndividuoReal());

	pair<double, double> auxGenesIniciais;
	for (int var = 0; var < this->entrada["qtdVariaveis"]; ++var) {
		auxGenesIniciais.first = this->entrada["variaveis"][var]["min"];
		auxGenesIniciais.second = this->entrada["variaveis"][var]["max"];
		this->genesInicial.push_back(auxGenesIniciais);
	}

	if (entrada["crossover"] == "padrao") {
		this->tipoCrossover = 1;
	}

	if (entrada["crossover"] == "arithmetic") {
		this->tipoCrossover = 2;
	}

	if (entrada["crossover"] == "uniform") {
		this->tipoCrossover = 3;
	}

	if (entrada["crossover"] == "BLX") {
		this->tipoCrossover = 4;
	}
}

PopulacaoReal::~PopulacaoReal() {
	// TODO Auto-generated destructor stub
}

pair<double, double> PopulacaoReal::calculoEscalonadoMenor() {
	pair<double, double> pares;
	IndividuoReal indMin = getWorseIndividuo();
	IndividuoReal indMax = getBestIndividuo();
	double media = mediaFitness(), alpha, beta, max = indMax.getFitness(), min =
			indMin.getFitness();

	alpha = (media * (this->C - 1)) / (max - media);
	beta = (media * (max - this->C * media)) / (max - media);

	pares.first = alpha;
	pares.second = beta;
	return pares;
}

pair<double, double> PopulacaoReal::calculoEscalonadoMaior() {
	pair<double, double> pares;
	IndividuoReal indMin = getWorseIndividuo();
	IndividuoReal indMax = getBestIndividuo();
	double media = mediaFitness(), alpha, beta, max = indMax.getFitness(), min =
			indMin.getFitness();
	alpha = media / (media - min);
	beta = (-min * media) / (media - min);
	pares.first = alpha;
	pares.second = beta;
	return pares;
}

double PopulacaoReal::calculoFitnessEscalonado(double fitness) {
	IndividuoReal indMin = getWorseIndividuo();
	IndividuoReal indMax = getBestIndividuo();
	double media = mediaFitness(), alpha, beta, max = indMax.getFitness(), min =
			indMin.getFitness(), fitnessEscalonado, teste;
	pair<double, double> pares;
	teste = (this->C * media - max) / (this->C - 1);
	if (teste > min)
		pares = calculoEscalonadoMaior();
	else
		pares = calculoEscalonadoMenor();

	alpha = pares.first;
	beta = pares.second;

	fitnessEscalonado = alpha * fitness + beta;
	if (fitnessEscalonado < 0)
		fitnessEscalonado = 0;

	return fitnessEscalonado;
}

double PopulacaoReal::calculoFitnessSharring(double fitness) {
	return fitness / summationDistanceGenotipica(); //Onde aplica a segunda formula?
}

const pair<IndividuoReal, IndividuoReal> PopulacaoReal::crossover(int individuo1, int individuo2) {
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 99);
	int var = 0, a = bit(mt);
	pair<IndividuoReal, IndividuoReal> newIndividuosCrossover;
	IndividuoReal newIndividuo1 = this->populacao[individuo1];
	IndividuoReal newIndividuo2 = this->populacao[individuo2];
	vector<double> genesInd1 = this->populacao[individuo1].getGenes(), genesInd2 =
			this->populacao[individuo2].getGenes();
	if (this->chanceCrossover >= a) {
		static uniform_int_distribution<int> numRandon(0, this->genesInicial.size() - 1);
		a = numRandon(mt);
		for (var = 0; var < a; ++var) {
			genesInd1.push_back(this->populacao[individuo2].getGenes().at(var));
			genesInd2.push_back(this->populacao[individuo1].getGenes().at(var));
		}
		for (; var < this->genesInicial.size() - 1; ++var) {
			genesInd1.push_back(this->populacao[individuo1].getGenes().at(var));
			genesInd2.push_back(this->populacao[individuo2].getGenes().at(var));
		}
		newIndividuo1.setGenes(genesInd1);
		newIndividuo2.setGenes(genesInd2);
	}
	newIndividuosCrossover = make_pair(newIndividuo1, newIndividuo2);
	return newIndividuosCrossover;
}

const pair<IndividuoReal, IndividuoReal> PopulacaoReal::crossoverArithmetic(int individuo1,
		int individuo2) {
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 99);
	int probCross = bit(mt);
	double a = 0.7;
	pair<IndividuoReal, IndividuoReal> newIndividuosCrossover;
	IndividuoReal newIndividuo1 = this->populacao[individuo1];
	IndividuoReal newIndividuo2 = this->populacao[individuo2];
	vector<double> genesInd1, genesInd2;

	if (this->chanceCrossover < probCross) {
		for (int var = 0; var < this->genesInicial.size(); ++var) {
			genesInd1.push_back(
					(a * this->populacao[individuo1].getGenes().at(var))
							+ ((1 - a) * this->populacao[individuo2].getGenes().at(var)));
			genesInd2.push_back(
					((1 - a) * this->populacao[individuo1].getGenes().at(var))
							+ (a * this->populacao[individuo2].getGenes().at(var)));

		}
		newIndividuo1.setGenes(genesInd1);
		newIndividuo2.setGenes(genesInd2);
	}

	newIndividuosCrossover = make_pair(newIndividuo1, newIndividuo2);
	return newIndividuosCrossover;
}

const pair<IndividuoReal, IndividuoReal> PopulacaoReal::crossoverBLX(int individuo1,
		int individuo2) {
	static mt19937 mt(time(NULL));
	double d, a = 0.5, u, x, y;
	pair<IndividuoReal, IndividuoReal> newIndividuosCrossover;
	IndividuoReal newIndividuo1 = this->populacao[individuo1];
	IndividuoReal newIndividuo2 = this->populacao[individuo2];
	vector<double> genesInd1, genesInd2;

	for (int var = 0; var < this->genesInicial.size(); ++var) {
		x = this->populacao[individuo1].getGenes().at(var);
		y = this->populacao[individuo2].getGenes().at(var);
		d = abs(x - y);

		static uniform_real_distribution<double> numRandon(min(x, y) - (a * d),
				max(x, y) + (a * d));

		u = numRandon(mt);
		if (u < this->genesInicial.at(var).first)
			u = this->genesInicial.at(var).first;

		if (u > this->genesInicial.at(var).second)
			u = this->genesInicial.at(var).second;

		genesInd1.push_back(u);
		u = numRandon(mt);
		if (u < this->genesInicial.at(var).first)
			u = this->genesInicial.at(var).first;

		if (u > this->genesInicial.at(var).second)
			u = this->genesInicial.at(var).second;
		genesInd2.push_back(u);

	}
	newIndividuo1.setGenes(genesInd1);
	newIndividuo2.setGenes(genesInd2);
	newIndividuosCrossover = make_pair(newIndividuo1, newIndividuo2);
	return newIndividuosCrossover;

}

const pair<IndividuoReal, IndividuoReal> PopulacaoReal::crossoverUniformAverage(int individuo1,
		int individuo2) {
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> bit(0, 99);
	int a = bit(mt);
	pair<IndividuoReal, IndividuoReal> newIndividuosCrossover;
	IndividuoReal newIndividuo1 = this->populacao[individuo1];
	IndividuoReal newIndividuo2 = this->populacao[individuo2];
	vector<double> genesInd1 = this->populacao[individuo1].getGenes(), genesInd2 =
			this->populacao[individuo2].getGenes();

	if (this->chanceCrossover > a) {
		static uniform_int_distribution<int> numRandon(0, 1);
		for (int var = 0; var < this->genesInicial.size(); ++var) {
			a = numRandon(mt);
			if (a == 1) {
				genesInd1.push_back(this->populacao[individuo2].getGenes().at(var));
				genesInd2.push_back(this->populacao[individuo1].getGenes().at(var));
				newIndividuo1.setGenes(genesInd1);
				newIndividuo2.setGenes(genesInd2);
			}
		}
	}
	newIndividuosCrossover = make_pair(newIndividuo1, newIndividuo2);
	return newIndividuosCrossover;
}

const IndividuoReal PopulacaoReal::crowding(int individuoCrowding) {
	static mt19937 mt(time(NULL));
	static uniform_int_distribution<int> numRandon(0, this->qtdIndividuos);
	IndividuoReal individuoAuxiliar;
	int numeroAleatorio;

	for (int var = 0; var < this->cCrowding; ++var) {
		numeroAleatorio = numRandon(mt);
		if (euclidiana(this->populacao[individuoCrowding].getFitness(),
				this->populacao[numeroAleatorio].getFitness()))
			;
		//Não entendi quando subtitui, como assim substitui na população antiga?
	}
	return individuoAuxiliar;
}

double PopulacaoReal::distanciaRealFenotipica() {
	IndividuoReal ind1, ind2;
	double fitnessInd1, fitnessInd2, dist = 0;
	for (int x = 0; x < this->populacao.size(); ++x) {
		ind1 = this->populacao[x];
		fitnessInd1 = ind1.getFitness();
		for (int y = x + 1; y < this->populacao.size(); ++y) {
			ind2 = this->populacao[y];
			fitnessInd2 = ind2.getFitness();
			dist += euclidiana(fitnessInd1, fitnessInd2);
		}
	}
	return dist;
}

IndividuoReal PopulacaoReal::getBestIndividuo() {
	this->bestIndividuo = this->populacao[0];
	for (int var = 0; var < this->populacao.size(); ++var) {
		if (this->bestIndividuo.getFitness() < this->populacao[var].getFitness()) {
			this->bestIndividuo = this->populacao[var];
		}
	}
	return this->bestIndividuo;
}

const IndividuoReal PopulacaoReal::getIndividuo(int index) {
	return this->populacao[index];
}

const vector<IndividuoReal>& PopulacaoReal::getPopulacao() const {
	return this->populacao;
}

const int PopulacaoReal::getQuantidadeGenes() {
	return this->genesInicial.size();
}

int PopulacaoReal::getQuantidadeIndividuos() const {
	return this->populacao.size();
}

const IndividuoReal PopulacaoReal::getWorseIndividuo() {
	this->worseIndividuo = this->populacao[0];
	for (int var = 0; var < this->populacao.size(); ++var) {
		if (this->worseIndividuo.getFitness() > this->populacao[var].getFitness()) {
			this->worseIndividuo = this->populacao[var];
		}
	}
	return this->worseIndividuo;
}

void PopulacaoReal::incrementaC() {
	int geracoes = this->entrada["geracoes"];
	geracoes = geracoes * 0.8;
	this->C += 0.8 / geracoes;
//cout << this->C << endl;
}

void PopulacaoReal::insertIndividuo(IndividuoReal newIndividuo) {
	this->populacao.push_back(newIndividuo);
}

void PopulacaoReal::insertIndividuo(IndividuoReal newIndividuo, int posicao) {
	this->populacao[posicao] = newIndividuo;
}

double PopulacaoReal::mediaFitness() {
	double media = 0;
	IndividuoReal ind;
	for (int var = 0; var < this->populacao.size(); ++var) {
		ind = this->populacao[var];
		media += ind.getFitness();
	}
	return media / this->populacao.size();
}

void PopulacaoReal::mutacaoPopulacao() {
	for (int var = 0; var < this->qtdIndividuos; ++var) {
		this->populacao[var].mutacao();
	}
}

void PopulacaoReal::openJson() {
	using json = nlohmann::json;
	ifstream texto("entrada.json");
	stringstream buffer;
	buffer << texto.rdbuf();
	this->entrada = json::parse(buffer.str());
	texto.close();
}

const PopulacaoReal PopulacaoReal::rollet() {
	static mt19937 mt(time(NULL));
	pair<IndividuoReal, IndividuoReal> newIndivuos;
	PopulacaoReal newPop;
	newPop.populacao.clear();
	int var, valorDaRollet = 0, individuoParaCross[1] { 0 }, auxInsertIndv = 0;
	double valorTotalFitness = 0.0, valorAcumuladoFitness = 0.0;
	for (var = 0; var < this->qtdIndividuos; ++var) {
		if (this->fitnessEscalonado)
			valorTotalFitness += calculoFitnessEscalonado(this->populacao[var].getFitness());
		else
			valorTotalFitness += this->populacao[var].getFitness();
	}
	for (int loopNovosIndiv = 0; loopNovosIndiv < (this->qtdIndividuos * this->gap) / 2; // * (this->gap / 100)
			++loopNovosIndiv) {
		for (int loop = 0; loop < 2; ++loop) {
			static uniform_int_distribution<int> numeroRandom(0, 100);
			valorDaRollet = numeroRandom(mt);
			for (var = 0; var < this->qtdIndividuos - 1; ++var) {
				if (this->fitnessEscalonado)
					valorAcumuladoFitness += ((double) calculoFitnessEscalonado(
							this->populacao[var].getFitness()) / valorTotalFitness) * 100;
				else
					valorAcumuladoFitness += ((double) this->populacao[var].getFitness()
							/ valorTotalFitness) * 100;
				if (valorDaRollet < valorAcumuladoFitness)
					break;
			}
			valorAcumuladoFitness = 0;
			individuoParaCross[loop] = var;
		}
		newIndivuos = sendCrossover(individuoParaCross[0], individuoParaCross[1]);
		newPop.insertIndividuo(newIndivuos.first);
		newPop.insertIndividuo(newIndivuos.second);
	}
	for (int count = newPop.getQuantidadeIndividuos(); count < this->qtdIndividuos; ++count)
		newPop.insertIndividuo(this->populacao[count]);
	newPop.mutacaoPopulacao();
	if (this->elitismo == true)
		newPop.insertIndividuo(this->getBestIndividuo(), 1);
	return newPop;
}

pair<IndividuoReal, IndividuoReal> PopulacaoReal::sendCrossover(int indiv1, int indiv2) {
	pair<IndividuoReal, IndividuoReal> newIndivuos;
	switch (this->tipoCrossover) {
	case 1:
		newIndivuos = crossover(indiv1, indiv2);
		break;
	case 2:
		newIndivuos = crossoverArithmetic(indiv1, indiv2);
		break;
	case 3:
		newIndivuos = crossoverUniformAverage(indiv1, indiv2);
		break;
	case 4:
		newIndivuos = crossoverBLX(indiv1, indiv2);
		break;
	default:
		break;
	}
	return newIndivuos;
}

void PopulacaoReal::setPopulacao(const vector<IndividuoReal>& populacao) {
	this->populacao = populacao;
}

double PopulacaoReal::summationDistanceFenotipica() {
	IndividuoReal ind1, ind2;
	double fitnessInd1, fitnessInd2, distancia = 0;
	for (int x = 0; x < this->qtdIndividuos; ++x) {
		ind1 = this->populacao[x];
		fitnessInd1 = ind1.getFitness();
		for (int y = x + 1; y < this->qtdIndividuos; ++y) {
			ind2 = this->populacao[y];
			fitnessInd2 = ind2.getFitness();
			for (int var = 0; var < this->getQuantidadeGenes(); ++var) {
				distancia += euclidiana(fitnessInd1, fitnessInd2);
			}
		}
	}
	return distancia;
}

double PopulacaoReal::summationDistanceGenotipica() {
	IndividuoReal ind1, ind2;
	vector<double> genesIndividuo1, genesIndividuo2;
	double distancia = 0;
	for (int x = 0; x < this->qtdIndividuos; ++x) {
		ind1 = this->populacao[x];
		genesIndividuo1 = ind1.getGenes();
		for (int y = x + 1; y < this->qtdIndividuos; ++y) {
			ind2 = this->populacao[y];
			genesIndividuo2 = ind2.getGenes();
			for (int var = 0; var < this->getQuantidadeGenes(); ++var) {
				distancia +=
						(euclidiana(genesIndividuo1.at(var), genesIndividuo2.at(var)) / (x * y));
			}
		}
	}
	return distancia;
}

const PopulacaoReal PopulacaoReal::tournament() {
	static mt19937 mt(time(NULL));
	pair<IndividuoReal, IndividuoReal> newIndivuos;
	IndividuoReal indRand, indAux;
	PopulacaoReal newPop;
	newPop.populacao.clear();
	int individuoParaCross[1] { 0 }, auxInsertIndv = 0, indvDoTournament;
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
				if (indRand.getFitness() > indAux.getFitness())
					individuoParaCross[qtdIndvParaCross] = indvDoTournament;
			}
		}
		newIndivuos = sendCrossover(individuoParaCross[0], individuoParaCross[1]);
		newPop.insertIndividuo(newIndivuos.first);
		newPop.insertIndividuo(newIndivuos.second);
	}
	for (int count = newPop.getQuantidadeIndividuos(); count < this->qtdIndividuos; ++count)
		newPop.insertIndividuo(this->populacao[count]);
	newPop.mutacaoPopulacao();
	if (this->elitismo == true)
		newPop.insertIndividuo(this->getBestIndividuo(), 1);
	return newPop;
}

} /* namespace std */
