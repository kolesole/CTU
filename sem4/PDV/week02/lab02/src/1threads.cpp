#include "1threads.h"
#include "../pdv_lib/pdv_lib.hpp"
#include <cstddef>
#include <algorithm>
#include <execution>
#include <thread>
#include <mutex>
#include <atomic>

const size_t THREAD_COUNT = std::thread::hardware_concurrency();

void map_sequential(std::vector<float>& data, MapFn map_fn) {
    for (float& f : data) {
        f = map_fn(f);
    }
    // C ekvivalent:
    //for (size_t i = 0; i < data.size(); i++) {
    //    data[i] = map_fn(data[i]);
    //}
}

void map_std_seq(std::vector<float>& data, MapFn map_fn) {
    std::transform(data.begin(), data.end(), data.begin(), map_fn);
}

void map_std_par([[maybe_unused]] std::vector<float>& data, [[maybe_unused]] MapFn map_fn) {
    // zakomentovano, protoze na Linuxu vyzaduje pouziti paralelni exekuce extra knihovnu
    // std::transform(std::execution::par_unseq, data.begin(), data.end(), data.begin(), map_fn);
}

void map_openmp(std::vector<float>& data, MapFn map_fn) {
    #pragma omp parallel for
    for (float& f : data) {
        f = map_fn(f);
    }
}


/** Naivni implementace paralelizace se sdilenym indexem. */
void map_manual(std::vector<float>& data, MapFn map_fn) {
    size_t i = 0;
    auto process = [&] {
        while (i < data.size()) {
            // kazde vlakno si ve smycce vezme a incrementuje dalsi index ke zpracovani...
            auto& entry = data[i++];
            // ...a prvek zpracuje
            entry = map_fn(entry);
        }
    };

    auto worker_threads = std::vector<std::jthread>();
    for (size_t j = 0; j < THREAD_COUNT; j++) {
        worker_threads.push_back(std::jthread(process));
    }
}

void map_manual_locking(std::vector<float>& data, MapFn map_fn) {
    size_t i = 0;
    std::mutex m;
    auto process = [&] {
        while (i < data.size()) {
            // kazde vlakno si ve smycce vezme a incrementuje dalsi index ke zpracovani...
            size_t loc_i = 0;
            {
                auto lock = std::unique_lock(m);
                loc_i = i++;
            }
                if (loc_i >= data.size()) break;

                auto& entry = data[loc_i];
                // ...a prvek zpracuje
                entry = map_fn(entry);
        }
    };

    auto worker_threads = std::vector<std::jthread>();
    for (size_t j = 0; j < THREAD_COUNT; j++) {
        worker_threads.push_back(std::jthread(process));
    }
    // TODO: opravte race condition v `map_manual` pomoci mutexu
    // throw pdv::not_implemented();
}

void map_manual_atomic(std::vector<float>& data, MapFn map_fn) {
    std::atomic<size_t> i = 0;
    auto process = [&] {
        while (i < data.size()) {
            // kazde vlakno si ve smycce vezme a incrementuje dalsi index ke zpracovani...
            size_t loc_i = i++;

            if (loc_i >= data.size()) break;

            auto& entry = data[loc_i];
            // ...a prvek zpracuje
            entry = map_fn(entry);
        }
    };

    auto worker_threads = std::vector<std::jthread>();
    for (size_t j = 0; j < THREAD_COUNT; j++) {
        worker_threads.push_back(std::jthread(process));
    }
    // TODO: opravte race condition v `map_manual` pomoci atomicke promenne
    // throw pdv::not_implemented();
}

void map_manual_ranges(std::vector<float>& data, MapFn map_fn) {
    // std::size_t i = 0;
    size_t block_size = data.size() / THREAD_COUNT + 1;
    auto process = [&](int thread_indx) {
        int j = thread_indx;
        while (j < data.size() && j < thread_indx + block_size) {
            // kazde vlakno si ve smycce vezme a incrementuje dalsi index ke zpracovani...
            auto& entry = data[j++];
            // ...a prvek zpracuje
            entry = map_fn(entry);
        }
    };

    auto worker_threads = std::vector<std::jthread>();
    for (size_t j = 0; j < THREAD_COUNT; j++) {
        worker_threads.push_back(std::jthread(process, j * block_size));
    }
    // TODO: opravte race condition v `map_manual` tim, ze kazdemu vlaknu predpocitate rozsah indexu, ktere ma zpracovat
    // throw pdv::not_implemented();
}
