#ifndef PLACEMENT_H
#define PLACEMENT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "sensor.h"
#include "aux_grid.h"

typedef struct {
    int num_of_points;
    int sum_of_elevations;
    int sum_of_sensor_elevations;
} placement;

bool compare_placements(placement* p1, placement* p2);
bool create_placement(placement** p, int rows, int cols, aux_grid_point** aux_grid, int** grid, int num_of_sensors, sensor** sensors);
bool fix_intersections(placement** p, int rows, int cols, aux_grid_point** aux_grid, int** grid, int num_of_sensors, sensor** sensors);

#endif //PLACEMENT_H
