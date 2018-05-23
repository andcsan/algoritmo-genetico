#ifndef ALGORITMOGENETICO_H
#define ALGORITMOGENETICO_H

#include <string>
#include <vector>
#include "populacao.h"

class AlgoritmoGenetico
{
public:
    AlgoritmoGenetico(double txcrossover, double txmutacao, Populacao populacao);
    void executar(int geracoes);
    void print();

private:
    double txcrossover;
    double txmutacao;
    std::vector<Populacao> populacoes;
};

#endif
