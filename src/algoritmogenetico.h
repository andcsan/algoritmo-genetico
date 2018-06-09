#ifndef ALGORITMOGENETICO_H
#define ALGORITMOGENETICO_H

#include <string>
#include <vector>
#include "populacao.h"

class AlgoritmoGenetico
{
public:
    AlgoritmoGenetico(double tx_crossover,
                      double tx_mutacao,
                      Populacao populacao,
                      std::string algoritmo_selecao,
                      std::string algoritmo_crossover);

    Populacao proxima_geracao(Populacao populacao);
    Individuo mutar(Individuo individuo);
    std::array<Individuo, 2> selecionar_pais(Populacao populacao, std::string algoritmo);
    Individuo selecao_torneio(Populacao populacao);
    Individuo selecao_roleta(Populacao populacao);
    std::array<Individuo, 2> crossover(Individuo a, Individuo b, std::string algoritmo);
    std::array<Individuo, 2> crossover_uniforme(Individuo a, Individuo b);
    std::array<Individuo, 2> crossover_um_ponto(Individuo a, Individuo b);
    std::array<Individuo, 2> crossover_dois_pontos(Individuo a, Individuo b);

    void executar(int geracoes);
    void print();

private:
    double tx_crossover;               // Probabilidade de ocorrência de crossover
    double tx_mutacao;                 // Probabilidade de ocorrência de mutação
    std::string algoritmo_selecao;     // Algoritmo de seleção (torneio, roleta)
    std::string algoritmo_crossover;   // Algoritmo de crossover (uniforme, um_ponto, dois_pontos)
    std::vector<Populacao> populacoes; // Todas as populações geradas
};

#endif
