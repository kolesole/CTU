#include <cstddef>
#include <iostream>
#include <omp.h>
#include <syncstream>

int main() {
    // split iterations of BOTH loops between threads thanks to the `collapse` clause
    #pragma omp parallel for collapse(2)
    for (size_t i = 0; i < 4; i++) {
        for (size_t j = 0; j < 4; j++) {
            std::osyncstream(std::cout) << "Iteration " << i << "," << j << " done by thread " << omp_get_thread_num() << "\n";
        }
    }
}
