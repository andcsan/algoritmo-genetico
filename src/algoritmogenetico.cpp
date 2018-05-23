#include "algoritmogenetico.h"
#include <cstdlib>

#include "populacao.h"
#include <iostream>
#include <array>
#include <cmath>

// Construtor
AlgoritmoGenetico::AlgoritmoGenetico(double txcrossover, double txmutacao, Populacao populacao)
{
    this->txcrossover = txcrossover;
    this->txmutacao = txmutacao;
    this->populacoes.push_back(populacao);
}

// Executa x gerações da última população
void AlgoritmoGenetico::executar(int geracoes)
{
    for (int i = 0; i < geracoes; i++)
    {
        Populacao ultimaPopulacao = populacoes[populacoes.size() - 1];
        std::vector<int> ultimosIndividuos = ultimaPopulacao.get_individuos();
        Populacao novaPopulacao = Populacao();

        std::array<int, 2> filhos;

        for (int i = 0; i < ultimaPopulacao.get_tamanho() / 2; i++)
        {
            // Selecionar os pais e fazer o crossover
            // Mutar os filhos
            // Adicionar os filhos na nova população
        }
    }
}

void AlgoritmoGenetico::print()
{
    for (int i = 0; i < populacoes.size(); i++)
    {
        std::cout << "Geração " << i << ": " << populacoes[i].get_fitness() << std::endl;
    }
}
