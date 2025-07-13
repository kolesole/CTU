#include "aux_grid.h"

bool create_aux_grid(int rows, int cols, aux_grid_point*** aux_grid, int** grid, int num_of_sensors) {
    *aux_grid = (aux_grid_point**)malloc(sizeof(aux_grid_point*) * rows);
    if (*aux_grid == NULL) {
        fprintf(stderr, "ERROR: cannot allocate memory for aux_grid!\n");
        return false;
    }

    for (int row = 0; row < rows; row++) {
        (*aux_grid)[row] = (aux_grid_point*)malloc(sizeof(aux_grid_point) * cols);
        if ((*aux_grid)[row] == NULL) {
            fprintf(stderr, "ERROR: cannot allocate memory for aux_grid!\n");
            my_free_aux(row, cols, *aux_grid);
            return false;
        }

        for (int col = 0; col < cols; col++) {
            (*aux_grid)[row][col].elevation = grid[row][col];

            (*aux_grid)[row][col].num_of_points = (int*)malloc(sizeof(int) * num_of_sensors);
            (*aux_grid)[row][col].sum_of_elevations = (int*)malloc(sizeof(int) * num_of_sensors);
            if ((*aux_grid)[row][col].num_of_points == NULL || (*aux_grid)[row][col].sum_of_elevations == NULL) {
                fprintf(stderr, "ERROR: cannot allocate memory for aux_grid!\n");
                my_free_aux(row + 1, cols, *aux_grid);
                return false;
            }

            for (int i = 0; i < num_of_sensors; i++) {
                (*aux_grid)[row][col].num_of_points[i] = 0;
                (*aux_grid)[row][col].sum_of_elevations[i] = 0;
            }
        }
    }

    return true;
}

bool create_aux_grid_visible_points(int rows, int cols, aux_grid_point*** aux_grid, int num_of_sensors, sensor** sensors) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            (*aux_grid)[row][col].visible_points = (int***)malloc(num_of_sensors * sizeof(int**));
            if ((*aux_grid)[row][col].visible_points == NULL) {
                fprintf(stderr, "ERROR: cannot allocate memory for aux_grid!\n");
                my_free_aux_grid_visible_points(rows, cols, *aux_grid, num_of_sensors, sensors);
                return false;
            }

            for (int sensor = 0; sensor < num_of_sensors; sensor++) {
                (*aux_grid)[row][col].visible_points[sensor] = (int**)malloc((sensors[sensor]->range * 4 + sensors[sensor]->diag_range * 4) * sizeof(int*));
                if ((*aux_grid)[row][col].visible_points[sensor] == NULL) {
                    fprintf(stderr, "ERROR: cannot allocate memory for aux_grid!\n");
                    my_free_aux_grid_visible_points(rows, cols, *aux_grid, num_of_sensors, sensors);
                    return false;
                }

                for (int i = 0; i < (sensors[sensor]->range * 4 + sensors[sensor]->diag_range * 4); i++) {
                    (*aux_grid)[row][col].visible_points[sensor][i] = (int*)malloc(2 * sizeof(int));
                    if ((*aux_grid)[row][col].visible_points[sensor][i] == NULL) {
                        fprintf(stderr, "ERROR: cannot allocate memory for aux_grid!\n");
                        my_free_aux_grid_visible_points(rows, cols, *aux_grid, num_of_sensors, sensors);
                        return false;
                    }
                }
            }
        }
    }

    return true;
}

void my_free_aux(int rows, int cols, aux_grid_point** aux_grid) {
    if (aux_grid == NULL) return;

    for (int row = 0; row < rows; row++) {
        if (aux_grid[row] != NULL) {
            for (int col = 0; col < cols; col++) {
                free(aux_grid[row][col].num_of_points);
                free(aux_grid[row][col].sum_of_elevations);
            }
            free(aux_grid[row]);
        }
    }

    free(aux_grid);
}

void my_free_aux_grid_visible_points(int rows, int cols, aux_grid_point** aux_grid, int num_of_sensors, sensor** sensors) {
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (aux_grid[row][col].visible_points != NULL) {
                for (int sensor = 0; sensor < num_of_sensors; sensor++) {
                    if (aux_grid[row][col].visible_points[sensor] != NULL) {
                        for (int i = 0; i < (sensors[sensor]->range * 4 + sensors[sensor]->diag_range * 4); i++) {
                            if (aux_grid[row][col].visible_points[sensor][i] != NULL) {
                                free(aux_grid[row][col].visible_points[sensor][i]);
                            }
                        }
                        free(aux_grid[row][col].visible_points[sensor]);
                    }
                }
                free(aux_grid[row][col].visible_points);
            }
        }
    }
}

void fill_aux_grid(int rows, int cols, aux_grid_point** aux_grid, int** grid, int num_of_sensors, sensor** sensors) {
    for (int direction = 0; direction < 8; direction++) {
        int max_sensor_range = direction > 3 ? sensors[num_of_sensors - 1]->diag_range : sensors[num_of_sensors - 1]->range;
        for (int sensor_row = 0; sensor_row < rows; sensor_row++) {
            for (int sensor_col = 0; sensor_col < cols; sensor_col++) {
                int point_row = sensor_row + directions[direction][0];
                int point_col = sensor_col + directions[direction][1];
                int step = 1;

                while (point_row >= 0 && point_row < rows && point_col >= 0 && point_col < cols && step <= max_sensor_range + 1) {
                    if (is_visible(sensors[num_of_sensors - 1], sensor_row, sensor_col, point_row, point_col, rows, cols, grid, direction)) {
                        for (int sensor_indx = 0; sensor_indx < num_of_sensors; sensor_indx++) {
                            int sensor_range = direction > 3 ? sensors[sensor_indx]->diag_range : sensors[sensor_indx]->range;
                            if (sensor_range >= step) {
                                aux_grid[sensor_row][sensor_col].visible_points[sensor_indx][aux_grid[sensor_row][sensor_col].num_of_points[sensor_indx]][0] = point_row;
                                aux_grid[sensor_row][sensor_col].visible_points[sensor_indx][aux_grid[sensor_row][sensor_col].num_of_points[sensor_indx]][1] = point_col;
                                aux_grid[sensor_row][sensor_col].num_of_points[sensor_indx]++;
                                aux_grid[sensor_row][sensor_col].sum_of_elevations[sensor_indx] += grid[point_row][point_col];
                            }
                        }
                    }
                    point_row += directions[direction][0];
                    point_col += directions[direction][1];
                    step++;
                }
            }
        }
    }
}