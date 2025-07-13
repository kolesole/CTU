#include <cstdint>
#include <iostream>
#include <syncstream>
#include <omp.h>
#include <thread>
#include <random>
#include "../pdv_lib/pdv_lib.hpp"

void parallel_num_threads() {
    auto thread_count = 4;
    #pragma omp parallel num_threads(thread_count)
    {
        std::cout << "running thread\n";
    }

    #pragma omp parallel num_threads(2)
    std::cout << "running thread 2\n";
}

void parallel_if() {
    auto rand = pdv::uniform_random<float>(std::random_device()())();
    std::cout << rand << "\n";

    #pragma omp parallel if(rand >= 0.5)
    {
        std::cout << "running thread\n";
    }
}

void parallel_sharing() {
    uint32_t n = 10;

    // all threads have the same variable `n`
    #pragma omp parallel shared(n)
    {
        std::cout << n << "\n";
    }


    // each thread has a private uninitialized variable `n`
    #pragma omp parallel
    {
        n = 0;
        std::osyncstream(std::cout) << "n = " << n << "\n";
    }


    n = 20;
    // each thread has a private variable `n`, initialized from the previous value
    #pragma omp parallel default(none) shared(std::cout) firstprivate(n)
    {
        std::osyncstream(std::cout) << "n = " << n << "\n";
    }
}

void parallel_nested() {
    // enable/disable nested parallelism
    omp_set_nested(false);

    #pragma omp parallel num_threads(2)
    {
        std::cout << "before nesting\n";

        #pragma omp parallel num_threads(4)
        {
            std::osyncstream(std::cout) << "nested " << omp_get_thread_num() << " " << std::this_thread::get_id() << "\n";
        };
    };
}

int main() {
    parallel_num_threads();
    parallel_if();
    parallel_sharing();
    parallel_nested();
}
