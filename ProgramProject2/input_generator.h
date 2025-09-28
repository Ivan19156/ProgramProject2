#pragma once
#include <vector>
#include <random>

inline std::vector<int> generate_sequence(size_t size, int min = 0, int max = 1000000) {
    
    std::vector<int> v;
    v.reserve(size);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(min, max);

    for (size_t i = 0; i < size; ++i)
        v.push_back(dist(gen));

    return v;
}
