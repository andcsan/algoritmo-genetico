#include <iostream>
#include <cstdlib>
#include <ctime>
#include "algoritmogenetico.h"
#include "populacao.h"

int main()
{
    srand(time(0)); // Seed para geração randômica

    std::cout << "Algoritmo genético" << std::endl;

    // Cria população inicial com 100 indivíduos
    Populacao populacao = Populacao(100);
    populacao.set_geracao(0);

    // Algoritmo genético com 0.7 de taxa de crossover e 0.01 de taxa de mutação
    AlgoritmoGenetico ag = AlgoritmoGenetico(0.75, 0.05, populacao);

    // Executa 100 gerações
    ag.executar(100);

    return 0;
}
