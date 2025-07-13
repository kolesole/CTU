#include "position.h"

int compare_positions(const void* a, const void* b) {
    return ((position*)b)->num_of_points - ((position*)a)->num_of_points;
}

bool create_positions(position*** positions, int rows, int cols, aux_grid_point** aux_grid, int num_of_sensors) {
    *positions = (position**)malloc(num_of_sensors * sizeof(position*));
    if (*positions == NULL) {
        fprintf(stderr, "ERROR: cannot allocate memory for positions!\n");
        return false;
    }

    for (int i = 0; i < num_of_sensors; i++) {
        (*positions)[i] = (position*)malloc(rows * cols * sizeof(position));
        if ((*positions)[i] == NULL) {
            fprintf(stderr, "ERROR: cannot allocate memory for positions!\n");
            free_positions(*positions, num_of_sensors);
            return false;
        }
    }

    int cur_indx = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            for (int i = 0; i < num_of_sensors; i++) {
                (*positions)[i][cur_indx].row = row;
                (*positions)[i][cur_indx].col = col;
                (*positions)[i][cur_indx].num_of_points = aux_grid[row][col].num_of_points[i];
            }
            cur_indx++;
        }
    }

    for (int i = 0; i < num_of_sensors; i++) {
        qsort((*positions)[i], rows * cols, sizeof(position), compare_positions);
    }

    return true;
}

void free_positions(position** positions, int num_of_sensors) {
    for (int i = 0; i < num_of_sensors; i++) {
        free(positions[i]);
    }
    free(positions);
}