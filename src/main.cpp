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
    Populacao populacao_inicial = Populacao(100);
    populacao_inicial.set_geracao(0);

    // Cria uma instância do algoritmo genético
    AlgoritmoGenetico ag = AlgoritmoGenetico(0.85, 0.005, populacao_inicial, "roleta", "dois_pontos");

    // Executa 100 gerações
    ag.executar(5000);

    return 0;
}
