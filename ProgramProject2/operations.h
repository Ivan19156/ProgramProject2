#pragma once
#include <cmath>


inline auto light_op = [](int& x) { x += 1; };


inline auto heavy_op = [](int& x) {
    for (int i = 0; i < 100; ++i)
        x = std::sqrt(x + i); 
    };
