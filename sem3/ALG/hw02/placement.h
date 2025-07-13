#ifndef PLACEMENT_H
#define PLACEMENT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "sensor.h"
#include "aux_grid.h"
//structure for placement
typedef struct {
    int num_of_points;
    int sum_of_elevations;
    int sum_of_sensor_elevations;
} placement;
//function to compare placements
bool compare_placements(placement* p1, placement* p2);
//function to create placement
bool create_placement(placement** p, int rows, int cols, aux_grid_point** aux_grid, int** grid, int num_of_sensors, sensor** sensors);
//function to fix intersections in placement
void fix_intersections(placement** p, int rows, int cols, aux_grid_point** aux_grid, int** grid, int num_of_sensors, sensor** sensors);

#endif //PLACEMENT_H
