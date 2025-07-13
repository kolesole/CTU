/// Using a reader-writer lock to protect a data structure from corruption. All containers in the standard library
/// are safe for concurrent reads, but not for concurrent writes, according to the C++ standard.

#include <shared_mutex>
#include <unordered_set>
#include <mutex>
#include <syncstream>
#include <omp.h>
#include <thread>
#include "../pdv_lib/pdv_lib.hpp"

using namespace std::chrono_literals;

int main() {
    auto already_processed = std::unordered_set<uint32_t>();
    auto already_processed_mutex = std::shared_mutex();

    auto values_to_print = pdv::generate_random_vector<uint32_t>(1'000'000, 0, 20);

    #pragma omp parallel for
    for (auto n : values_to_print) {
        // first, we lock the set in reader mode and check if `n` is already contained (the common case)
        {
            auto lock = std::shared_lock(already_processed_mutex);
            if (already_processed.contains(n)) {
                continue;
            }
        }

        // it was not contained, re-lock the set in writer mode and insert it
        {
            auto lock = std::unique_lock(already_processed_mutex);
            // note that .insert() verifies that n is not already added
            already_processed.insert(n);
        }

        std::osyncstream(std::cerr) << "found new m_value: " << n << " (thread #" << omp_get_thread_num() << ")\n";
        std::this_thread::sleep_for(10ms);
    }
}
