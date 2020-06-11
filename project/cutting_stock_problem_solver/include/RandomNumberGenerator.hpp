#pragma once

#include <thread>
#include <random>

// Sources: 
// https://stackoverflow.com/questions/21237905/how-do-i-generate-thread-safe-uniform-random-numbers
// https://en.cppreference.com/w/cpp/numeric/random/uniform_int_distribution
// https://gist.github.com/srivathsanmurali/6ca74bdf154b0f5447321be183ba28d1
int randomInteger(const int lowerBound, const int upperBound);

double randomUniformRealNumber();

double randomNormalRealNumber();