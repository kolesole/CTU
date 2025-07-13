#include <thread>
#include <vector>
#include <iostream>

void thread_fn() {
    std::cout << "hello from a few parallel threads:";
    for (size_t i = 0; i < 10; i++) {
        std::cout << " " << i;
    }
    std::cout << "\n";
}

int main() {
    auto threads = std::vector<std::jthread>();

    for (size_t i = 0; i < 8; i++) {
        threads.push_back(std::jthread(thread_fn));
    }
}
