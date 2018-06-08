#ifndef ALGORITMOGENETICO_H
#define ALGORITMOGENETICO_H

#include <string>
#include <vector>
#include "populacao.h"

class AlgoritmoGenetico
{
public:
    AlgoritmoGenetico(double tx_crossover, double tx_mutacao, Populacao populacao);

    Populacao proxima_geracao(Populacao populacao);
    Individuo torneio(std::vector<Individuo> individuos);
    Individuo mutar(Individuo individuo);
    std::array<Individuo, 2> selecionar_pais(std::vector<Individuo> individuos);
    std::array<Individuo, 2> crossover(Individuo a, Individuo b, std::string tipo);
    std::array<Individuo, 2> crossover_uniforme(Individuo a, Individuo b);
    std::array<Individuo, 2> crossover_um_ponto(Individuo a, Individuo b);
    std::array<Individuo, 2> crossover_dois_pontos(Individuo a, Individuo b);
    void executar(int geracoes);
    void print();

private:
    double tx_crossover;               // Probabilidade de ocorrência de crossover
    double tx_mutacao;                 // Probabilidade de ocorrência de mutação
    std::vector<Populacao> populacoes; // Todas as populações geradas
};

#endif
