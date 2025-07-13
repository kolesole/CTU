#pragma once

#include <chrono>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <optional>
#include <atomic>
#include <utility>
#include <cassert>
#include <vector>
#include <algorithm>
#include <numeric>
#include "benchmark/result.hpp"
#include "benchmark/core.hpp"
#include "benchmark/presentation.hpp"
#include "util.hpp"


#ifndef NDEBUG
#include <iostream>
// write a warning message when compiling in debug mode
PDV_STATIC_INIT(debug_mode_check, {
    std::cerr << "\033[33m"
                 "WARNING: Running in DEBUG mode. If you're benchmarking your code, you should use RELEASE mode.\n"
                 "\033[0m";
})
#endif


namespace pdv {
    /**
     * An exception class, which is thrown from tests that are supposed to be implemented
     * by students. `pdv::benchmark` handles this exception and shows an appropriate message.
     *
     * MK: It would be nice if this would work correctly from inside OpenMP `parallel` blocks,
     * where we shouldn't throw exceptions, e.g. by setting a flag and then somehow stopping
     * the loop, but I couldn't figure out any nice way of implementing that.
     */
    class not_implemented : public std::runtime_error {
    public:
        not_implemented() : runtime_error("Not yet implemented") {}
    };

    template<typename BenchmarkFn>
    inline void benchmark(std::string_view description, const benchmark_options& options, BenchmarkFn fn) {
        // keep the length of the longest benchmark name
        if (_::benchmark_name_width < description.size()) {
            _::benchmark_name_width = description.size();
        }

        std::cout << std::setw((int)_::benchmark_name_width) << description << ": " << std::flush;
        try {
            // run the benchmark
            auto benchmark_result = benchmark_raw(options, fn);
            // print the results
            _::print_benchmark_result(benchmark_result);
        } catch (const pdv::not_implemented&) {
            std::cout << "--- not implemented ---";
        }

        std::cout << '\n';

        // I would like to return either the `fn` return value or the whole result struct, but we would need to figure
        //  out what to return when `pdv::not_implemented` is thrown
    }

    template<typename BenchmarkFn>
    inline void benchmark(std::string_view description, size_t warmup_iteration_count,
                          size_t iteration_count, BenchmarkFn fn) {
        benchmark(description, benchmark_options{iteration_count, warmup_iteration_count}, fn);
    }

    template<typename BenchmarkFn>
    inline void benchmark(std::string_view description, size_t iteration_count, BenchmarkFn fn) {
        benchmark(description, benchmark_options{iteration_count}, fn);
    }

    template<typename BenchmarkFn>
    inline void benchmark(std::string_view description, BenchmarkFn fn) {
        benchmark(description, benchmark_options{}, fn);
    }
}
