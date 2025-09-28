#include <iostream>
#include <vector>
#include <algorithm>
#include <execution>
#include <thread>

#include "input_generator.h"    
#include "operations.h"         
#include "utils.h"              
#include "parallel_for_each.h"  
using namespace std;

int main() {
    try {
        
        size_t n = 1'000'000;
        vector<int> v_original = generate_sequence(n, 0, 1'000'000);
        vector<int> v_temp; 

        
        auto run_test = [&](auto op, auto policy) -> double {
            v_temp = v_original; 
            return measure_time([&]() {
                for_each(policy, v_temp.begin(), v_temp.end(), op);
                });
            };

        
        cout << "Light operation:\n";
        double t_seq_light = run_test(light_op, execution::seq);
        double t_par_light = run_test(light_op, execution::par);
        double t_par_unseq_light = run_test(light_op, execution::par_unseq);

        cout << "  seq:       " << t_seq_light << " ms\n";
        cout << "  par:       " << t_par_light << " ms\n";
        cout << "  par_unseq: " << t_par_unseq_light << " ms\n\n";

        
        cout << "Heavy operation:\n";
        double t_seq_heavy = run_test(heavy_op, execution::seq);
        double t_par_heavy = run_test(heavy_op, execution::par);
        double t_par_unseq_heavy = run_test(heavy_op, execution::par_unseq);

        cout << "  seq:       " << t_seq_heavy << " ms\n";
        cout << "  par:       " << t_par_heavy << " ms\n";
        cout << "  par_unseq: " << t_par_unseq_heavy << " ms\n\n";

        
        size_t max_threads = thread::hardware_concurrency();
        cout << "Parallel for_each timing (own algorithm) — sequence length: " << n << "\n";

        for (size_t K = 1; K <= max_threads * 2; ++K) {
            v_temp = v_original; 
            double t = measure_time([&]() {
                parallel_for_each(v_temp, heavy_op, K);
                });
            cout << "  K=" << K << " threads: " << t << " ms\n";
        }

    }
    catch (const exception& e) {
        cerr << "Error: " << e.what() << "\n";
        return 1;
    }

    return 0;
}
