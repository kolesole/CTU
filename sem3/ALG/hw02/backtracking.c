#include "backtracking.h"

void place_sensors(placement** max_placement, int rows, int cols, int** is_visible, aux_grid_point** aux_grid, placement cur_placement, int depth, position** positions, int num_of_sensors, sensor** sensors) {
    if (depth == -1) {
        if (!compare_placements(*max_placement, &cur_placement)) {
            (*max_placement)->num_of_points = cur_placement.num_of_points;
            (*max_placement)->sum_of_elevations = cur_placement.sum_of_elevations;
            (*max_placement)->sum_of_sensor_elevations = cur_placement.sum_of_sensor_elevations;
        }
        return;
    }

    for (int j = 0; j < rows * cols; j++) {
        int row = positions[depth][j].row;
        int col = positions[depth][j].col;

        placement new_placement;

        new_placement.num_of_points = cur_placement.num_of_points;
        new_placement.sum_of_elevations = cur_placement.sum_of_elevations;

        if (is_visible[row][col] >= 1000) continue;

        new_placement.num_of_points += aux_grid[row][col].num_of_points[depth];
        new_placement.sum_of_elevations += aux_grid[row][col].sum_of_elevations[depth];
        if (is_visible[row][col] == 0) {
            new_placement.num_of_points++;
            new_placement.sum_of_elevations += aux_grid[row][col].elevation;
        }

        is_visible[row][col] += 1001;

        for (int i = 0; i < aux_grid[row][col].num_of_points[depth]; i++) {
            int point_row = aux_grid[row][col].visible_points[depth][i][0];
            int point_col = aux_grid[row][col].visible_points[depth][i][1];
            if (is_visible[point_row][point_col] > 0) {
                new_placement.num_of_points--;
                new_placement.sum_of_elevations -= aux_grid[point_row][point_col].elevation;
            }

            is_visible[point_row][point_col]++;
        }

        for (int i = depth - 1; i >= 0; i--) {
            new_placement.num_of_points += sensors[i]->max_num_of_points + 1;
            new_placement.sum_of_elevations += sensors[i]->max_num_of_elevations;
        }

        new_placement.sum_of_sensor_elevations = cur_placement.sum_of_sensor_elevations + aux_grid[row][col].elevation;

        bool flag = false;
        if (compare_placements(*max_placement, &new_placement)) {
            flag = true;
        }

        for (int i = depth - 1; i >= 0; i--) {
            new_placement.num_of_points -= (sensors[i]->max_num_of_points + 1);
            new_placement.sum_of_elevations -= sensors[i]->max_num_of_elevations;
        }

        if (!flag) {
            sensors[depth]->row = row;
            sensors[depth]->col = col;
            place_sensors(max_placement, rows, cols, is_visible, aux_grid, new_placement, depth - 1, positions, num_of_sensors, sensors);
        }

        for (int i = 0; i < aux_grid[row][col].num_of_points[depth]; i++) {
            int point_row = aux_grid[row][col].visible_points[depth][i][0];
            int point_col = aux_grid[row][col].visible_points[depth][i][1];
            is_visible[point_row][point_col]--;
        }

        is_visible[row][col] -= 1001;
    }
}
