#include "utils.h"

bool my_malloc_int_grid(int*** grid) {
    *grid = (int**)malloc(N * sizeof(int*));
    if (*grid == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for grid!\n");
        return false;
    }

    for (int i = 0; i < N; i++) {
        (*grid)[i] = (int*)malloc(N * sizeof(int));
        if ((*grid)[i] == NULL) {
            fprintf(stderr, "ERROR: Cannot allocate memory for grid!\n");
            my_free_int_grid(*grid);
            return false;
        }
    }

    return true;
}

void my_free_int_grid(int** grid) {
    for (int i = 0; i < N; i++) {
        if (grid[i] == NULL) break;

        free(grid[i]);
    }
    free(grid);
}

bool read_input(int*** grid) {
    if (scanf("%d %d %d %d", &N, &DH, &H1, &H2) != 4) {
        fprintf(stderr, "ERROR: Cannot read input!\n");
        return false;
    }

    if (!my_malloc_int_grid(grid)) return false;

    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            if (scanf("%d", &(*grid)[row][col]) != 1) {
                fprintf(stderr, "ERROR: Cannot read input!\n");
                free(*grid);
                return false;
            }
        }
    }

    return true;
}
