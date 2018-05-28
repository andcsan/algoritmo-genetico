#ifndef INDIVIDUO_H
#define INDIVIDUO_H

#include <vector>
#include <array>

class Individuo
{
public:
    Individuo();
    Individuo(int genes, int bits_por_gene);

    // setters
    void set_cromossomo(std::vector<bool> cromossomo);
    void set_gene(int posicao, bool value);

    // getters
    std::vector<bool> get_cromossomo();
    bool get_gene(int posicao);

    // métodos
    void mutar();
    void mutar_gene(int posicao);
    std::vector<int> numerico(); // Representação numérica do indivíduo
    int fitness();
    void print();

    static bool comparar(Individuo a, Individuo b);

private:
    std::vector<bool> cromossomo;
    int genes;
    int bits_por_gene;
};

#endif // !INDIVIDUO_H
