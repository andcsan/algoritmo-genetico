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

    sort();
}

void Populacao::set_individuos(std::vector<Individuo> individuos)
{
    this->individuos = individuos;
}

void Populacao::set_geracao(int geracao)
{
    this->geracao = geracao;
}

std::vector<Individuo> Populacao::get_individuos()
{
    return individuos;
}

int Populacao::get_tamanho()
{
    return individuos.size();
}

double Populacao::get_fitness()
{
    double fitness = 0;

    for (int i = 0; i < individuos.size(); i++)
    {
        fitness += individuos[i].fitness();
    }

    return fitness / individuos.size();
}

void Populacao::add_individuo(Individuo individuo)
{
    individuos.push_back(individuo);
}

// Indivíduos mais aptos primeiro
void Populacao::sort()
{
    std::sort(individuos.begin(), individuos.end(), Individuo::comparar);
}

void Populacao::print()
{
    std::cout << std::right;
    std::cout << "Geração " << std::setfill('0') << std::setw(3) << geracao;
    std::cout << " - Fitness: " << std::setfill('0') << std::setw(6) << get_fitness();
    std::cout << " - Melhor indivíduo: ";
    get_individuos()[0].print();
    std::cout << std::endl;
}
