#include "sort.h"

#include <stdexcept>
#include <omp.h>

void radix_seq(std::vector<std::string*>& vector_to_sort, MappingFunction mapping_function,
                      size_t alphabet_size, size_t str_size) {
    size_t len = vector_to_sort.size();

    for (size_t i = str_size; i-- > 0;) {
        std::vector<std::size_t> counters(alphabet_size, 0);

        for (auto str : vector_to_sort) {
            counters[mapping_function((*str)[i])]++;
        }

        for (size_t j = 1; j < alphabet_size; j++) {
            counters[j] += counters[j - 1];
        }

        std::vector<std::string*> new_vector_to_sort(len);
        for (size_t j = len; j-- > 0;) {
            auto cur_str = vector_to_sort[j];
            new_vector_to_sort[--counters[mapping_function((*cur_str)[i])]] = cur_str;
        }

        vector_to_sort = std::move(new_vector_to_sort);
    }
}

// implementace vaseho radiciho algoritmu. Detalnejsi popis zadani najdete v "sort.h"
void radix_par(std::vector<std::string*>& vector_to_sort, MappingFunction mapping_function,
               size_t alphabet_size, size_t str_size) {
    size_t len = vector_to_sort.size();
    size_t num_threads = omp_get_max_threads();

    for (size_t i = str_size; i-- > 0;) {
        std::vector<std::vector<long long>> threads_counters(num_threads, std::vector<long long>(alphabet_size, 0));
        std::vector<std::string*> new_vector_to_sort(len);

        #pragma omp parallel
        {
            auto thread_num = omp_get_thread_num();
            auto begin = thread_num * (len + 1) / num_threads;
            auto end = (thread_num + 1) * (len + 1) / num_threads;

            end = end > len ? len : end;

            for (auto j = begin; j < end; j++) {
                threads_counters[thread_num][mapping_function((*vector_to_sort[j])[i])]++;
                new_vector_to_sort[j] = vector_to_sort[j];
            }

            #pragma omp barrier

            #pragma omp single
            {
                for (size_t j = 1; j < num_threads; j++) {
                    threads_counters[j][0] += threads_counters[j - 1][0];
                }

                for (size_t j = 1; j < alphabet_size; j++) {
                    for (size_t k = 0; k < num_threads; k++) {
                        if (k == 0) {
                            threads_counters[k][j] += threads_counters[num_threads - 1][j - 1];
                        } else {
                            threads_counters[k][j] += threads_counters[k - 1][j];
                        }
                    }
                }
            }

            #pragma omp barrier

            for (size_t j = end; j-- > begin;) {
                auto cur_str = new_vector_to_sort[j];

                vector_to_sort[--threads_counters[thread_num][mapping_function((*cur_str)[i])]] = cur_str;
            }
        }
    }
}
