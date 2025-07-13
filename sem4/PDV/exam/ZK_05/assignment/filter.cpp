#include <cmath>
#include "data_table.h"

void filtering(data_table& table, unsigned int iterations) {
    const int S = table.getSize();

    for (int iter=0; iter<iterations; ++iter) {
        for (int i = 0; i < S; ++i) {
            for (int j = 0; j < S; ++j) {
                int old_value = table(i, j);
                int new_value = old_value*old_value;

                // Update hodnoty pocitame na zaklade 4-okoli
                new_value += (i-1 >= 0) ? table(i-1,j)*table(i-1,j) : 0;
                new_value += (j-1 >= 0) ? table(i,j-1)*table(i,j-1) : 0;
                new_value += (i+1 < S) ? table(i+1,j)*table(i+1,j) : 0;
                new_value += (j+1 < S) ? table(i,j+1)*table(i,j+1) : 0;

                table(i,j) = std::sqrt(new_value/3);
            }
        }
    }
}

void update(data_table& table, int i, int j, int S) {
    int old_value = table(i, j);
    int new_value = old_value*old_value;

    // Update hodnoty pocitame na zaklade 4-okoli
    new_value += (i-1 >= 0) ? table(i-1,j)*table(i-1,j) : 0;
    new_value += (j-1 >= 0) ? table(i,j-1)*table(i,j-1) : 0;
    new_value += (i+1 < S) ? table(i+1,j)*table(i+1,j) : 0;
    new_value += (j+1 < S) ? table(i,j+1)*table(i,j+1) : 0;

    table(i,j) = std::sqrt(new_value/3);
}
void filtering_par(data_table& table, unsigned int iterations) {
    const int S = table.getSize();

    for (int iter=0; iter<iterations; ++iter) {
        for (int i = 0; i < S; ++i) {
            #pragma omp parallel for
            for (int j = 0; j <= i; ++j) {
                update(table, i - j, j, S);
            }
        }

        for (int j = 1; j < S; j++) {
            #pragma omp parallel for
            for (int i = S - 1; i >= j; i--) {
                update(table, i, j + (S - 1 - i), S);
            }
        }
    }
}

