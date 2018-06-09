#ifndef POPULACAO_H
#define POPULACAO_H

#include <vector>
#include <map>
#include "individuo.h"

class Populacao
{
public:
    Populacao();                                  // População vazia
    Populacao(int tamanho);                       // População aleatória com x indivíduos
    Populacao(std::vector<Individuo> individuos); // População criada com indivíduos passados por parâmetro

    // setters
    void set_individuos(std::vector<Individuo> individuos);
    void set_geracao(int geracao);

    // getters
    std::vector<Individuo> get_individuos();
    std::map<Individuo, std::pair<double, double>> get_roleta();

    // métodos
    double fitness();       // Soma do fitness de todos os invidíduos
    double media_fitness(); // Média do fitness dos indivíduos
    int tamanho();
    void ordenar();
    void atualizar();
    void atualizar_roleta();
    void print();

private:
    int geracao;
    std::map<Individuo, std::pair<double, double>> roleta;
    std::vector<Individuo> individuos; // População de indivíduos
};

#endif // !POPULACAO_H
