#include "sensor.h"

int calculate_diag_range(int range) {
    return (int)(range / sqrt(2.0));
}

bool create_sensors_array(int num_of_sensors, sensor*** sensors, int* sensor_ranges) {
    *sensors = (sensor**)malloc(num_of_sensors * sizeof(sensor*));
    if (*sensors == NULL) {
        printf("Error: unable to allocate memory for the sensors\n");
        return false;
    }

    for (int i = 0; i < num_of_sensors; i++) {
        (*sensors)[i] = (sensor*)malloc(sizeof(sensor));
        if ((*sensors)[i] == NULL) {
            printf("Error: unable to allocate memory for the sensor\n");
            free_sensors_array(i, *sensors);
            return false;
        }
        (*sensors)[i]->range = sensor_ranges[i];
        (*sensors)[i]->diag_range = calculate_diag_range((*sensors)[i]->range);
        (*sensors)[i]->max_num_of_points = 0;
        (*sensors)[i]->cur_num_of_points = 0;
    }

    return true;
}

void free_sensors_array(int num_of_sensors, sensor** sensors) {
    for (int i = 0; i < num_of_sensors; i++) {
        free(sensors[i]);
    }

    free(sensors);
}

bool is_visible(sensor* sensor, int sensor_row, int sensor_col, int point_row, int point_col, int rows, int cols, int** grid, int direction) {
    if (direction == -1) return false;

    if (sensor_row == point_row && sensor_col == point_col) return true;

    int range = direction > 3 ? sensor->diag_range : sensor->range;

    int distance;
    if (direction > 3) {
        distance = abs(sensor_row - point_row);
    }
    else if (direction > 1) {
        distance = abs(sensor_col - point_col);
    } else {
        distance = abs(sensor_row - point_row);
    }

    if (distance > range) return false;

    int sensor_elevation = grid[sensor_row][sensor_col];
    int point_elevation = grid[point_row][point_col];
    int elevation_diff = point_elevation - sensor_elevation;

    double k = (double)elevation_diff / distance;
    int b = sensor_elevation;

    int row_change = directions[direction][0];
    int col_change = directions[direction][1];

    int tmp_sensor_row = sensor_row;
    int tmp_sensor_col = sensor_col;

    for (int step = 1; step <= range; step++) {
        tmp_sensor_row += row_change;
        tmp_sensor_col += col_change;

        if (tmp_sensor_row < 0 || tmp_sensor_row >= rows || tmp_sensor_col < 0 || tmp_sensor_col >= cols) return false;

        if (tmp_sensor_row == point_row && tmp_sensor_col == point_col) return true;

        int new_point_elevation = grid[tmp_sensor_row][tmp_sensor_col];

        if ((new_point_elevation) > (k * step) + b) return false;
    }

    return false;
}

int find_direction(int row1, int col1, int row2, int col2) {
    if (row1 > row2) {
        if (col1 == col2) {
            return 0;
        }

        if (col1 < col2) {
            return 5;
        }

        if (col1 > col2) {
            return 4;
        }
    }
    else if (row1 == row2) {
        if (col1 < col2) {
            return 3;
        }

        if (col1 > col2) {
            return 2;
        }
    }
    else if (row1 < row2) {
        if (col1 == col2) {
            return 1;
        }

        if (col1 < col2) {
            return 7;
        }

        if (col1 > col2) {
            return 6;
        }
    }

    return -1;
}
