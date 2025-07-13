#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "utils.h"
#include "sensor.h"

typedef struct {
    int* num_of_points;
    int* sum_of_elevations;
    int elevation;
    int*** visible_points;
} aux_grid_point;

extern int directions[8][2];

bool create_aux_grid(int rows, int cols, aux_grid_point*** aux_grid, int** grid, int num_of_sensors);
void my_free_aux(int rows, int cols, aux_grid_point** aux_grid);
void fill_aux_grid(int rows, int cols, aux_grid_point** aux_grid, int** grid, int num_of_sensors, sensor** sensors);

#endif //GRID_H
