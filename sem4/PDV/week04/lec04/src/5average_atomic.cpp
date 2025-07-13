/// Example of a class that atomically tracks the average of passed numbers.
/// Illustrates how to update multiple values atomically by packing them into a single uint64_t.

#include <cstdint>
#include <atomic>
#include <iostream>

class average_counter {
private:
    std::atomic<uint64_t> counter = 0;

public:
    void add(uint32_t value) {
        // pack both sum and count into a single atomic variable, so that they're in sync
        counter += 1ull << 32 | (uint64_t) value;
    }

    uint32_t average() {
        // read the value once
        auto counter_value = counter.load();

        // we know that the sum and count will be in sync
        auto sum = uint32_t(counter_value & 0xffffffff);
        auto count = uint32_t(counter_value >> 32);

        return sum / count;
    }
};


int main() {
    average_counter counter{};

    #pragma omp parallel for
    for (size_t i = 0; i < 1'000; i++) {
        counter.add(i);
    }

    std::cout << "average: " << counter.average() << "\n";
}
