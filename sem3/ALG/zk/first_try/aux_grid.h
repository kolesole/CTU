#ifndef AUX_GRID_H
#define AUX_GRID_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    int bnum;                   // num of black
    int wnum;                   // num of white
    int mnum;                   // num of mix
    int color;
    bool is_visited;
} aux_grid_point_t;

void my_free_aux_grid(int m, aux_grid_point_t** aux_grid);
bool my_malloc_aux_grid(int m, int n, aux_grid_point_t*** aux_grid);
bool create_aux_grid(int m, int n, int** grid, aux_grid_point_t*** aux_grid);

#endif //AUX_GRID_H
