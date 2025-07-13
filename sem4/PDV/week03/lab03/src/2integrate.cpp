#include "2integrate.hpp"
#include "../pdv_lib/pdv_lib.hpp"
#include <omp.h>
#include <algorithm>


// Nasledujici funkce odhaduji urcity integral funkce 'integrand'. Dolni mez integralu odpovida promenne
// 'a', horni mez pak ziskame jako a + step_size*step_count. Integral odhadujeme pomoci obdelnikove metody
// za pouziti 'step_count' stejne sirokych obdelniku.


double integrate_sequential(Integrand integrand, double a, double step_size, size_t step_count) {
    // Vypocet urciteho integralu se da chapat jako vypocet plochy pod krivkou funkce. Tuto plochu nebudeme
    // pocitat exaktne, ale odhadneme ji pomoci mnoziny obdelniku (a jejich obsahu). Kazdy z techto obdelniku
    // ma svuj levy okraj na pozici a + step_size*i a pravy okraj na pozici a + step_size*(i+1). Pro vypocet
    // vysky obdelniku existuje mnoho pristupu. My budeme uvazovat ten nejsnazsi a to sice pouzijeme hodnotu
    // integrovane funkce "uprostred" intervalu (tedy na pozici a + step_size*i + step_size/2 ).

    // Obsahy obdelniku scitame do promenne 'acc'
    double acc = 0.0;

    for (size_t i = 0; i < step_count; i++) {
        // Nyni prochazime jednotlive obdelniky a pricitame jejich obsah do promenne 'acc'.
        // Nejprve si vypocteme "prostredek" intervalu [a + step_size*i, a + step_size*(i+1):
        double cx = a + (double)(2 * i + 1) * step_size / 2.0;

        // Nyni pricteme obsah obdelniku. Jeho sirka odpovida promenne 'step_size'. Vysku odhadneme
        // hodnotou funkce uprostred intervalu (tj., hodnotou integrand(cx)).
        acc += integrand(cx) * step_size;
    }

    // Nakonec nascitany obsah vratime jako odhad urciteho integralu
    return acc;
}

double integrate_omp_critical(Integrand integrand, double a, double step_size, size_t step_count) {
    // Nyni vypocet integralu z funkce 'integrate_sequential' zparalelizujeme za pouziti direktiv OpenMP
    // #pragma omp parallel (slouzi ke spusteni tymu vlaken) a #pragma omp critical (ktera slouzi k vytvoreni
    // kriticke sekce, kterou v jeden cas muze vykonavat pouze jedno vlakno).
    // Obsahy obdelniku opet budeme scitat do promenne 'acc'.

    double acc = 0.0;

    #pragma omp parallel
    {
        int num_of_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        size_t size = 1 + step_count / num_of_threads;
        size_t begin = size * thread_id;
        size_t end = std::min(size * (thread_id + 1), step_count);

        for (size_t i = begin; i < end; i++) {
            double cx = a + (double)(2 * i + 1) * step_size / 2.0;

            #pragma omp critical
            acc += integrand(cx) * step_size;
        }
    }

    return acc;
    // TODO: Rozdelte celkovy interval na podintervaly prislusici jednotlivym vlaknum.
    //  Identifikujte kritickou sekci, kde musi dojit k zajisteni konzistence mezi vlakny.
    // throw pdv::not_implemented();
}

double
integrate_omp_atomic(Integrand integrand, double a, double step_size, size_t step_count) {
    // Vstup do kriticke sekce je velmi drahy. V mnoha pripadech (zejmena kdyz dochazi ke kolizim) je
    // potreba asistence jadra operacniho systemu, cemuz bychom se radi vyhnuli. Pro jednoduche operace
    // nad jednou promennou si ale muzeme vystacit s jednodussim typem zamku - atomickou operaci. Tento
    // zamek za nas vyresi procesor na hardwarove urovni a je ve vetsine pripadu rychlejsi.

    double acc = 0.0;

    #pragma omp parallel
    {
        int num_of_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        size_t size = 1 + step_count / num_of_threads;
        size_t begin = size * thread_id;
        size_t end = std::min(size * (thread_id + 1), step_count);

        for (size_t i = begin; i < end; i++) {
            double cx = a + (double)(2 * i + 1) * step_size / 2.0;
            double res = integrand(cx) * step_size;

            #pragma omp atomic
            acc += res;
        }
    }

    return acc;

    // TODO: Nahradte kritickou sekci pouzitim atomicke operace.
    // throw pdv::not_implemented();
}

double integrate_omp_reduction(Integrand integrand, double a, double step_size, size_t step_count) {
    double acc = 0.0;

    #pragma omp parallel reduction(+:acc)
    {
        int num_of_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();

        size_t size = 1 + step_count / num_of_threads;
        size_t begin = size * thread_id;
        size_t end = std::min(size * (thread_id + 1), step_count);


        for (size_t i = begin; i < end; i++) {
            double cx = a + (double)(2 * i + 1) * step_size / 2.0;
            double res = integrand(cx) * step_size;
            acc += res;
        }
    }

    return acc;
    // TODO: Nahradte atomickou operaci direktivou `reduction(...)`.
    //  Rozmyslete si, co zpusobuje vyrazny rozdil v rychlosti behu oproti predchozim verzim.
    // throw pdv::not_implemented();
}

double integrate_omp_for_static(Integrand integrand, double a, double step_size, size_t step_count) {
    // To, co jsme naimplementovali ve funkci 'integrate_omp_reduction', lze udelat v OpenMP jednoduseji.
    // Misto toho, abychom si rozsahy [begin, end) pro jednotliva vlakna pocitali rucne, muzeme rict OpenMP,
    // at je napocita za nas. Jedine, co k tomu potrebujeme je pouzit direktivu `#pragma omp for` pred for
    // smyckou, kterou chceme paralelizovat.

    double acc = 0.0;

    #pragma omp parallel for reduction(+:acc) // schedule(static)
    for (size_t i = 0; i < step_count; i++) {
        double cx = a + (double)(2 * i + 1) * step_size / 2.0;
        double res = integrand(cx) * step_size;
        acc += res;
    }

    return acc;
    // TODO: Zjednoduste `integrate_omp_reduction` pomoci `#pragma omp for` se statickym rozvrhovanim.
    // throw pdv::not_implemented();
}

double integrate_omp_for_dynamic(Integrand integrand, double a, double step_size, size_t step_count) {
    // Abychom vyuzili vypocetni zdroje efektivne, je potreba praci mezi jednotlive procesory rozdelit
    // pokud mozno rovnomerne. V opacnem pripade nektera vlakna skonci drive nez ostatni, a nektera jadra
    // tak budou nevyuzita. Staticky scheduling priradi stejny pocet uloh jednotlivym vlaknum, a bohuzel
    // nam tak negarantuje rovnomerne rozdeleni prace. V pripade, ze ulohy netrvaji stejne dlouho a "budeme
    // mit smulu", se nam muze stat, ze vsechny casove narocne ulohy pripadnou jednomu vlaknu. To pak bude
    // potrebovat vice casu nez ostatni.

    double acc = 0.0;

    #pragma omp parallel for reduction(+:acc) schedule(dynamic)
    for (size_t i = 0; i < step_count; i++) {
        double cx = a + (double)(2 * i + 1) * step_size / 2.0;
        double res = integrand(cx) * step_size;
        acc += res;
    }

    return acc;
    // TODO: Pouzijte pro rovnomernejsi rozdeleni prace dynamicke rozvrhovani.
    //  Vyzkousejte ruzne velikosti bloku.
    // throw pdv::not_implemented();
}
