#ifndef POPULACAO_H
#define POPULACAO_H

#include <vector>

class Populacao
{
public:
    Populacao();
    Populacao(int tamanho);

    std::vector<int> get_individuos();
    void set_individuos(std::vector<int> individuos);

    int get_tamanho();
    double get_fitness();
    void add_individuo(int individuo);
    void sort();
    void print();

private:
    std::vector<int> individuos; // População de indivíduos
};

#endif // !POPULACAO_H
