/// Use an atomic variable as an instrumentation counter in a larger multithreaded application to log
/// how many times an event occurred.

#include <atomic>
#include <cstdint>
#include <iostream>

class Counter {
private:
    std::atomic<uint64_t> counter = 0;

public:
    uint64_t event_count() {
        return counter.load();
    }

    void log_event() {
        counter++;
    }
};

auto requests_made = Counter();

void handle_request() {
    requests_made.log_event();
    // ...1
}

int main() {
    #pragma omp parallel
    {
        handle_request();
        handle_request();
        handle_request();
    }

    std::cout << "Handled " << requests_made.event_count() << " requests.\n";
}
