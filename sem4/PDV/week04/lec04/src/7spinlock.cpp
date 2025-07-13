/// A naive mutex implementation using a spinlock.
/// For a less naive version, see https://rigtorp.se/spinlock/.

#include <atomic>
#include <mutex>
#include <iostream>

class spinlock {
private:
    std::atomic<bool> flag = false;

public:
    void lock() {
        while (true) {
            // try to lock the mutex using a CAS (compare-and-swap) operation
            auto expected = false;
            if (flag.compare_exchange_weak(expected, true)) {
                break;
            }

            // wait in read-only mode until the mutex is unlocked
            // this may be more efficient when multiple threads are waiting by reducing cache invalidation traffic
            while (flag.load()) {}
        }
    }

    void unlock() {
        // unlock the mutex by setting the flag back to false
        flag.store(false);
    }
};


int main() {
    spinlock m{};
    #pragma omp parallel
    {
        // note that here, it is not enough that atomics give us atomic operations, but we also need them to prevent
        //  reordering the content of the critical section outside the range where the mutex is help
        // keyword to learn more: acquire-release semantics
        auto lock = std::unique_lock(m);
        std::cout << "hello ";
        std::cout << "world ";
        std::cout << "from ";
        std::cout << "a ";
        std::cout << "thread\n";
    };
}
