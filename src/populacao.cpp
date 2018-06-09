#include "populacao.h"
#include "utils.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <iomanip>

Populacao::Populacao()
{
    // construtor vazio
}

Populacao::Populacao(int tamanho)
{
    Populacao();

    for (int i = 0; i < tamanho; i++)
    {
        individuos.push_back(Individuo(8, 4));
    }

    atualizar();
}

Populacao::Populacao(std::vector<Individuo> individuos)
{
    Populacao();

    for (auto const &individuo : individuos)
    {
        this->individuos.push_back(individuo);
    }

    atualizar();
}

void Populacao::set_individuos(std::vector<Individuo> individuos)
{
    this->individuos = individuos;

    atualizar();
}

void Populacao::set_geracao(int geracao)
{
    this->geracao = geracao;
}

std::vector<Individuo> Populacao::get_individuos()
{
    return individuos;
}

std::map<Individuo, std::pair<double, double>> Populacao::get_roleta()
{
    return roleta;
}

int Populacao::tamanho()
{
    return individuos.size();
}

double Populacao::fitness()
{
    double fitness = 0;

    for (int i = 0; i < individuos.size(); i++)
    {
        fitness += individuos[i].fitness();
    }

    return fitness;
}

double Populacao::media_fitness()
{
    return fitness() / individuos.size();
}

void Populacao::atualizar_roleta()
{
    double pop_fitness = fitness();
    double start = 0.0;
    double end = 0.0;

    roleta.clear();

    for (int i = 0; i < individuos.size(); i++)
    {
        start = end;
        end = start + (individuos[i].fitness() / pop_fitness);

        if (i == (individuos.size() - 1))
        {
            end = 1.0;
        }

        roleta.insert(std::make_pair(individuos[i], std::make_pair(start, end)));
    }
}

// Indivíduos mais aptos primeiro
void Populacao::ordenar()
{
    std::sort(individuos.begin(), individuos.end(), Individuo::comparar_aptidao);
}

void Populacao::atualizar()
{
    atualizar_roleta();
    ordenar();
}

void Populacao::print()
{
    std::cout << std::right;
    std::cout << "Geração " << std::setfill('0') << std::setw(3) << geracao;
    std::cout << " - Média fitness: " << std::setfill('0') << std::setw(6) << media_fitness();
    std::cout << " - Melhor indivíduo: ";
    get_individuos()[0].print();
    std::cout << std::endl;
}
