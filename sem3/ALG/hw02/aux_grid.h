#ifndef AUX_GRID_H
#define AUX_GRID_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "utils.h"
#include "sensor.h"
//structure for aux_grid_point
typedef struct {
    int* num_of_points;
    int* sum_of_elevations;
    int elevation;
    int*** visible_points;
} aux_grid_point;

extern int directions[8][2];
//function to create aux_grid
bool create_aux_grid(int rows, int cols, aux_grid_point*** aux_grid, int** grid, int num_of_sensors);
//function to add arrays with visible points
bool create_aux_grid_visible_points(int rows, int cols, aux_grid_point*** aux_grid, int num_of_sensors, sensor** sensors);
//function to free aux_grid
void my_free_aux(int rows, int cols, aux_grid_point** aux_grid);
//function to delete arrays with visible points
void my_free_aux_grid_visible_points(int rows, int cols, aux_grid_point** aux_grid, int num_of_sensors, sensor** sensors);
//function to fil aux_grid
void fill_aux_grid(int rows, int cols, aux_grid_point** aux_grid, int** grid, int num_of_sensors, sensor** sensors);

#endif //AUX_GRID_H
