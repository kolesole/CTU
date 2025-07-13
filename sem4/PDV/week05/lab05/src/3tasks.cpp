#include <omp.h>
#include "../pdv_lib/pdv_lib.hpp"

// V posledni sade uloh se zamerime na vypocet Fibonacciho cisla pomoci rekurze a budete si moci vyzkouset
// `#pragma omp task` pro rekurzivni paralelizaci. V testech pocitame cislo FIB_QUERY, ktere si muzete
// upravit ve funkci `main`.


// sekvencni implementace; je tu jednak pro porovnani rychlosti, a druhak proto, ze i v paralelni
//  implementaci na ni prepneme, kdyz uz mame dost vytvorenych tasku, abychom saturovali vsechna jadra CPU
uint64_t fibonacci_seq(uint64_t n) {
    if (n <= 1) return n;
    return fibonacci_seq(n - 1) + fibonacci_seq(n - 2);
}

uint64_t fibonacci_worker(uint64_t n, int task_count) {
    if (n <= 1) return n;
    if (task_count == 1) return fibonacci_seq(n);

    uint64_t x, y;

    #pragma omp task shared(x)
    x = fibonacci_worker(n - 1, task_count / 2);

    y = fibonacci_worker(n - 2, task_count - task_count / 2);

    #pragma omp taskwait
    return x + y;


    // TODO: implementujte paralelni vypocet Fibonacciho cisla pomoci `#pragma omp task`
    // throw pdv::not_implemented{};
}

uint64_t fibonacci_par(uint64_t n) {
    uint64_t res;
    #pragma omp parallel
    #pragma omp single
    res = fibonacci_worker(n, omp_get_num_threads() * 8);
    return res;
}


int main() {
    constexpr uint64_t FIB_QUERY = 38;

    pdv::benchmark("fibonacci_seq", 10, [&] { return fibonacci_seq(pdv::launder_value(FIB_QUERY)); });
    pdv::benchmark("fibonacci_par", 10, [&] { return fibonacci_par(pdv::launder_value(FIB_QUERY)); });

    return 0;
}
