/*
 * PopulacaoBinario.h
 *
 *  Created on: 16 de abr de 2016
 *      Author: deko
 */

#ifndef SRC_POPULACAOBINARIO_HPP_
#define SRC_POPULACAOBINARIO_HPP_

#include <fstream>
#include "IndividuoBinario.hpp"
#include "Populacao.hpp"
#include "json.hpp"

using json = nlohmann::json;
namespace std {

class PopulacaoBinario: public Populacao {
public:
	PopulacaoBinario();
	virtual ~PopulacaoBinario();
	double calculoFitnessEscalonado(double fitness);
	void incrementaC();
	pair<double, double> calculoEscalonadoMenor();
	pair<double, double> calculoEscalonadoMaior();
	double mediaFitness();
	const vector<IndividuoBinario>& getPopulacao() const;
	void setPopulacao(const vector<IndividuoBinario>& populacao);
	void setIndividuo(int, IndividuoBinario);
	void print_populacao();
	void print_individuo(int id);
	void insertIndividuo(IndividuoBinario newIndividuo);
	void insertIndividuo(IndividuoBinario newIndividuo, int posicao);
	const IndividuoBinario getIndividuo(int index);
	IndividuoBinario getBestIndividuo();
	const IndividuoBinario getWorseIndividuo();
	const pair<IndividuoBinario, IndividuoBinario> crossover(int, int);
	const pair<IndividuoBinario, IndividuoBinario> crossoverUniforme(int, int);
	const PopulacaoBinario rollet();
	const PopulacaoBinario tournament();
	int getQtdIndividuos() const;
	void mutacaoPopulacao();
	void openJson();

private:
	vector<IndividuoBinario> populacao;
	IndividuoBinario bestIndividuo;
	IndividuoBinario worseIndividuo;
	json entrada;
};

} /* namespace std */

#endif /* SRC_POPULACAOBINARIO_HPP_ */
