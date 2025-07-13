#ifndef AUX_MATRIX_H
#define AUX_MATRIX_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
//structure for aux_matrix point
typedef struct {
    int elevation;
    int* is_visited[4];
} aux_point_t;
//function to allocate memory for aux_matrix
bool my_malloc_aux_matrix(int rows, int cols, int max_speed, aux_point_t*** aux_matrix);
//function to free memory for aux_matrix
void my_free_aux_matrix(int rows, int cols, aux_point_t** aux_matrix);
//function to fill up aux_matrix
bool create_aux_matrix(int rows, int cols, int max_speed, int** matrix, aux_point_t*** aux_matrix);

#endif //AUX_MATRIX_H
