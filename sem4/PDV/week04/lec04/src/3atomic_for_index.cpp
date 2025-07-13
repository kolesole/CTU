/// Example of using an atomic variable to implement a dynamically-scheduled for loop parallelization
/// (you already know this example from the labs).

#include <atomic>
#include <thread>
#include "../pdv_lib/pdv_lib.hpp"

void map_in_place(auto data, auto map_fn) {
    std::atomic<size_t> i = 0;
    #pragma omp parallel
    {
        while (true) {
            auto i_local = i++;
            if (i_local >= data.size()) {
                break;
            }
            auto& item = data[i_local];

            item = map_fn(item);
        }
    }
}

int main() {
    auto data = pdv::generate_random_vector<float>(1'000'000);

    map_in_place(data, [](auto n) {
        return std::exp(n);
    });

    std::cout << "sum: " << std::reduce(data.begin(), data.end()) << "\n";
}
