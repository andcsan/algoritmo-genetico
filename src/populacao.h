#ifndef POPULACAO_H
#define POPULACAO_H

#include <vector>
#include "individuo.h"

class Populacao
{
public:
    Populacao();
    Populacao(int tamanho);

    // setters
    void set_individuos(std::vector<Individuo> individuos);

    // getters
    std::vector<Individuo> get_individuos();
    int get_tamanho();
    double get_fitness();

    // métodos
    void add_individuo(Individuo individuo);
    void sort();
    void print();

private:
    std::vector<Individuo> individuos; // População de indivíduos
};

#endif // !POPULACAO_H
