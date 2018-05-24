#ifndef ALGORITMOGENETICO_H
#define ALGORITMOGENETICO_H

#include <string>
#include <vector>
#include "populacao.h"

class AlgoritmoGenetico
{
public:
    AlgoritmoGenetico(double tx_crossover, double tx_mutacao, Populacao populacao);
    void executar(int geracoes);
    void print();

private:
    double tx_crossover;
    double tx_mutacao;
    std::vector<Populacao> populacoes;
};

#endif
