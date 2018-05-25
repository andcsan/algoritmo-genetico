#include "algoritmogenetico.h"
#include <cstdlib>

#include "populacao.h"
#include <iostream>
#include <array>
#include <cmath>

// Construtor
AlgoritmoGenetico::AlgoritmoGenetico(double tx_crossover, double tx_mutacao, Populacao populacao)
{
    this->tx_crossover = tx_crossover;
    this->tx_mutacao = tx_mutacao;
    this->populacoes.push_back(populacao);
}

// Executa x gerações da última população
void AlgoritmoGenetico::executar(int geracoes)
{
    for (int i = 0; i < geracoes; i++)
    {
        std::vector<Individuo> ultima_geracao = populacoes[populacoes.size() - 1].get_individuos();

        Populacao novaPopulacao = Populacao();

        std::array<Individuo, 2> filhos;

        for (int i = 0; i < ultima_geracao.size() / 2; i++)
        {
            // Selecionar os pais e fazer o crossover
            // Mutar os filhos
            // Adicionar os filhos na nova população
        }

        novaPopulacao.sort();

        populacoes.push_back(novaPopulacao);
    }
}

void AlgoritmoGenetico::print()
{
    for (int i = 0; i < populacoes.size(); i++)
    {
        std::cout << "Geração " << i << ": " << populacoes[i].get_fitness() << std::endl;
    }
}
