#include <vector>
#include <algorithm>
#include <execution>

int main() {
    auto vec = std::vector<uint32_t>{3, 4, 1, 5, 2};

    // if you have MSVC installed, configure it as your toolchain and then follow Ctrl-B (Go to definition)
    //  to enter the standard library; otherwise, you can read the source on GitHub (see links below)

    // sequential sort
    // - algorithm:8484 (_Sort_unchecked)
    //   https://github.com/microsoft/STL/blob/f2a2933dd65d9e8d3fa698a97b6074f7ef00e1fd/stl/inc/algorithm#L8484
    //   the main serial sorting function in the STL – uses insertion sort for small arrays, heap sort for arrays where
    //   quicksort does not work well (side-heavy recursion tree due to suboptimal pivot choice), and quicksort
    //   by default; note that the larger subtree is processed iteratively instead of recursively to minimize chance of
    //   a stack overflow
    std::sort(vec.begin(), vec.end());

    // parallel sort
    // - execution:2652 (_Process_sort_work_item)
    //   https://github.com/microsoft/STL/blob/f2a2933dd65d9e8d3fa698a97b6074f7ef00e1fd/stl/inc/execution#L2652
    //   the actual sorting kernel, which processes 1 level of quicksort; this function is repeatedly invoked
    //   until the local task queue is empty; in libc++ (macOS/Clang C++ standard library), sorting networks are
    //   used for very small arrays, otherwise the algorithm is quite similar
    //
    // - execution:2743 (sort)
    //   https://github.com/microsoft/STL/blob/f2a2933dd65d9e8d3fa698a97b6074f7ef00e1fd/stl/inc/execution#L2743
    //   entry point to the parallel sorting algorithm (creates a thread pool and the first task ("work item" in
    //   STL terminology))
    //
    // - execution:2718 (_Threadpool_callback)
    //   https://github.com/microsoft/STL/blob/f2a2933dd65d9e8d3fa698a97b6074f7ef00e1fd/stl/inc/execution#L2718
    //   main function executed by each worker thread in the threadpool that is processing the tasks;
    //   only the main thread has work in the beginning so each of the worker threads start by trying to steal
    //   a task from the main thread
    //
    // - execution:571 (_Work_stealing_deque)
    //   https://github.com/microsoft/STL/blob/f2a2933dd65d9e8d3fa698a97b6074f7ef00e1fd/stl/inc/execution#L571
    //   implementation of a work-stealing stack (as discussed in the 5th lecture) where the local thread pushes
    //   tasks and pops them from the same side, while other threads steal tasks from the bottom of the stack
    std::sort(std::execution::par_unseq, vec.begin(), vec.end());
}
