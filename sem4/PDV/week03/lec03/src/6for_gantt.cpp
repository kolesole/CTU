/// Pipe the output of this program to `python3 6render_gantt.py` to visualize the loop schedule with a Gantt diagram.
///
/// Try setting the schedule of the for loop to:
///  schedule(static), schedule(static, 1), schedule(static, 5),
///  schedule(dynamic), schedule(dynamic, 5),
///  schedule(guided)
///
/// Also try changing the sleep to `10ms` and `1ms * i`.

#include <omp.h>
#include <cstddef>
#include <iostream>
#include <syncstream>
#include <thread>

using namespace std::chrono_literals;
using Clock = std::chrono::system_clock;

int main() {
    auto time_base = Clock::now();

    #pragma omp parallel for
    for (size_t i = 0; i < 100; i++) {
        auto start_time = Clock::now();
        std::this_thread::sleep_for(1ms * i);
        std::osyncstream(std::cout) << i << " " << omp_get_thread_num() << " " << (start_time - time_base).count() << " " << (Clock::now() - time_base).count() << "\n";
    }
}
