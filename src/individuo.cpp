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

void Individuo::set_bit(int posicao, bool value)
{
    this->cromossomo[posicao] = value;
}

std::vector<bool> Individuo::get_cromossomo()
{
    return this->cromossomo;
}

bool Individuo::get_bit(int posicao)
{
    return this->cromossomo.at(posicao);
}

void Individuo::mutar()
{
    int posicao = rand() % this->cromossomo.size();
    this->mutar_bit(posicao);
}

void Individuo::mutar_bit(int posicao)
{
    this->cromossomo[posicao] = !this->cromossomo[posicao];
}

std::vector<int> Individuo::cromossomo_numerico()
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
    std::vector<int> cromossomo_numerico = this->cromossomo_numerico();
    int fitness = 0;

    for (int i = 0; i < genes; i++)
    {
        fitness += cromossomo_numerico[i];
    }

    return fitness;
}

void Individuo::print()
{
    std::cout << std::fixed << std::setprecision(2) << std::left;
    std::cout << "| ";

    for (int gene = 0; gene < genes; gene++)
    {
        for (int bit = 0; bit < bits_por_gene; bit++)
        {
            std::cout << this->cromossomo[gene * bits_por_gene + bit] << " ";
        }

        std::cout << "| ";
    }
}

bool Individuo::comparar_aptidao(Individuo a, Individuo b)
{
    return a.fitness() < b.fitness();
}

bool Individuo::operator<(const Individuo &ob) const
{
    for (int i = 0; i < cromossomo.size(); i++)
    {
        if (cromossomo[i] == ob.cromossomo[i])
        {
            continue;
        }

        return !cromossomo[i];
    }
}

bool Individuo::operator==(const Individuo &ob) const
{
    for (int i = 0; i < cromossomo.size(); i++)
    {
        if (cromossomo[i] == ob.cromossomo[i])
        {
            continue;
        }

        return false;
    }

    return true;
}
