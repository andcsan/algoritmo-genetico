#include "algoritmogenetico.h"
#include <cstdlib>

#include "populacao.h"
#include "utils.h"
#include <iostream>
#include <array>
#include <cmath>
#include <iomanip>

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
    populacoes.front().print();

    for (int i = 0; i < geracoes; i++)
    {
        Populacao novaPopulacao = proxima_geracao(populacoes[populacoes.size() - 1]);
        novaPopulacao.set_geracao(i + 1);
        novaPopulacao.print();
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
        filhos = crossover(pais[0], pais[1], "dois_pontos");
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
std::array<Individuo, 2> AlgoritmoGenetico::crossover(Individuo a, Individuo b, std::string tipo)
{
    if (random_double() < tx_crossover)
    {
        if (tipo == "uniforme")
        {
            return crossover_uniforme(a, b);
        }

        if (tipo == "um_ponto")
        {
            return crossover_um_ponto(a, b);
        }

        if (tipo == "dois_pontos")
        {
            return crossover_dois_pontos(a, b);
        }
    }

    // Se não ocorrer crossover, retorna os pais sem alteração
    return std::array<Individuo, 2>{a, b};
}

std::array<Individuo, 2> AlgoritmoGenetico::crossover_uniforme(Individuo a, Individuo b)
{
    std::array<Individuo, 2> crossover = {a, b};

    // Crossover uniforme
    for (int posicao = 0; posicao < a.get_cromossomo().size(); posicao++)
    {
        if (rand() % 2 == 0)
        {
            crossover[0].set_bit(posicao, b.get_bit(posicao));
            crossover[1].set_bit(posicao, a.get_bit(posicao));
        }
        else
        {
            crossover[0].set_bit(posicao, b.get_bit(posicao));
            crossover[1].set_bit(posicao, a.get_bit(posicao));
        }
    }

    return crossover;
}

// Crossover um ponto
std::array<Individuo, 2> AlgoritmoGenetico::crossover_um_ponto(Individuo a, Individuo b)
{
    std::array<Individuo, 2> crossover = {a, b};

    int posicao = rand() % a.get_cromossomo().size();

    // Na posição aleatória escolhida, troca os bits dos pais
    for (int i = 0; i < posicao; i++)
    {
        crossover[0].set_bit(i, b.get_bit(i));
        crossover[1].set_bit(i, a.get_bit(i));
    }

    return crossover;
}

// Crossover dois pontos, semelhante ao um ponto, mas com dois pontos de troca
std::array<Individuo, 2> AlgoritmoGenetico::crossover_dois_pontos(Individuo a, Individuo b)
{
    std::array<Individuo, 2> crossover = {a, b};

    int posicao1 = rand() % a.get_cromossomo().size();
    int posicao2 = rand() % a.get_cromossomo().size();

    // Ordena as posições para que a menor seja a primeira
    if (posicao1 > posicao2)
    {
        int aux = posicao1;
        posicao1 = posicao2;
        posicao2 = aux;
    }

    // Na posição aleatória escolhida, troca os bits dos pais
    for (int i = posicao1; i < posicao2; i++)
    {
        crossover[0].set_bit(i, b.get_bit(i));
        crossover[1].set_bit(i, a.get_bit(i));
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
