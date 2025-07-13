#include <thread>
#include <iostream>

using namespace std::chrono_literals;

void thread_fn() {
    std::cerr << "sleeping\n";
    std::this_thread::sleep_for(2s);
    std::cerr << "done\n";
}

int main() {
    auto t1 = std::jthread(thread_fn);
    auto t2 = std::jthread(thread_fn);
}
