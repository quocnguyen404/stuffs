#ifndef SALT_H
#define SALT_H

#include <random>

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<> distr(1, 100);

float GetRandom() {
    return distr(gen) * 0.01;
}

int GetRange(int min, int max) {
    std::uniform_int_distribution<> d(min, max);
    return d(gen);
}

#endif //SALT_H