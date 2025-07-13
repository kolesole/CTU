#ifndef POSITION_H
#define POSITION_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "aux_grid.h"
//structure for position
typedef struct {
    int row;
    int col;
    int num_of_points;
} position;
//function to compare positions
int compare_positions(const void* a, const void* b);
//function to create and sort positions array
bool create_positions(position*** positions, int rows, int cols, aux_grid_point** aux_grid, int num_of_sensors);
//function to free positions array
void free_positions(position** positions, int num_of_sensors);


#endif //POSITION_H
