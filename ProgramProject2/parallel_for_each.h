#pragma once
#include <vector>
#include <thread>
#include <algorithm>
#include <functional>

template<typename T, typename F>
void parallel_for_each(std::vector<T>& v, F op, size_t K) {
    if (K == 0) K = 1; 
    size_t n = v.size();
    std::vector<std::thread> threads;
    size_t chunk_size = n / K;

    size_t start = 0;
    for (size_t i = 0; i < K; ++i) {
        size_t end = (i == K - 1) ? n : start + chunk_size;
        threads.emplace_back([start, end, &v, &op]() {
            std::for_each(v.begin() + start, v.begin() + end, op);
            });
        start += chunk_size;
    }

    
    for (auto& t : threads)
        t.join();
}
