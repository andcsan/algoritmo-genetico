#include "individuo.h"

#include "utils.h"
#include <cstdlib>
#include <iostream>
#include <iomanip>

Individuo::Individuo()
{
    //
}

Individuo::Individuo(int genes, int bits_por_gene)
{
    this->genes = genes;
    this->bits_por_gene = bits_por_gene;

    // Cromossomo inicia com todos os genes com valor 0
    this->cromossomo = std::vector<bool>(genes * bits_por_gene, false);

    // Inicializa o cromossomo com valores aleatórios
    for (auto gene : this->cromossomo)
    {
        gene = rand() % 2 == 0 ? true : false;
    }
}

void Individuo::set_cromossomo(std::vector<bool> cromossomo)
{
    this->cromossomo = cromossomo;
}

void Individuo::set_gene(int posicao, bool value)
{
    this->cromossomo[posicao] = value;
}

std::vector<bool> Individuo::get_cromossomo()
{
    return this->cromossomo;
}

bool Individuo::get_gene(int posicao)
{
    return this->cromossomo.at(posicao);
}

void Individuo::mutar()
{
    int posicao = rand() % this->cromossomo.size();
    this->mutar_gene(posicao);
}

void Individuo::mutar_gene(int posicao)
{
    this->cromossomo[posicao] = !this->cromossomo[posicao];
}

std::vector<int> Individuo::numerico()
{
    std::vector<int> cromossomo_numerico(genes);
    std::vector<bool> gene(bits_por_gene);

    for (int i = 0; i < genes; i++)
    {
        for (int j = 0; j < bits_por_gene; j++)
        {
            gene[j] = this->cromossomo[i * bits_por_gene + j];
        }

        cromossomo_numerico[i] = binario_para_decimal(gene);
    }

    return cromossomo_numerico;
}

int Individuo::fitness()
{
    std::vector<int> numerico = this->numerico();
    int fitness = 0;

    for (int i = 0; i < genes; i++)
    {
        fitness += numerico[i];
    }

    return fitness;
}

void Individuo::print()
{
    std::cout << std::fixed << std::setprecision(2) << std::left;

    std::cout << "[ ";
    for (auto const &bit : this->cromossomo)
    {
        {
            std::cout << bit << " ";
        }
    }
    std::cout << "]";
    // std::cout << "[";
    // for (auto const &numero : this->numerico())
    // {
    //     std::cout << numero << " ";
    // }
    // std::cout << "]";
}

bool Individuo::comparar(Individuo a, Individuo b)
{
    return a.fitness() < b.fitness();
}
