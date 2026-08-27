#pragma once

#include <random>

class RNG
{
public:
    RNG(std::mt19937::result_type seed) { setSeed(seed); }
    RNG() : RNG(0) {}
    void setSeed(std::mt19937::result_type seed) { gen.seed(seed); }
    float uniform() const { return uniform_distribution(gen); }
private:
    mutable std::mt19937 gen;
    mutable std::uniform_real_distribution<float> uniform_distribution { 0, 1 };

};
