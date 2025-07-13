#include <stdio.h>
#include <stdlib.h>

#include "utils.h"
#include "sensor.h"
#include "aux_grid.h"
#include "placement.h"
#include "position.h"
#include "backtracking.h"

int directions[8][2] = {
    {-1, 0}, {1, 0}, {0, -1}, {0, 1},
    {-1, -1}, {-1, 1}, {1, -1}, {1, 1}
};

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
    free(sensor_ranges);

    aux_grid_point** aux_grid;
    if (!create_aux_grid(rows, cols, &aux_grid, grid, num_of_sensors)) {
        my_free_int(rows, grid);
        free_sensors_array(num_of_sensors, sensors);
        return -1;
    }

    if (!create_aux_grid_visible_points(rows, cols, &aux_grid, num_of_sensors, sensors)) {
        my_free_int(rows, grid);
        free_sensors_array(num_of_sensors, sensors);
        my_free_aux(rows, cols, aux_grid);
        return -1;
    }

    fill_aux_grid(rows, cols, aux_grid, grid, num_of_sensors, sensors);

    bool** is_visited;
    if (!my_malloc_bool(rows, cols, &is_visited)) {
        my_free_aux_grid_visible_points(rows, cols, aux_grid, num_of_sensors, sensors);
        my_free_aux(rows, cols, aux_grid);
        my_free_int(rows, grid);
        free_sensors_array(num_of_sensors, sensors);
        return -1;
    }

    for (int i = num_of_sensors - 1; i >= 0; i--) {
        for (int row = 0; row < rows; row++) {
            for (int col = 0; col < cols; col++) {
                if (is_visited[row][col]) continue;

                bool flag = false;
                if (sensors[i]->max_num_of_elevations < aux_grid[row][col].sum_of_elevations[i]) {
                    sensors[i]->max_num_of_elevations = aux_grid[row][col].sum_of_elevations[i];
                }

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

                    if (flag) continue;

                    sensors[i]->cur_num_of_points = aux_grid[row][col].num_of_points[i];
                    sensors[i]->row = row;
                    sensors[i]->col = col;
                }
            }
        }

        is_visited[sensors[i]->row][sensors[i]->col] = true;
    }

    my_free_bool(rows, is_visited);

    position** positions;
    if (!create_positions(&positions, rows, cols, aux_grid, num_of_sensors)) {
        my_free_aux_grid_visible_points(rows, cols, aux_grid, num_of_sensors, sensors);
        my_free_aux(rows, cols, aux_grid);
        my_free_int(rows, grid);
        free_sensors_array(num_of_sensors, sensors);
        return -1;
    }

    placement* max_placement;
    if (!create_placement(&max_placement, rows, cols, aux_grid, grid, num_of_sensors, sensors)) {
        my_free_aux_grid_visible_points(rows, cols, aux_grid, num_of_sensors, sensors);
        my_free_aux(rows, cols, aux_grid);
        my_free_int(rows, grid);
        free_positions(positions, num_of_sensors);
        free_sensors_array(num_of_sensors, sensors);
        return -1;
    }

    placement cur_placement;
    cur_placement.num_of_points = 0;
    cur_placement.sum_of_elevations = 0;
    cur_placement.sum_of_sensor_elevations = 0;

    int** is_visible;
    if (!my_malloc(rows, cols, &is_visible)) {
        my_free_aux_grid_visible_points(rows, cols, aux_grid, num_of_sensors, sensors);
        my_free_aux(rows, cols, aux_grid);
        my_free_int(rows, grid);
        free(max_placement);
        free_positions(positions, num_of_sensors);
        free_sensors_array(num_of_sensors, sensors);
        return -1;
    }

    place_sensors(&max_placement, rows, cols, is_visible, aux_grid, cur_placement, num_of_sensors - 1, positions, num_of_sensors, sensors);

    printf("%d %d %d\n", max_placement->num_of_points, max_placement->sum_of_elevations, max_placement->sum_of_sensor_elevations);

    my_free_aux_grid_visible_points(rows, cols, aux_grid, num_of_sensors, sensors);
    my_free_aux(rows, cols, aux_grid);
    my_free_int(rows, grid);
    my_free_int(rows, is_visible);
    free(max_placement);
    free_positions(positions, num_of_sensors);
    free_sensors_array(num_of_sensors, sensors);

    return 0;
}