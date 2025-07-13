#include <execution>
#include "../pdv_lib/pdv_lib.hpp"

int main() {
    auto vec = pdv::generate_random_vector<float>(50'000'000);

    auto vec_seq = vec;
    pdv::benchmark("Vector std::exp (scalar)", 10, [&] {
        for (auto& n : vec_seq) {
            n = std::exp(n);
        }
    });

    auto vec_par = vec;
    pdv::benchmark("Vector std::exp (parallel)", 10, [&] {
        #pragma omp parallel for
        for (auto& n : vec_par) {
            n = std::exp(n);
        }
    });
}
