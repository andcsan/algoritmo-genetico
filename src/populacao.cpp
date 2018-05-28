#include "populacao.h"
#include "utils.h"
#include <cstdlib>
#include <iostream>
#include <algorithm>

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
}

std::vector<Individuo> Populacao::get_individuos()
{
    return individuos;
}

void Populacao::set_individuos(std::vector<Individuo> individuos)
{
    this->individuos = individuos;
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
    for (int i = 0; i < individuos.size(); i++)
    {
        std::cout << individuos[i].fitness();
    }
}
