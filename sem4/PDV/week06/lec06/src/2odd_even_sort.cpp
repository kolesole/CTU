#include <algorithm>
#include "../pdv_lib/pdv_lib.hpp"

template<typename T>
void minmax(T& v1, T& v2) {
    if (v1 > v2) {
        std::swap(v1, v2);
    }

    // alternative equivalent formulation (will soon become useful)
    //auto min = std::min(v1, v2);
    //auto max = std::max(v1, v2);
    //v1 = min;
    //v2 = max;
}

template<std::forward_iterator It>
void bubble_sort(It begin, It end) {
    // in each outer loop iteration, we correctly place at least 1 value (starting from the highest one)
    for (end--; end != begin; end--) {
        // go through all consecutive unsorted pairs, swap them if they're not in the correct order
        for (auto it = begin; it != end; ++it) {
            minmax(*it, *(it + 1));
        }
    }
}

template<std::forward_iterator It>
void odd_even_sort(It begin, It end) {
    end--;
    auto n = end - begin;

    #pragma omp parallel
    for (size_t i = 0; i < n; i++) {
        // first, swap (even, odd) pairs (phase 1)
        #pragma omp for
        for (auto it = begin; it < end; it += 2) {
            minmax(*it, *(it + 1));
        }

        // #pragma omp for has an implicit barrier at the end

        // now, swap (odd, even) pairs (phase 2)
        #pragma omp for
        for (auto it = begin + 1; it < end; it += 2) {
            minmax(*it, *(it + 1));
        }
    }
}

template <typename T>
using iter_fn = void (*)(typename std::vector<T>::iterator begin, typename std::vector<T>::iterator end);

template<typename T>
void test(std::string_view name, std::vector<T> data, iter_fn<T> test_fn) {
    pdv::benchmark(name, [&] {
        pdv::do_not_optimize_away(data);
        test_fn(data.begin(), data.end());
        pdv::do_not_optimize_away(data);
    });
    std::cout << "is_sorted: " << std::is_sorted(data.begin(), data.end()) << "\n";
}

int main() {
    auto data = pdv::generate_random_vector<uint32_t>(30'000);

    test("bubble_sort", data, &bubble_sort);
    test("odd_even_sort", data, &odd_even_sort);
}
