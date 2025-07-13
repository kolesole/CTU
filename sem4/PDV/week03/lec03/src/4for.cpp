#include <cstddef>
#include <iostream>
#include <syncstream>
#include <omp.h>

int main() {
    #pragma omp parallel for
    for (size_t i = 0; i < 100; i++) {
        std::osyncstream(std::cout) << "Thread " << omp_get_thread_num() << " processing iteration #" << i << "\n";
    }
}
