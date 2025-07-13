#include "placement.h"

bool compare_placements(placement* p1, placement* p2) {
    if (p1->num_of_points == p2->num_of_points) {
        if (p1->sum_of_elevations == p2->sum_of_elevations) {
            return p1->sum_of_sensor_elevations < p2->sum_of_sensor_elevations;
        }

        return p1->sum_of_elevations > p2->sum_of_elevations;
    }

    return p1->num_of_points > p2->num_of_points;
}

bool create_placement(placement** p, int rows, int cols, aux_grid_point** aux_grid, int** grid, int num_of_sensors, sensor** sensors) {
    *p = (placement*)malloc(sizeof(placement));
    if (*p == NULL) {
        fprintf(stderr, "Error; Cannot allocate memory for placement!\n");
        return false;
    }

    (*p)->num_of_points = 0;
    (*p)->sum_of_elevations = 0;
    (*p)->sum_of_sensor_elevations = 0;
    for (int i = 0; i < num_of_sensors; i++) {
        sensor* cur_s = sensors[i];

        (*p)->num_of_points += aux_grid[cur_s->row][cur_s->col].num_of_points[i] + 1;
        (*p)->sum_of_elevations += aux_grid[cur_s->row][cur_s->col].sum_of_elevations[i] + aux_grid[cur_s->row][cur_s->col].elevation;
        (*p)->sum_of_sensor_elevations += aux_grid[cur_s->row][cur_s->col].elevation;
    }

    /*for (int sensor_indx1 = 0; sensor_indx1 < num_of_sensors; sensor_indx1++) {
        sensor* sensor1 = sensors[sensor_indx1];
        for (int sensor_indx2 = 0; sensor_indx2 < num_of_sensors; sensor_indx2++) {
            sensor* sensor2 = sensors[sensor_indx2];
            for (int i = 0; i < aux_grid[sensor1->row][sensor1->col].num_of_points[sensor_indx1]; i++) {
                for (int j = 0; j < aux_grid[sensor2->row][sensor2->col].num_of_points[sensor_indx2]; j++) {
                    int point_row1 = aux_grid[sensor1->row][sensor1->col].visible_points[sensor_indx1][i][0];
                    int point_col1 = aux_grid[sensor1->row][sensor1->col].visible_points[sensor_indx1][i][1];
                    int point_row2 = aux_grid[sensor2->row][sensor2->col].visible_points[sensor_indx2][j][0];
                    int point_col2 = aux_grid[sensor2->row][sensor2->col].visible_points[sensor_indx2][j][1];

                    if (point_row1 == point_row2 && point_col1 == point_col2) {
                        (*p)->num_of_points--;
                        (*p)->sum_of_elevations -= aux_grid[point_row1][point_col1].elevation;
                        break;
                    }

                    if (point_row1 == sensor2->row && point_col1 == sensor2->col) {
                        (*p)->num_of_points--;
                        (*p)->sum_of_elevations -= aux_grid[sensor2->row][sensor2->col].elevation;
                    }

                    if (point_row2 == sensor1->row && point_col2 == sensor1->col) {
                        (*p)->num_of_points--;
                        (*p)->sum_of_elevations -= aux_grid[sensor1->row][sensor1->col].elevation;
                    }
                }
            }
        }
    }

    return true;*/

    return fix_intersections(p, rows, cols, aux_grid, grid, num_of_sensors, sensors);
}

bool fix_intersections(placement** p, int rows, int cols, aux_grid_point** aux_grid, int** grid, int num_of_sensors, sensor** sensors) {
    for (int sensor_indx1 = 0; sensor_indx1 < num_of_sensors; sensor_indx1++) {
        sensor* sensor1 = sensors[sensor_indx1];
        int sensor1_row = sensor1->row;
        int sensor1_col = sensor1->col;
        for (int sensor_indx2 = sensor_indx1 + 1; sensor_indx2 < num_of_sensors; sensor_indx2++) {
            sensor* sensor2 = sensors[sensor_indx2];
            int sensor2_row = sensor2->row;
            int sensor2_col = sensor2->col;

            int d1 = find_direction(sensor1->row, sensor1->col, sensor2->row, sensor2->col);
            if (is_visible(sensor1, sensor1_row, sensor1_col, sensor2_row, sensor2_col, rows, cols, grid, d1)) {
                (*p)->num_of_points--;
                (*p)->sum_of_elevations -= aux_grid[sensor2_row][sensor2_col].elevation;
            }

            int d2 = find_direction(sensor2->row, sensor2->col, sensor1->row, sensor1->col);
            if (is_visible(sensor2, sensor2_row, sensor2_col, sensor1_row, sensor1_col, rows, cols, grid, d2)) {
                (*p)->num_of_points--;
                (*p)->sum_of_elevations -= aux_grid[sensor1_row][sensor1_col].elevation;
            }

            for (int direction1 = 0; direction1 < 8; direction1++) {
                int min_sensor_range = direction1 > 3 ? sensor1->diag_range : sensor1->range;
                int point_row = sensor1_row + directions[direction1][0];
                int point_col = sensor1_col + directions[direction1][1];
                int step = 1;

                while (point_row >= 0 && point_row < rows && point_col >= 0 && point_col < cols && step <= min_sensor_range) {
                    int direction2 = find_direction(sensor2_row, sensor2_col, point_row, point_col);

                    if (direction2 == -1) break;

                    if ((sensor2_row != point_row || sensor2_col != point_col) && (sensor1_row != point_row || sensor1_col != point_col) &&
                        is_visible(sensor2, sensor2_row, sensor2_col, point_row, point_col, rows, cols, grid, direction2) &&
                        is_visible(sensor1, sensor1_row, sensor1_col, point_row, point_col, rows, cols, grid, direction1)) {
                        (*p)->num_of_points--;
                        (*p)->sum_of_elevations -= aux_grid[point_row][point_col].elevation;
                    }

                    point_row += directions[direction1][0];
                    point_col += directions[direction1][1];
                    step++;
                }
            }
        }
    }

    return true;
}
