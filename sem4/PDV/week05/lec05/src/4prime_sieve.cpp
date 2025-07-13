#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

std::vector<uint64_t> find_primes_under(uint64_t max_n) {
    // Eratosthenes sieve
    auto sieve = std::vector<bool>(max_n, true);
    for (size_t n = 2; n <= std::sqrt(max_n); n++) {
        if (sieve[n]) {
            for (size_t mult = n; mult < max_n; mult += n) {
                sieve[mult] = false;
            }
        }
    }

    auto found_primes = std::vector<uint64_t>();
    for (size_t n = 2; n < max_n; n++) {
        if (sieve[n]) {
            found_primes.push_back(n);
        }
    }
    return found_primes;
}

int main() {
    auto primes = find_primes_under(1'000);
    for (auto n : primes) {
        std::cout << n << " ";
    }
    std::cout << "\n";
}
