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
    void set_bit(int posicao, bool value);

    // getters
    std::vector<bool> get_cromossomo();
    bool get_bit(int posicao);

    // métodos
    void mutar();
    void mutar_bit(int posicao);
    void print();
    int fitness();

    // Cromossomo em representação numérica, isto é, vetor dos genes representados por número inteiro
    std::vector<int> cromossomo_numerico();

    static bool comparar(Individuo a, Individuo b);

private:
    std::vector<bool> cromossomo; // lista de bits que representa o indivíduo
    int genes;                    // número de genes (pode-se interpretar como bytes)
    int bits_por_gene;            // número de bits por gene (pode-se interpretar como bits por byte)
};

#endif // !INDIVIDUO_H
