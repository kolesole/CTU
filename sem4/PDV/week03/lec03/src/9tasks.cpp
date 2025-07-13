#include <cstdint>
#include <iostream>
#include <omp.h>

uint64_t fibonacci(uint64_t n) {
    if (n <= 1) return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

uint64_t fibonacci_par(uint64_t n, size_t task_count) {
    if (n <= 1) return n;

    // if we created enough tasks already, switch to the sequential version
    //  to avoid overhead from needlessly spawning small tasks
    if (task_count <= 1) {
        return fibonacci(n);
    }

    uint64_t left;
    uint64_t right;

    // create a task for both branches of recursion
    // need to use `shared(left)`, because tasks use `firstprivate` by default for all variables
    #pragma omp task shared(left)
    left = fibonacci_par(n - 1, task_count / 2);

    // we could also skip the task here and run this branch in the current thread to avoid some overhead
    #pragma omp task shared(right)
    right = fibonacci_par(n - 2, task_count / 2);

    // now we wait for both tasks
    #pragma omp taskwait
    return left + right;
}

int main() {
    constexpr auto N = 45;

    // sequential version
    std::cout << "fibonacci(" << N << ") = " << fibonacci(N) << std::endl;

    // create a thread pool, so that we can assign tasks to it
    uint64_t result;
    #pragma omp parallel
    {
        // but only start the recursion in a single thread
        #pragma omp single
        result = fibonacci_par(N, omp_get_num_threads() * 8);
    }

    std::cout << "fibonacci_par(" << N << ") = " << result << "\n";
}
