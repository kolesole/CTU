#pragma once

#include <cstdlib>
#include <cstring>
#include <memory>
#include <omp.h>
#include <vector>
#include "../pdv_lib/pdv_lib.hpp"

// Metoda pro sliti dvou serazenych poli [a .. b-1] a [b .. end-1].
template<typename elem_t>
void merge(elem_t* a, elem_t* b, elem_t* end, elem_t* tmp) {
    elem_t* orig_a = a;
    elem_t* orig_b = b;
    elem_t* orig_tmp = tmp;

    // Nejprve hodnoty z poli 'a' a 'b' vypisujeme do pomocneho pole
    // 'tmp'.
    while (a < orig_b && b < end) {
        if (*a < *b) *tmp++ = *a++;
        else *tmp++ = *b++;
    }
    while (a < orig_b) *tmp++ = *a++;
    while (b < end) *tmp++ = *b++;

    // Pote, co vsechny prvky vypiseme do pole 'tmp', prekopirujeme
    // je zpet na puvodni misto - tj. do pole [a .. end-1]. Vysledne
    // pole [a .. end-1] je serazene.
    memcpy(orig_a, orig_tmp, (tmp - orig_tmp) * sizeof(elem_t));
}

template<typename elem_t>
void mergesort_sequential_worker(elem_t* data, unsigned long size, elem_t* tmp) {
    // Pole velikosti mensi nez 1 je serazene
    if (size <= 1) {
        return;
    }

    size_t h_size = size / 2;

    // Nejprve si pole rozdelime na dve casti [a .. b-1] a [b .. end-1]
    elem_t* a = data;             // Pointer na zacatek segmentu
    elem_t* b = data + h_size;    // Pointer doprostred segmentu (konec leve poloviny)
    elem_t* end = data + size;    // Konec segmentu (konec prave poloviny)

    // Stejnym zpusobem si rozdelime i pomocne pole
    elem_t* tmp_a = tmp;
    elem_t* tmp_b = tmp + h_size;

    // Zavolame rekurzivni volani na levou a pravou polovinu
    mergesort_sequential_worker(a, static_cast<unsigned long>(h_size), tmp_a);

    mergesort_sequential_worker(b, static_cast<unsigned long>(size - h_size), tmp_b);

    // A vysledky nakonec slijeme pomoci operace merge
    merge(a, b, end, tmp);
}

template<typename elem_t>
void mergesort_sequential(std::vector<elem_t>& data) {
    const size_t size = data.size();

    // Vytvorime si pomocne pole, do ktereho budeme provadet operaci 'merge'
    std::vector<elem_t> tmp(size);

    // Zavolame rekurzivni funkci mergesortu
    mergesort_sequential_worker(&data[0], static_cast<unsigned long>(size), &tmp[0]);
}

template<typename elem_t>
void mergesort_parallel_worker(elem_t* data, unsigned long size, elem_t* tmp, int CUTOFF) {
    // Pole velikosti mensi nez 1 je serazene
    if (size <= 1000000) {
        return mergesort_sequential_worker(&data[0], static_cast<unsigned long>(size), &tmp[0]);
    }

    size_t h_size = size / 2;

    // Nejprve si pole rozdelime na dve casti [a .. b-1] a [b .. end-1]omp_get_num_threads() * 8
    elem_t* a = data;             // Pointer na zacatek segmentu
    elem_t* b = data + h_size;    // Pointer doprostred segmentu (konec leve poloviny)
    elem_t* end = data + size;    // Konec segmentu (konec prave poloviny)

    // Stejnym zpusobem si rozdelime i pomocne pole
    elem_t* tmp_a = tmp;
    elem_t* tmp_b = tmp + h_size;

    // Zavolame rekurzivni volani na levou a pravou polovinu
    #pragma omp task
    mergesort_parallel_worker(a, static_cast<unsigned long>(h_size), tmp_a, CUTOFF);

    // #pragma omp task
    mergesort_parallel_worker(b, static_cast<unsigned long>(size - h_size), tmp_b, CUTOFF);

    // A vysledky nakonec slijeme pomoci operace merge
    #pragma omp taskwait
    merge(a, b, end, tmp);
}

template<typename elem_t>
void mergesort_parallel(std::vector<elem_t>& data) {
    const size_t size = data.size();
    std::vector<elem_t> tmp(size);

    #pragma omp parallel
    #pragma omp single
    mergesort_parallel_worker(&data[0], static_cast<unsigned long>(size), &tmp[0], omp_get_num_threads() * 4);

    // Doimplementujte paralelni verzi algoritmu mergesort za pouziti `task` v OpenMP. Muzete se inspirovat sekvencni
    // verzi algoritmu a muzete take pouzit sekvencni funkci `merge` pro sliti dvou serazenych poli do jednoho.
    // throw pdv::not_implemented();
}
