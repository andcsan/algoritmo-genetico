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
    void set_geracao(int geracao);

    // getters
    std::vector<Individuo> get_individuos();
    int get_tamanho();
    double get_fitness();

    // métodos
    void add_individuo(Individuo individuo);
    void sort();
    void print();

private:
    int geracao;
    std::vector<Individuo> individuos; // População de indivíduos
};

#endif // !POPULACAO_H
