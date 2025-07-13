#include <iostream>
#include <atomic>
#include <thread>

int main() {
    std::atomic<uint32_t> shared_var = 0;

    // lambda function that is executed by both threads below
    auto thread_fn = [&] {
        for (size_t i = 0; i < 1'000'000; i++) {
            shared_var++;
        }
    };

    {
        // create 2 threads that execute `thread_fn`
        auto t1 = std::jthread(thread_fn);
        auto t2 = std::jthread(thread_fn);

        // wait for the threads to finish
    }

    // print the value of the variable
    std::cout << "shared_var = " << shared_var << "\n";
}
