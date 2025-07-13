#ifndef SENSOR_H
#define SENSOR_H

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
//structure for sensor
typedef struct {
    int range;
    int diag_range;
    int row;
    int col;
    int max_num_of_elevations;
    int max_num_of_points;
    int cur_num_of_points;
} sensor;

extern int directions[8][2];
//function to calculate diag. range for sensor
int calculate_diag_range(int range);
//function to create sensor array
bool create_sensors_array(int num_of_sensors, sensor*** sensors, int* sensor_ranges);
//function to free sensor array
void free_sensors_array(int num_of_sensors, sensor** sensors);
//function to check if point is visible from sensor
bool is_visible(sensor* sensor, int sensor_row, int sensor_col, int point_row, int point_col, int rows, int cols, int** grid, int direction);
//function to find in which direction is point
int find_direction(int row1, int col1, int row2, int col2);

#endif //SENSOR_H
