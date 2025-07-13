#include <omp.h>
#include "../pdv_lib/pdv_lib.hpp"

size_t find_value(std::vector<uint32_t> data, uint32_t value) {
    size_t found_i = 0;
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] == value) {
            found_i = i;
            break;
        }
    }
    return found_i;
}

size_t find_value_par(std::vector<uint32_t> data, uint32_t value) {
    std::atomic<size_t> found_i = 0;
    #pragma omp parallel for
    for (size_t i = 0; i < data.size(); i++) {
        if (data[i] == value) {
            found_i.store(i);
            #pragma omp cancel for
        }
    }
    return found_i.load();
}


int main() {
    if (!omp_get_cancellation()) {
        std::cerr << "Cancellations not enabled, set OMP_CANCELLATION=true!\n";
        return 1;
    }

    auto vec = pdv::generate_random_vector<uint32_t>(1'000'000'000);
    auto query = vec[900'000'000];

    pdv::benchmark("find_value", [&] { return find_value(vec, query); });
    pdv::benchmark("find_value_par", [&] { return find_value_par(vec, query); });
}
