#include <cstdint>
#include <iostream>
#include <syncstream>
#include <omp.h>
#include <thread>
#include "../pdv_lib/pdv_lib.hpp"

// do not do this
void parallel_split_if() {
    #pragma omp parallel num_threads(3)
    {
        if (omp_get_thread_num() == 0) {
            std::cout << "I'm thread 0\n";

        } else if (omp_get_thread_num() == 1) {
            std::cout << "I'm thread 1\n";

        } else if (omp_get_thread_num() == 2) {
            std::cout << "I'm thread 2\n";

        } else {
            std::cout << "I don't get to do anything useful\n";
        }
    }
}

// do not do this
void parallel_split_loop() {
    auto vec = pdv::generate_random_vector<float>(100);
    #pragma omp parallel num_threads(vec.size())
    {
        std::osyncstream(std::cout) << "Processing item " << omp_get_thread_num() << "\n";
    };
}

int main() {
    parallel_split_if();
//    parallel_split_loop();
}
