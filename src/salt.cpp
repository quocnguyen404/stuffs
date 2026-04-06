#include "salt.h"
#include <random>

static std::random_device rd;
static std::mt19937 gen(rd());
static std::uniform_real_distribution<> distr(0.0, 1.0);

float GetRandom() {
    return distr(gen);
}

int GetRange(int a, int b) {
    std::uniform_int_distribution<> d(a, b);
    return d(gen);
}