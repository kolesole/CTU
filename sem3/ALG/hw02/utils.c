#include "utils.h"

bool my_malloc(int rows, int cols, int*** grid) {
    *grid = (int**)malloc(sizeof(int*) * rows);
    if (*grid == NULL) {
        fprintf(stderr, "Error: cannot allocate memory for grid!\n");
        return false;
    }

    for (int row = 0; row < rows; row++) {
        (*grid)[row] = (int*)malloc(sizeof(int) * cols);
        if ((*grid)[row] == NULL) {
            fprintf(stderr, "Error: cannot allocate memory for grid!\n");
            my_free_int(row, *grid);
            return false;
        }

        for (int col = 0; col < cols; col++) {
            (*grid)[row][col] = 0;
        }
    }

    return true;
}

bool my_malloc_bool(int rows, int cols, bool*** grid) {
    *grid = (bool**) malloc(sizeof(bool*) * rows);
    if (*grid == NULL) {
        fprintf(stderr, "Error: cannot allocate memory for grid!\n");
        return false;
    }

    for (int row = 0; row < rows; row++) {
        (*grid)[row] = (bool*)malloc(sizeof(bool) * cols);
        if ((*grid)[row] == NULL) {
            fprintf(stderr, "Error: cannot allocate memory for grid!\n");
            my_free_bool(row, *grid);
            return false;
        }

        for (int col = 0; col < cols; col++) {
            (*grid)[row][col] = false;
        }
    }

    return true;
}

void my_free_int(int rows, int** grid) {
    for (int row = 0; row < rows; row++) {
        free(grid[row]);
    }

    free(grid);
}

void my_free_bool(int rows, bool** grid) {
    for (int row = 0; row < rows; row++) {
        free(grid[row]);
    }

    free(grid);
}

bool read_input(int* rows, int* cols, int*** grid, int* num_of_sensors, int** sensor_ranges) {
    if (scanf("%d %d", rows, cols) != 2) {
        fprintf(stderr, "Error: cannot read grid sizes!\n");
        return false;
    }

    if (!my_malloc(*rows, *cols, grid)) return false;

    for (int row = 0; row < *rows; row++) {
        for (int col = 0; col < *cols; col++) {
            if (scanf("%d", &(*grid)[row][col]) != 1) {
                fprintf(stderr, "Error: cannot read grid elements!\n");
                my_free_int(*rows, *grid);
                return false;
            }
        }
    }

    if (scanf("%d", num_of_sensors) != 1) {
        fprintf(stderr, "Error: cannot read number of sensors!\n");
        my_free_int(*rows, *grid);
        return false;
    }

    *sensor_ranges = (int*)malloc(sizeof(int) * (*num_of_sensors));
    if (sensor_ranges == NULL) {
        fprintf(stderr, "Error: cannot allocate memory for sensor ranges!\n");
        my_free_int(*rows, *grid);
        return false;
    }

    for (int i = 0; i < *num_of_sensors; i++) {
        if (scanf("%d", &(*sensor_ranges)[i]) != 1) {
            fprintf(stderr, "Error: cannot read sensor ranges!\n");
            my_free_int(*rows, *grid);
            free(*sensor_ranges);
            return false;
        }
    }

    return true;
}

