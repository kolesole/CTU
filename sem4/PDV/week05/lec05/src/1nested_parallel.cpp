#include <iostream>
#include <syncstream>
#include <omp.h>
#include <thread>

int main() {
    // enable/disable nested parallelism
    omp_set_nested(true);

    #pragma omp parallel num_threads(2)
    {
        std::cout << "before nesting\n";

        #pragma omp parallel num_threads(4)
        {
            std::osyncstream(std::cout) << "nested " << omp_get_thread_num() << " " << std::this_thread::get_id() << "\n";
        };
    };
}
