#include <algorithm>
#include <iostream>
#include <omp.h>
#include <span>
#include "../pdv_lib/pdv_lib.hpp"

template<typename It>
auto partition(It begin, It end, It pivot_it) {
    // ensure pivot is at last position
    std::swap(*(end - 1), *pivot_it);

    auto pivot = *(end - 1);
    auto mid_it = std::partition(begin, end - 1, [&](auto n) { return n < pivot; });

    // move pivot to the correct position
    std::swap(*(end - 1), *mid_it);
    return mid_it;
}

template<typename It>
void quicksort_seq(It begin, It end) {
    if (end - begin <= 1) {
        return;
    }

    // use first value as pivot
    auto pivot_it = partition(begin, end, begin);
    quicksort_seq(begin, pivot_it);
    quicksort_seq(pivot_it + 1, end);
}

template<typename It>
void quicksort(It begin, It end, size_t task_count) {
    if (end - begin <= 1) {
        return;
    }

    if (task_count == 1) {
        quicksort_seq(begin, end);
        return;
    }

    // use first value as pivot
    auto pivot_it = partition(begin, end, begin);

    #pragma omp task default(none) firstprivate(begin, pivot_it, task_count)
    quicksort(begin, pivot_it, task_count / 2);
    // run this branch in the current task
    quicksort(pivot_it + 1, end, task_count / 2);
}

template <typename T>
void test(std::string_view name, std::vector<T> data, auto test_fn) {
    pdv::benchmark(name, [&] {
        pdv::do_not_optimize_away(data);
        test_fn(data);
        pdv::do_not_optimize_away(data);
    });
    std::cout << "is_sorted: " << std::is_sorted(data.begin(), data.end()) << "\n";
}

int main() {
    auto data = pdv::generate_random_vector<float>(10'000'000);

    test("quicksort_seq", data, [](auto& data) {
        quicksort_seq(data.begin(), data.end());
    });

    test("quicksort", data, [](auto& data) {
        #pragma omp parallel default(none) shared(data)
        #pragma omp single
        quicksort(data.begin(), data.end(), omp_get_num_threads() * 8);
    });
}
