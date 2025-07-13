#include "../pdv_lib/pdv_lib.hpp"
#include <thread>
#include <array>

constexpr size_t NTHREADS = 8;

// Tuto funkci vykonava `NTHREADS` vlaken soucasne. Kazde vlakno zapisuje pouze do pametove bunky
// odkazovane pomoci ukazatele `x`.
void inc(volatile int32_t* x) {
    for (size_t i = 0L; i < 1'000'000'000; ++i) {
        if (i & 1) *x = *x + 1;
        else *x = (*x) * (*x);
    }
}

// `Step` musime predat jako template argument (v compile time), abychom ho mohli pouzit
// pro nastaveni velikosti `threads` a `data`.
template<size_t Step>
void run_test() {
    // array na jednotlive objekty reprezentujici bezici vlakna
    std::array<std::thread, NTHREADS> threads;
    // array, do ktere vlakna za behu opakovane zapisuji; pomoci `Step` lze menit vzdalenost
    //  mezi misty, kam jednotliva vlakna zapisuji
    std::array<int32_t, NTHREADS * Step> data{};

    pdv::benchmark("False sharing (STEP=" + std::to_string(Step) + ")", [&] {
        for (size_t i = 0; i < threads.size(); i++) {
            // Nyni spustime vlakna. Kazde vlakno bude cist a zapisovat do promenne na pozici
            // `i * Step` v poli data. Pokud zvolime hodnotu `Step=1`, promenne se nachazi ve stejne
            // cache line (a proto hrozi, ze dojde k false-sharingu, protoze vic jader bude mit
            // stejnou cache line ve sve privatni cache). Pokud hodnotu navysime, napriklad na
            // `Step=16`, vzdalenost mezi dvemi sousednimi promennymi bude `16 * sizeof(int32_t)`.
            // Pokud je velikost cache line 64 bytu, promenne se nikdy nebudou nachazet ve stejne
            // cache line, a k false-sharingu tak nedojde.
            threads[i] = std::thread(inc, &data[i * Step]);
        }

        // Na zaver pockame na dokonceni vsech vlaken.
        for (auto& t : threads) {
            t.join();
        }
    });
}

int main() {
    // pomale, casto dochazi k false sharingu
    run_test<1>();
    // rychle, k false sharingu nedochazi vubec
    run_test<16>();

    return 0;
}
