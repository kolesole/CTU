#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "sensor.h"
#include "aux_grid.h"
#include "placement.h"

int directions[8][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};

typedef struct {
    int row;
    int col;
    int num_of_points;
} position;

int compare_positions(const void* a, const void* b) {
    return ((position*)b)->num_of_points - ((position*)a)->num_of_points;
}

void place_sensors(placement** max_placement, int rows, int cols, int** grid, aux_grid_point** aux_grid, int depth, int num_of_sensors, sensor** sensors);
int main() {
    int rows, cols;
    int** grid;
    int num_of_sensors;
    int* sensor_ranges;
    if (!read_input(&rows, &cols, &grid, &num_of_sensors, &sensor_ranges)) return -1;

    sensor** sensors;
    if (!create_sensors_array(num_of_sensors, &sensors, sensor_ranges)) {
        my_free_int(rows, grid);
        free(sensor_ranges);
        return -1;
    }

    aux_grid_point** aux_grid;
    if (!create_aux_grid(rows, cols, &aux_grid, grid, num_of_sensors)) {
        my_free_int(rows, grid);
        free(sensor_ranges);
        free_sensors_array(num_of_sensors, sensors);
        return -1;
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            aux_grid[row][col].visible_points = (int***)malloc(num_of_sensors * sizeof(int**));
            for (int sensor = 0; sensor < num_of_sensors; sensor++) {
                aux_grid[row][col].visible_points[sensor] = (int**)malloc((sensors[sensor]->range * 4 + sensors[sensor]->diag_range * 4) * sizeof(int*));
                for (int i = 0; i < (sensors[sensor]->range * 4 + sensors[sensor]->diag_range * 4); i++) {
                    aux_grid[row][col].visible_points[sensor][i] = (int*)malloc(2 * sizeof(int));
                }
            }
        }
    }

    fill_aux_grid(rows, cols, aux_grid, grid, num_of_sensors, sensors);

    /*for (int i = 0; i < aux_grid[0][0].num_of_points[3]; i++) {
        printf("%d %d\n", aux_grid[0][0].visible_points[3][i][0], aux_grid[0][0].visible_points[3][i][1]);
    }*/

    bool** is_visited = (bool**) malloc(rows * sizeof(bool*));
    for (int i = 0; i < rows; i++) {
        is_visited[i] = (bool*)malloc(cols * sizeof(bool));
        for (int j = 0; j < cols; j++) is_visited[i][j] = false;
    }

    for (int i = num_of_sensors - 1; i >= 0; i--) {
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (is_visited[row][col]) continue;

                bool flag = false;
                if (sensors[i]->cur_num_of_points < aux_grid[row][col].num_of_points[i]) {
                    if (sensors[i]->max_num_of_points < aux_grid[row][col].num_of_points[i]) {
                        sensors[i]->max_num_of_points = aux_grid[row][col].num_of_points[i];
                    }
                    for (int j = num_of_sensors - 1; j > i; j--) {
                        int d1 = find_direction(sensors[j]->row, sensors[j]->col, row, col);
                        int d2 = find_direction(row, col, sensors[j]->row, sensors[j]->col);
                        if (is_visible(sensors[j], sensors[j]->row, sensors[j]->col, row, col, rows, cols, grid, d1) ||
                            is_visible(sensors[i], row, col, sensors[j]->row, sensors[j]->col, rows, cols, grid, d2)) {
                            flag = true;
                            break;
                            }
                    }

                    //if (flag) continue;
                    sensors[i]->cur_num_of_points = aux_grid[row][col].num_of_points[i];
                    sensors[i]->row = row;
                    sensors[i]->col = col;
                }
            }
        }

        is_visited[sensors[i]->row][sensors[i]->col] = true;
    }
    for (int row = 0; row < rows; row++) {
        free(is_visited[row]);
    }
    free(is_visited);

    /*position** positions = (position**)malloc(num_of_sensors * sizeof(position*));
    for (int i = 0; i < num_of_sensors; i++) {
        positions[i] = (position*)malloc(rows * cols * sizeof(position));
    }

    int cur_indx = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            for (int i = 0; i < num_of_sensors; i++) {
                positions[i][cur_indx].row = row;
                positions[i][cur_indx].col = col;
                positions[i][cur_indx].num_of_points = aux_grid[row][col].num_of_points[i];
            }
            cur_indx++;
        }
    }

    for (int i = 0; i < num_of_sensors; i++) {
        qsort(positions[i], rows * cols, sizeof(position), compare_positions);
    }*/

    placement* max_placement;
    //create_placement(&max_placement, rows, cols, aux_grid, grid, num_of_sensors, sensors);

    //printf("%d\n", max_placement->num_of_points);

    place_sensors(&max_placement, rows, cols, grid, aux_grid, 0, num_of_sensors, sensors);

    printf("%d %d %d\n", max_placement->num_of_points, max_placement->sum_of_elevations, max_placement->sum_of_sensor_elevations);

    free(max_placement);

    my_free_aux(rows, cols, aux_grid);
    my_free_int(rows, grid);
    free(sensor_ranges);
    free_sensors_array(num_of_sensors, sensors);

    return 0;
}

void place_sensors(placement** max_placement, int rows, int cols, int** grid, aux_grid_point** aux_grid, int depth, int num_of_sensors, sensor** sensors) {
    if (depth == num_of_sensors) {
        if (*max_placement == NULL) {
            create_placement(max_placement, rows, cols, aux_grid, grid, num_of_sensors, sensors);
            return;
        }

        placement* new_placement;
        int num_of_points = 0;
        for (int i = 0; i < num_of_sensors; i++) {
            sensor* cur_s = sensors[i];
            num_of_points += aux_grid[cur_s->row][cur_s->col].num_of_points[i] + 1;
        }
        if (num_of_points < (*max_placement)->num_of_points) return;

        create_placement(&new_placement, rows, cols, aux_grid, grid, num_of_sensors, sensors);

        if (!compare_placements(*max_placement, new_placement)) {
            free(*max_placement);
            *max_placement = new_placement;
        } else {
            free(new_placement);
        }
        return;
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            int cur_sum = 0;
            bool flag = false;
            for (int i = 0; i < depth; i++) {
                if ((row == sensors[i]->row && col == sensors[i]->col)) {
                    flag = true;
                    break;
                }

                cur_sum += aux_grid[sensors[i]->row][sensors[i]->col].num_of_points[i] + 1;
            }

            if (flag) continue;

            if (*max_placement != NULL) {
                cur_sum += aux_grid[row][col].num_of_points[depth] + 1;

                for (int i = depth + 1; i < num_of_sensors; i++) {
                    cur_sum += sensors[i]->max_num_of_points + 1;
                }

                if (cur_sum < (*max_placement)->num_of_points) continue;
            }


            sensors[depth]->row = row;
            sensors[depth]->col = col;
            place_sensors(max_placement, rows, cols, grid, aux_grid, depth + 1, num_of_sensors, sensors);
        }
    }
}