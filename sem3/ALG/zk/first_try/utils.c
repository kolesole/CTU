#include "utils.h"

void my_free(int m, int** grid) {
    for (int i = 0; i < m; i++) {
        free(grid[i]);
    }

    free(grid);
}

bool my_malloc_int(int m, int n, int*** grid) {
    *grid = (int**)malloc(m * sizeof(int*));
    if (*grid == NULL) {
        fprintf(stderr, "ERROR: cannot allocate memory!\n");
        return false;
    }

    for (int i = 0; i < m; i++) {
        (*grid)[i] = (int*)malloc(n * sizeof(int));
        if ((*grid)[i] == NULL) {
            my_free(i, *grid);
            fprintf(stderr, "ERROR: cannot allocate memory!\n");
            return false;
        }
    }

    return true;
}
bool read(int* m, int* n, int*** grid) {
    if (scanf("%d %d", m, n) != 2) {
        fprintf(stderr, "ERROR: wrong input!\n");
        return false;
    }

    if (!my_malloc_int(*m, *n, grid)) {
        return false;
    }

    for (int row = 0; row < *m; row++) {
        for (int col = 0; col < *n; col++) {
            if (scanf("%d", &(*grid)[row][col]) != 1) {
                fprintf(stderr, "ERROR: cannot read input!\n");
                my_free(*m, *grid);
                return false;
            }
        }
    }

    return true;
}
