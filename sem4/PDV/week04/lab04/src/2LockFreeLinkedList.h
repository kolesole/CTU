#pragma once

#include <cstdint>
#include <stdexcept>
#include <atomic>
#include "../pdv_lib/benchmark.hpp"

class LockFreeLinkedList {
public:
    class Node {
    public:
        uint64_t value;
        std::atomic<Node*> next = nullptr;

        explicit Node(uint64_t value) : value(value) {}
    };

    Node head{0};
    // TODO: Doplnte kod pro vlozeni uzlu 'node' na spravnou pozici ve spojovem seznamu.
    void insert(uint64_t value) {
        Node* node = new Node(value);
        Node* current = &head;
        while (true) {
            Node* next = current->next.load();
            while (next == nullptr || next->value > value) {
                node->next.store(next);
                if (current->next.compare_exchange_strong(next, node)) return;
                next = current->next;
            }

            current = next;
        }
    }

    // Pokud byste si chteli vyzkouset slozitejsi operaci se spojovym seznamem, muzete
    // si zkusit naimplementovat metodu pro odebrani prvku ze seznamu. Vzpomente si,
    // ze na prednasce jsme si rikali, ze mazani prvku probiha dvoufazove.
    //   1) Nejprve prvek oznacim za smazany. Tim zabranim ostatnim vlaknu vkladat za
    //      nej nove prvky.
    //   2) Pote ho vypojim ze seznamu
    //
    // Oznaceni prvku za smazany muzete provest pomoci atomickych operaci tak, ze ukazatel
    // na naslednika oznacite bitovym priznakem (schematicky napr., current->next | 1ULL).
    //
    // Pro jednoduchost nemusite resit dealokaci pameti po odebrani prvku.
    bool remove(uint64_t value) {
        throw pdv::not_implemented();
    }
};
