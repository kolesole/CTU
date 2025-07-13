#include "aux_matrix.h"

bool my_malloc_aux_matrix(int rows, int cols, int max_speed, aux_point_t*** aux_matrix) {
    *aux_matrix = (aux_point_t**)malloc(rows * sizeof(aux_point_t*));
    if (*aux_matrix == NULL) {
        fprintf(stderr, "ERROR: cannot allocate memory for aux matrix!\n");
        return false;
    }

    for (int row = 0; row < rows; row++) {
        (*aux_matrix)[row] = (aux_point_t*)malloc(cols * sizeof(aux_point_t));
        if ((*aux_matrix)[row] == NULL) {
            fprintf(stderr, "ERROR: cannot allocate memory for aux matrix!\n");
            my_free_aux_matrix(row, cols, *aux_matrix);
            return false;
        }

        for (int col = 0; col < cols; col++) {
            for (int i = 0; i < 4; i++) {
                (*aux_matrix)[row][col].is_visited[i] = (int*)malloc(max_speed * sizeof(int));
                if ((*aux_matrix)[row][col].is_visited[i] == NULL) {
                    fprintf(stderr, "ERROR: cannot allocate memory for aux matrix!\n");
                    my_free_aux_matrix(row, cols, *aux_matrix);
                    return false;
                }
            }
        }
    }

    return true;
}

void my_free_aux_matrix(int rows, int cols, aux_point_t** aux_matrix) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            for (int i = 0; i < 4; i++) {
                if (aux_matrix[row][col].is_visited[i] != NULL) {
                    free(aux_matrix[row][col].is_visited[i]);
                }
            }
        }
        if (aux_matrix[row] != NULL) {
            free(aux_matrix[row]);
        }
    }

    free(aux_matrix);
}

bool create_aux_matrix(int rows, int cols, int max_speed, int** matrix, aux_point_t*** aux_matrix) {
    if (!my_malloc_aux_matrix(rows, cols, max_speed, aux_matrix)) {
        return false;
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            (*aux_matrix)[row][col].elevation = matrix[row][col];
            for (int i = 0; i < 4; i++) {
                for (int j = 0; j < max_speed; j++) {
                    (*aux_matrix)[row][col].is_visited[i][j] = 0;
                }
            }
        }
    }

    return true;
}
