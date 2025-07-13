#pragma once

#include <cstddef>
#include <vector>
#include <functional>
#include <atomic>

template<typename row_t>
using predicate_t = std::function<bool(const row_t&)>;


template<typename row_t>
bool is_satisfied_for_all(std::vector<predicate_t<row_t>> predicates, std::vector<row_t> data_table);

template<typename row_t>
bool is_satisfied_for_any(std::vector<predicate_t<row_t>> predicates, std::vector<row_t> data_table);


template<typename row_t>
bool is_satisfied_for_all(std::vector<predicate_t<row_t>> predicates, std::vector<row_t> data_table) {
    // Doimplementujte telo funkce, ktera rozhodne, zda pro VSECHNY dilci dotazy (obsazene ve
    // vektoru 'predicates') existuje alespon jeden zaznam v tabulce (reprezentovane vektorem
    // 'data_table'), pro ktery je dany predikat splneny.

    // Pro inspiraci si prostudujte kod, kterym muzete zjistit, zda prvni dilci dotaz plati,
    // tj., zda existuje alespon jeden radek v tabulce, pro ktery predikat reprezentovany
    // funkci predicates[i] plati:
    std::atomic<bool> ret(true);

    #pragma omp parallel for
    for (size_t i = 0; i < predicates.size(); i++) {
        auto& predicate = predicates[i];
        for (size_t j = 0; j < data_table.size(); j++) {
            if (!ret.load()) {
                break;
            }

            if (predicate(data_table[j])) {
                break;
            }

            if (j == data_table.size() - 1) {
                ret.store(false);
                break;
            }
        }

        if (!ret.load()) {
            #pragma omp cancel for
        }
    }

    return ret.load();
}

template<typename row_t>
bool is_satisfied_for_any(std::vector<predicate_t<row_t>> predicates, std::vector<row_t> data_table) {
    // Doimplementujte telo funkce, ktera rozhodne, zda je ALESPON JEDEN dilci dotaz pravdivy.
    // To znamena, ze mate zjistit, zda existuje alespon jeden predikat 'p' a jeden zaznam
    // v tabulce 'r' takovy, ze p(r) vraci true.

    // Zamyslete se nad tim, pro ktery druh dotazu je vhodny jaky druh paralelizace. Vas
    // kod optimalizujte na situaci, kdy si myslite, ze navratova hodnota funkce bude true.
    // Je pro Vas dulezitejsi rychle najit splnujici radek pro jeden vybrany predikat, nebo
    // je dulezitejsi zkouset najit takovy radek pro vice predikatu paralelne?
    std::atomic<bool> ret(false);

    for (size_t i = 0; i < predicates.size(); i++) {
        auto& predicate = predicates[i];
        #pragma omp parallel for
        for (size_t j = 0; j < data_table.size(); j++) {
            #pragma omp cancellation point for

            if (predicate(data_table[j])) {
                ret.store(true);
                #pragma omp cancel for
            }
        }

        if (ret.load()) {
            break;
        }
    }

    return ret.load();
}

