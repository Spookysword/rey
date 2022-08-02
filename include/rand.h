
#ifndef SIMPLEPARTICLES_RAND_H
#define SIMPLEPARTICLES_RAND_H
#include <random>

std::random_device rd;
std::mt19937 gen;

void initRandom() {
    gen = std::mt19937(rd());
}

int randInt(int a, int b) {
    std::uniform_int_distribution<> dist(a,b);

    return dist(gen);
}

bool randBool() {
    std::uniform_int_distribution<> dist(0, 1);

    return dist(gen);
}

#endif //SIMPLEPARTICLES_RAND_H
