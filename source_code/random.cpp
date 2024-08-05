#include <ctime>
#include <random>
#include "random.h"

int randomNum(int a, int b)
{
    std::mt19937 gen(static_cast<unsigned>(std::time(0)));
    std::uniform_int_distribution<> dist(a, b);

    return dist(gen);
}