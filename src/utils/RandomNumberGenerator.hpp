#pragma once
#include <random>
#include <time.h>

// use the current time as the generator's seed to guarantee different random sequences at each run
std::mt19937 randomNumberGenerator(time(nullptr));