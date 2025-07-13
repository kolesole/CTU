#ifndef PLACEMENT_H
#define PLACEMENT_H

#include <stdlib.h>

#include "aux_grid.h"

bool find_best_placement(int m, int n, int** grid, aux_grid_point_t*** aux_grid, int row, int col, int* min_row, int* min_col);
bool find_best_placement2(int m, int n, int** grid, aux_grid_point_t*** aux_grid, int row, int col);
bool find_best_placement3(int m, int n, int** grid, aux_grid_point_t*** aux_grid, int row, int col);
void mark_points(int row1, int col1, int row2, int col2, aux_grid_point_t*** aux_grid);
void unmark_points(int m, int n, aux_grid_point_t*** aux_grid);
void unmark_points1(int row1, int col1, int row2, int col2, aux_grid_point_t*** aux_grid);

#endif //PLACEMENT_H
