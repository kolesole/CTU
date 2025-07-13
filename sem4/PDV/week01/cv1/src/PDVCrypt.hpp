#pragma once

#include "../pdv_lib/pdv_lib.hpp"
#include <cstdlib>
#include <fstream>
#include <vector>
#include <array>

/**
 * Datova struktura, ktera obsahuje parametry desifrovaciho procesu
 */
struct enc_params {
    /** Prvocislo p1 */
    uint64_t p1;
    /** Prvocislo p2 */
    uint64_t p2;
    /** Index v retezci, ze ktereho zahajime desifrovaci proces */
    size_t start;
    /** Pocet kroku desifrovani, ktere mame provest */
    size_t steps;

    enc_params() : enc_params(0, 0, 0, 0) {}

    enc_params(uint64_t p1, uint64_t p2, size_t start, size_t steps)
            : p1(p1), p2(p2), start(start), steps(steps) {};
};

class PDVCrypt {
private:
    /** Pocet znaku abecedy (v nasem pripade 27: A-Z a mezera). */
    const size_t alphabet_size;

    /**
     * Tabulka tajnych klicu (5-ti rozmerne pole, s 27 moznymi hodnotami v kazde dimenzi).
     * Pomoci teto tabulky muzeme zjistit hodnotu tajneho klice pro kazdou petici znaku.
     */
    std::vector<uint32_t> secret = std::vector<uint32_t>(
            alphabet_size * alphabet_size * alphabet_size * alphabet_size * alphabet_size);

    /** Tabulka pro mapovani z ASCII znaku do abecedy (v nasem pripade cisel 0-26) */
    std::array<uint8_t, 256> map_table{};
    /**
     * Tabulka pro mapovani z 0-26 zpet do ASCII. Pro tabulky map_table a unmap_table plati:
     * x = unmap_table[map_table[x]] pro vsechny x z abecedy
     */
    std::array<char, 256> unmap_table{};

public:
    explicit PDVCrypt(const std::string& alphabet) : alphabet_size(alphabet.length()) {
        // Nejprve nainicializujeme tabulky pro mapovani z ASCII do [0..alphabet_size-1] a zpet
        uint8_t i = 0;
        for (const char c : alphabet) {
            map_table[(uint8_t)c] = i;
            unmap_table[i] = c;
            i++;
        }
    }

    PDVCrypt(const std::string& alphabet, std::istream& secretStream) : PDVCrypt(alphabet) {
        loadSecret(secretStream);
    }

    /** Metoda pro nacteni tajneho klice ze souboru. */
    void loadSecret(std::istream& secretStream) {
        secretStream.read((char*)secret.data(),
                          (std::streamsize)(secret.size() * sizeof(secret[0])));
    }

    /** Pokud nas zajima pouze vykon (a ne "smysl" desifrovani), muzeme si vygenerovat nahodny klic. */
    [[maybe_unused]] void generateSecret() {
        pdv::uniform_random<uint32_t> random{10000, 11000};
        for (auto& s : secret) {
            s = random();
        }
    }

    /**
     * Metoda pro desifrovani retezce "string" zasifrovaneho za pouziti sifrovacich parametru
     * `params` a sifrovaci tabulky `secret`. Desifrovani probiha "in-place", tedy znaky jsou
     * prepisovane primo v retezci "string".
     */
    void decrypt(std::string& string, const enc_params& params) const {
        // Desifrovani zacina na pozici params.start
        size_t index = params.start;
        const size_t len = string.length();

        // Provadime params.steps kroku desifrovaciho procesu
        for (size_t i = 0; i < params.steps; i++) {
            // [c1,c2,c3,c4,c5] je petice znaku okolo aktualniho indexu, kterou vyuzijeme pro
            // ziskani sifrovaciho klice pro aktualni krok desifrovani.
            // Metoda `map` provadi mapovani ze znaku abecedy do intervalu [0 .. alphabet_size-1].
            uint8_t c1 = map(string[(index + len - 2) % len]);
            uint8_t c2 = map(string[(index + len - 1) % len]);
            uint8_t c3 = map(string[(index + len + 0) % len]);
            uint8_t c4 = map(string[(index + len + 1) % len]);
            uint8_t c5 = map(string[(index + len + 2) % len]);

            // Nalezneme odpovidajici sifrovaci cislo
            uint64_t currentSecret = getSecret(c1, c2, c3, c4, c5);

            // A provedeme desifrovaci vypocet (vsimnete si pouziti funkci `map` a `unmap`
            // pro prevod z ASCII do pouzite abecedy a zpet)
            string[index] = unmap((uint8_t)((c3 + params.p1 * currentSecret) % alphabet_size));
            index = (index + params.p2 * currentSecret) % len;
        }
    }

private:
    /**
     * Metoda `map` mapuje znaky z ASCII do [0..alphabet_size-1] a `unmap` je mapuje zpet do ASCII.
     * Plati `x = unmap(map(x))` pro znaky x z pouzite abecedy.
     */
    [[nodiscard]] uint8_t map(char c) const {
        return map_table[(uint8_t)c];
    }

    [[nodiscard]] char unmap(uint8_t c) const {
        return unmap_table[c];
    }

    /** Metoda, ktera nam vrati tajne cislo pro petici znaku [c1,c2,c3,c4,c5]. */
    [[nodiscard]] uint64_t getSecret(uint8_t c1, uint8_t c2, uint8_t c3,
                                     uint8_t c4, uint8_t c5) const {
        return secret[c5 + alphabet_size *
                (c4 + alphabet_size * (c3 + alphabet_size * (c2 + alphabet_size * c1)))];
    }
};
