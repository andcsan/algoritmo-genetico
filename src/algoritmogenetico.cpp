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
        Populacao ultimaPopulacao = populacoes[populacoes.size() - 1];
        std::vector<int> ultimosIndividuos = ultimaPopulacao.get_individuos();
        Populacao novaPopulacao = Populacao();

        std::array<int, 2> filhos;

        for (int i = 0; i < ultimaPopulacao.get_tamanho() / 2; i++)
        {
            int pai = ultimosIndividuos[rand() % ultimaPopulacao.get_tamanho()];
            int mae = ultimosIndividuos[rand() % ultimaPopulacao.get_tamanho()];

            filhos[0] = pai + floor(mae * (rand() % 2) * tx_crossover);
            filhos[1] = mae + floor(pai * (rand() % 2) * tx_crossover);

            for (int j = 0; j < 2; j++)
            {
                if (filhos[j] > 100)
                {
                    filhos[j] = 100;
                }

                if (rand() % 100 < tx_mutacao)
                {
                    filhos[j] = rand() % 100;
                }
            }

            novaPopulacao.add_individuo(filhos[0]);
            novaPopulacao.add_individuo(filhos[1]);

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
