#include "utils.h"

#include <stdlib.h>

bool my_malloc_int_matrix(int rows, int cols, int*** matrix) {
    *matrix = (int**)malloc(sizeof(int*) * rows);
    if (*matrix == NULL) {
        fprintf(stderr, "ERROR: cannot allocate memory for matrix!\n");
        return false;
    }

    for (int row = 0; row < rows; row++) {
        (*matrix)[row] = (int*)malloc(sizeof(int) * cols);
        if ((*matrix)[row] == NULL) {
            fprintf(stderr, "ERROR: cannot allocate memory for matrix!\n");
            my_free_int_matrix(row, *matrix);
            return false;
        }
    }

    return true;
}

void my_free_int_matrix(int rows, int** matrix) {
    for (int row = 0; row < rows; row++) {
        free(matrix[row]);
    }

    free(matrix);
}

bool read_input(int* rows, int* cols, int* max_speed, int*** matrix) {
    if (scanf("%d %d %d", rows, cols, max_speed) != 3) {
        fprintf(stderr, "ERROR: wrong input!\n");
        return false;
    }

    if (!my_malloc_int_matrix(*rows, *cols, matrix)) {
        return false;
    }

    for (int row = 0; row < *rows; row++) {
        for (int col = 0; col < *cols; col++) {
            if (scanf("%d", &(*matrix)[row][col]) != 1) {
                fprintf(stderr, "ERROR: wrong input!\n");
                my_free_int_matrix(*rows, *matrix);
                return false;
            }
        }
    }

    return true;
}