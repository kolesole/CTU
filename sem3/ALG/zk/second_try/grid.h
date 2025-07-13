#ifndef GRID_H
#define GRID_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct grid_point {
    int indx;
    bool is_noisy;
    int* is_visited;
    int v;
    int children_size;
    int num_of_children;
    int* children;
} grid_point;

bool my_malloc_grid_point(grid_point** point, int indx, int num_of_children, int num_of_points, int num_of_cat_jmps);
bool my_realloc_grid_point(grid_point** point, int new_children_size);
void my_free_grid_point(grid_point* point, int num_of_points);
bool my_malloc_grid(grid_point*** grid, int num_of_points, int num_of_cat_jmps);
void my_free_grid(grid_point** grid, int num_of_points);


#endif //GRID_H
