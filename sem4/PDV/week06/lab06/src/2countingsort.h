#pragma once

#include <vector>
#include <limits>
#include <cstdlib>
#include <chrono>
#include <omp.h>
#include "../pdv_lib/pdv_lib.hpp"
#include "3prefixsum.h"

template <typename elem_t>
void counting_sequential(std::vector<elem_t> & data) {
    elem_t min = std::numeric_limits<elem_t>::max();
    elem_t max = std::numeric_limits<elem_t>::min();

    for(auto && el : data) {
        if(el < min) min = el;
        if(el > max) max = el;
    }

    const size_t range = max - min + 1;
    std::vector<unsigned int> counts(range);

    for(auto && el : data) {
        ++counts[el-min];
    }

    unsigned int idx = 0;
    for(unsigned int i = 0 ; i < range ; i++) {
        unsigned int count = counts[i];
        unsigned int number = min + i;
        for(unsigned int k = 0 ; k < count ; k++) {
            data[idx++] = number;
        }
    }
}

template <typename elem_t>
void counting_parallel(std::vector<elem_t> & data) {
    elem_t min = std::numeric_limits<elem_t>::max();
    elem_t max = std::numeric_limits<elem_t>::min();

    unsigned int size = static_cast<unsigned>(data.size());
    unsigned int numThreads = omp_get_max_threads();

    #pragma omp parallel for reduction(max:max) reduction(min:min)
    for(unsigned i = 0; i < size; i++) {
        auto &el = data[i];
        if(el < min) min = el;
        if(el > max) max = el;
    }

    const size_t range = max - min + 1;

    std::vector<unsigned int> histogram;

    std::vector<std::vector<unsigned>> histogramPerThread(numThreads, std::vector<unsigned>(range));

    #pragma omp parallel
    {
        std::vector<unsigned int> &localHistogram = histogramPerThread[omp_get_thread_num()];
        #pragma omp for
        for(unsigned i = 0; i < size; i++)
            localHistogram[data[i] - min] ++;
    };

    #pragma omp parallel for
    for(unsigned i = 0; i < range; i++){
        for(unsigned j = 1; j < numThreads; j++){
            histogramPerThread[0][i] += histogramPerThread[j][i];
        }
    }

    histogram.swap(histogramPerThread[0]);

    prefix_sum_parallel(&histogram[0], range);

    #pragma omp parallel for
    for(unsigned int i = 0 ; i < range ; i++) {
        unsigned int begin  = i == 0 ? 0 : histogram[i-1];
        unsigned int end = histogram[i];
        unsigned int number = min + i;
        for(unsigned int k = begin ; k < end ; k++) {
            data[k] = number;
        }
    }
}
