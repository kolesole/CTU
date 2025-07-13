#ifndef BACKTRACKING_H
#define BACKTRACKING_H

#include <stdbool.h>

#include "placement.h"
#include "position.h"
//function for backtracking(place sensors)
void place_sensors(placement** max_placement, int rows, int cols, int** is_visible, aux_grid_point** aux_grid, placement cur_placement, int depth, position** positions, int num_of_sensors, sensor** sensors);


#endif //BACKTRACKING_H
