#include "algoritmogenetico.h"
#include <cstdlib>

#include "populacao.h"
#include "utils.h"
#include <iostream>
#include <array>
#include <cmath>
#include <iomanip>

// Construtor
AlgoritmoGenetico::AlgoritmoGenetico(double tx_crossover,
                                     double tx_mutacao,
                                     Populacao populacao,
                                     std::string algoritmo_selecao,
                                     std::string algoritmo_crossover)
{
    this->tx_crossover = tx_crossover;
    this->tx_mutacao = tx_mutacao;
    this->algoritmo_crossover = algoritmo_crossover;
    this->algoritmo_selecao = algoritmo_selecao;
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
    std::array<Individuo, 2> pais;
    std::array<Individuo, 2> filhos;
    std::vector<Individuo> novosIndividuos;

    for (int i = 0; i < populacao.tamanho() / 2; i++)
    {
        pais = selecionar_pais(populacao, algoritmo_selecao);
        filhos = crossover(pais[0], pais[1], algoritmo_crossover);
        filhos[0] = mutar(filhos[0]);
        filhos[1] = mutar(filhos[1]);
        novosIndividuos.push_back(filhos[0]);
        novosIndividuos.push_back(filhos[1]);
    }

    return Populacao(novosIndividuos);
}

// Seleciona os pais para o crossover de acordo com o algoritmo de seleção
std::array<Individuo, 2> AlgoritmoGenetico::selecionar_pais(Populacao populacao, std::string algoritmo)
{
    std::array<Individuo, 2> pais;

    if (algoritmo == "torneio")
    {
        pais[0] = selecao_torneio(populacao);
        pais[1] = selecao_torneio(populacao);
    }
    else if (algoritmo == "roleta")
    {
        pais[0] = selecao_roleta(populacao);
        pais[1] = selecao_roleta(populacao);
    }

    return pais;
}

// Seleciona dois individuos aleatórios da população e retorna o mais apto
Individuo AlgoritmoGenetico::selecao_torneio(Populacao populacao)
{
    std::vector<Individuo> individuos = populacao.get_individuos();

    Individuo a = individuos[rand() % individuos.size()];
    Individuo b = individuos[rand() % individuos.size()];

    if (a.fitness() > b.fitness())
    {
        return a;
    }

    return b;
}

// Seleciona um indivíduo com base na roleta
Individuo AlgoritmoGenetico::selecao_roleta(Populacao populacao)
{
    std::vector<Individuo> individuos = populacao.get_individuos();
    std::map<Individuo, std::pair<double, double>> roleta = populacao.get_roleta();
    Individuo individuo;

    double valor = random_double();

    // Busca na roleta o individuo que corresponde ao intervalo do valor aleatório gerado
    for (auto it = roleta.begin(); it != roleta.end(); it++)
    {
        if (valor >= it->second.first && valor < it->second.second)
        {
            individuo = it->first;
            break;
        }
    }

    return individuo;
}

// Cruzamento dos indivíduos aplicando a probabilidade de crossover e o algoritmo de crossover
std::array<Individuo, 2> AlgoritmoGenetico::crossover(Individuo a, Individuo b, std::string algoritmo)
{
    if (random_double() < tx_crossover)
    {
        if (algoritmo == "uniforme")
        {
            return crossover_uniforme(a, b);
        }

        if (algoritmo == "um_ponto")
        {
            return crossover_um_ponto(a, b);
        }

        if (algoritmo == "dois_pontos")
        {
            return crossover_dois_pontos(a, b);
        }
    }

    // Se não ocorrer crossover, retorna os pais sem alteração
    return std::array<Individuo, 2>{a, b};
}

// Crossover uniforme
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
        std::cout << "Geração " << i << " - Média fitness: " << populacoes[i].media_fitness() << std::endl;
    }
}
