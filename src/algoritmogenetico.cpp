#include "algoritmogenetico.h"
#include <cstdlib>

#include "populacao.h"
#include "utils.h"
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
        Populacao novaPopulacao = proxima_geracao(populacoes[populacoes.size() - 1]);
        populacoes.push_back(novaPopulacao);
    }
}

// Calcula a proxima geração de uma população
Populacao AlgoritmoGenetico::proxima_geracao(Populacao populacao)
{
    std::vector<Individuo> individuos = populacao.get_individuos();

    Populacao proxima_geracao = Populacao();

    std::array<Individuo, 2> pais;
    std::array<Individuo, 2> filhos;

    for (int i = 0; i < individuos.size() / 2; i++)
    {
        pais = selecionar_pais(individuos);
        filhos = crossover(pais[0], pais[1]);
        filhos[0] = mutar(filhos[0]);
        filhos[1] = mutar(filhos[1]);
        proxima_geracao.add_individuo(filhos[0]);
        proxima_geracao.add_individuo(filhos[1]);
    }

    // Ordena a próxima geração pelo individuo com maior fitness
    proxima_geracao.sort();

    return proxima_geracao;
}

// Seleciona os pais para o crossover com algoritmo de torneio
std::array<Individuo, 2> AlgoritmoGenetico::selecionar_pais(std::vector<Individuo> individuos)
{
    Individuo candidato1 = torneio(individuos);
    Individuo candidato2 = torneio(individuos);

    return std::array<Individuo, 2>{candidato1, candidato2};
}

// Seleciona dois individuos aleatórios da população e retorna o com melhor fitness
Individuo AlgoritmoGenetico::torneio(std::vector<Individuo> individuos)
{
    Individuo a = individuos[rand() % individuos.size()];
    Individuo b = individuos[rand() % individuos.size()];

    if (a.fitness() > b.fitness())
    {
        return a;
    }

    return b;
}

// Cruzamento uniforme dos individuos aplicando a probabilidade de crossover
std::array<Individuo, 2> AlgoritmoGenetico::crossover(Individuo a, Individuo b)
{
    std::array<Individuo, 2> crossover = {a, b};

    if (random_double() < tx_crossover)
    {
        // Crossover uniforme
        for (int posicao = 0; posicao < a.get_cromossomo().size(); posicao++)
        {
            if (rand() % 2 == 0)
            {
                crossover[0].set_gene(posicao, b.get_gene(posicao));
                crossover[1].set_gene(posicao, a.get_gene(posicao));
            }
            else
            {
                crossover[0].set_gene(posicao, b.get_gene(posicao));
                crossover[1].set_gene(posicao, a.get_gene(posicao));
            }
        }
    }

    return crossover;
}

// Mutação do individuo aplicando a taxa de mutação
Individuo AlgoritmoGenetico::mutar(Individuo individuo)
{
    if (random_double() < tx_mutacao)
    {
        individuo.mutar();
    }

    return individuo;
}

void AlgoritmoGenetico::print()
{
    for (int i = 0; i < populacoes.size(); i++)
    {
        std::cout << "Geração " << i << ": " << populacoes[i].get_fitness() << std::endl;
    }
}
