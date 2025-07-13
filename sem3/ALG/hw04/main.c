#include <stdio.h>

#include "utils.h"
#include "aux_matrix.h"
#include "bfs.h"

const int directions[4][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1},
};

int main() {
    int rows, cols;
    int max_speed;
    int** matrix;
    if (!read_input(&rows, &cols, &max_speed, &matrix)) {
        return -1;
    }

    aux_point_t** aux_matrix;
    if (!create_aux_matrix(rows, cols, max_speed, matrix, &aux_matrix)) {
        return -1;
    }
    my_free_int_matrix(rows, matrix);

    int min_path;
    bfs(rows, cols, aux_matrix, max_speed, &min_path);

    printf("%d\n", min_path);

    my_free_aux_matrix(rows, cols, aux_matrix);
    return 0;
}