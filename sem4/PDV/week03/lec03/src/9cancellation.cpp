#include "../pdv_lib/pdv_lib.hpp"

int main() {
    auto vec = pdv::generate_random_vector<uint32_t>(1'000'000'000);
    auto query = vec[250'000];

    //#pragma omp parallel for
    for (size_t i = 0; i < vec.size(); i++) {
        if (vec[i] == query) {
            std::cout << "found at " << i << "\n";
            //#pragma omp cancel for
            break;
        }
    }
}
