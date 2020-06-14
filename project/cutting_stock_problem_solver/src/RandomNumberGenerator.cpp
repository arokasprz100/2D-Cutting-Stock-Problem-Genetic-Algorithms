#include "RandomNumberGenerator.hpp"

int randomInteger(const int lowerBound, const int upperBound) {
    static thread_local std::random_device rd;
    static thread_local std::mt19937 generator(rd());
    std::uniform_int_distribution<int> distribution(lowerBound, upperBound);
    return distribution(generator);
}

double randomUniformRealNumber() {
    static thread_local std::random_device rd;
    static thread_local std::mt19937 generator(rd());
    std::uniform_real_distribution<> distribution;
    return distribution(generator);
}

double randomNormalRealNumber() {
    static thread_local std::random_device rd;
    static thread_local std::mt19937 generator(rd());
    std::normal_distribution<> distribution(0, 50);
    return distribution(generator);
}