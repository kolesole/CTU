#ifndef SENSOR_H
#define SENSOR_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int range;
    int diag_range;
    int row;
    int col;
    int max_num_of_points;
    int cur_num_of_points;
} sensor;

extern int directions[8][2];

int calculate_diag_range(int range);
bool create_sensors_array(int num_of_sensors, sensor*** sensors, int* sensor_ranges);
void free_sensors_array(int num_of_sensors, sensor** sensors);
bool is_visible(sensor* sensor, int sensor_row, int sensor_col, int point_row, int point_col, int rows, int cols, int** grid, int direction);
int find_direction(int row1, int col1, int row2, int col2);

#endif //SENSOR_H
