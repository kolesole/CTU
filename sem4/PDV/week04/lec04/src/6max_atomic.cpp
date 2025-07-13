/// Find the maximum value in a vector using CAS (compare-and-swap).
/// This would be more efficient using omp reduction (but wouldn't showcase atomics :) ).

#include "../pdv_lib/pdv_lib.hpp"

int main() {
    auto values = pdv::generate_random_vector<uint32_t>(1'000'000, 0, 1'000);
    std::atomic<uint32_t> max = 0;

    #pragma omp parallel for
    for (auto n : values) {
        auto current_max = max.load();
        while (n > current_max) {
            // new maximum, update max
            if (max.compare_exchange_weak(current_max, n)) break;
            // update failed, `current_max` was updated with the up-to-date value, retry
        }
    }

    std::cout << "max: " << max << "\n";
}
