#pragma once

#include <cstdlib>
#include <chrono>
#include <iostream>
#include <omp.h>
#include <vector>
#include <cmath>
#include "../pdv_lib/pdv_lib.hpp"

template<typename T>
void prefix_sum_sequential(T* data, const size_t size) {
    for (size_t i = 1; i < size; i++) {
        data[i] += data[i - 1];
    }
}

template<typename T>
void prefix_sum_parallel(T* data, const size_t size) {
    std::vector<T> sums(omp_get_max_threads());

    #pragma omp parallel
    {
        auto thread_num = omp_get_thread_num();
        auto begin = thread_num * (1 + size) / omp_get_num_threads();
        auto end = (thread_num + 1) * (1 + size) / omp_get_num_threads();

        end = end > size ? size : end;

        for (size_t i = begin; i < end; i++) {
            sums[thread_num] += data[i];
        }

        #pragma omp barrier

        auto pre_sum = 0;
        for (size_t i = 0; i < thread_num; i++) {
            pre_sum += sums[i];
        }

        data[begin] += pre_sum;

        for (auto i = begin + 1; i < end; i++) {
            data[i] += data[i - 1];
        }
        // Rozdelte vypocet prefixni sumy pole mezi jednotliva vlakna
        // Zamyslete se, jak byste se mohli "vyhnout" zavislosti sumy
        // na prefixni sume predchazejicich prvku. (Teto zavislosti se
        // nelze vyhnout - ale mozna by nam stacilo "vysbirat" vysledky
        // ostatnich vlaken a nemuseli bychom prochazet cele pole?)
    }
    // throw pdv::not_implemented();
}


