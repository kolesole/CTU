#include "utils.h"

bool my_malloc_int(int rows, int cols, int*** matrix) {
    *matrix = (int**)malloc(rows * sizeof(int*));
    if (*matrix == NULL) {
        fprintf(stderr, "Error: Cannot allocate memory for matrix!\n");
        return false;
    }

    for (int row = 0; row < rows; row++) {
        (*matrix)[row] = (int*)malloc(cols * sizeof(int));
        if ((*matrix)[row] == NULL) {
            fprintf(stderr, "Error: Cannot allocate memory for matrix row %d!\n", row);
            my_free_int(row, matrix);
            return false;
        }
    }

    return true;
}

bool my_malloc_bool(int rows, int cols, bool*** matrix) {
    *matrix = (bool**)malloc(rows * sizeof(bool*));
    if (*matrix == NULL) {
        fprintf(stderr, "Error: Cannot allocate memory for matrix!\n");
        return false;
    }

    for (int row = 0; row < rows; row++) {
        (*matrix)[row] = (bool*)malloc(cols * sizeof(bool));
        if ((*matrix)[row] == NULL) {
            fprintf(stderr, "Error: Cannot allocate memory for matrix row %d!\n", row);
            my_free_bool(row, matrix);
            return false;
        }

        for (int col = 0; col < cols; col++) {
            (*matrix)[row][col] = false;
        }
    }

    return true;
}

bool my_malloc_aux_zero_matrix(int rows, int cols, matrix_element*** matrix) {
    *matrix = (matrix_element**)malloc(rows * sizeof(matrix_element*));
    if (*matrix == NULL) {
        fprintf(stderr, "Error: Cannot allocate memory for matrix!\n");
        return false;
    }

    for (int row = 0; row < rows; row++) {
        (*matrix)[row] = (matrix_element*)malloc(cols * sizeof(matrix_element));
        if ((*matrix)[row] == NULL) {
            fprintf(stderr, "Error: Cannot allocate memory for matrix row %d!\n", row);
            my_free_zero_matrix(row, matrix);
            return false;
        }
    }

    return true;
}

void my_free_int(int rows, int*** matrix) {
    for (int row = 0; row < rows; row++) {
        free((*matrix)[row]);
    }

    free(*matrix);
}

void my_free_bool(int rows, bool*** matrix) {
    for (int row = 0; row < rows; row++) {
        free((*matrix)[row]);
    }

    free(*matrix);
}

void my_free_zero_matrix(int rows, matrix_element*** matrix) {
    for (int row = 0; row < rows; row++) {
        free((*matrix)[row]);
    }

    free(*matrix);
}

bool allocate_and_read(int* rows, int* cols, int*** matrix) {
    if (scanf("%d %d", rows, cols) != 2) {
        fprintf(stderr, "Error: Incorrect dimensions entered!\n");
        return false;
    }

    if (!my_malloc_int(*rows, *cols, matrix)) return false;

    for (int row = 0; row < *rows; row++) {
        for (int col = 0; col < *cols; col++) {
            if ((scanf("%d", &(*matrix)[row][col])) != 1) {
                fprintf(stderr, "Error: Incorrect input!\n");
                my_free_int(*rows, matrix);
                return false;
            }
        }
    }

    return true;
}
