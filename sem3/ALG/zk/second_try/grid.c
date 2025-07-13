#include "grid.h"

bool my_malloc_grid_point(grid_point** point, int indx, int num_of_children, int num_of_points, int num_of_cat_jmps) {
    *point = (grid_point*)malloc(sizeof(grid_point));
    (*point)->indx = indx;
    (*point)->is_noisy = false;
    //(*point)->is_visited = false;
    (*point)->children_size = 10;
    (*point)->num_of_children = num_of_children;

    (*point)->children = (int*)malloc(sizeof(int) * 10);
    if ((*point)->children == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for children array!\n");
        return false;
    }

    /**point)->v = (bool*)malloc(sizeof(bool) * (num_of_cat_jmps + 2));
    if ((*point)->v == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for is_visited array!\n");
        free((*point)->children);
        return false;
    }

    for (int i = 0; i < num_of_cat_jmps + 2; i++) {
        (*point)->v[i] = false;
    }*/

    //(*point)->is_visited = false;

    return true;
}

bool my_realloc_grid_point(grid_point** point, int new_children_size) {
    int* children_tmp = (int*)realloc((*point)->children, sizeof(int) * new_children_size);
    if (children_tmp == NULL) {
        fprintf(stderr, "ERROR: Cannot reallocate memory for children array!\n");
        return false;
    }

    (*point)->children = children_tmp;
    (*point)->children_size = new_children_size;

    return true;
}

void my_free_grid_point(grid_point* point, int num_of_points) {
    free(point->children);
    //free(point->v);
    free(point);
}

bool my_malloc_grid(grid_point*** grid, int num_of_points, int num_of_cat_jmps) {
    *grid = (grid_point**)malloc(sizeof(grid_point*) * num_of_points);
    if (*grid == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for grid!\n");
        return false;
    }

    for (int i = 0; i < num_of_points; i++) {
        if (!my_malloc_grid_point(&(*grid)[i], i, 0, num_of_points, num_of_cat_jmps)) {
            my_free_grid(*grid, i);
        }
    }

    return true;
}

void my_free_grid(grid_point** grid, int num_of_points) {
    for (int i = 0; i < num_of_points; i++) {
        my_free_grid_point(grid[i], num_of_points);
    }

    free(grid);
}
