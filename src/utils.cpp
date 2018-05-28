#include "utils.h"
#include <cstdlib>

double random_double()
{
    return (double)rand() / (double)RAND_MAX;
}

int const binario_para_decimal(std::vector<bool> bits)
{
    int decimal = 0;

    for (std::vector<bool>::iterator it = bits.begin(); it != bits.end(); ++it)
    {
        *it ? decimal = (decimal << 1) + 1 : decimal <<= 1;
    }

    return decimal;
}
