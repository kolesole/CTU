#ifndef ATTRACTIVENESS_H
#define ATTRACTIVENESS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

extern int N;
extern int DH;

// structure to represent attractive grid cell
typedef struct {
    int elevation;
    long long attr;
    long long* attrs;
    int size_of_attrs;
} attr_cell_t;

// function to allocate memory for attractive grid
bool my_malloc_attr_grid(attr_cell_t*** attr_grid, int** grid);
// function to free memory for attractive grid
void my_free_attr_grid(attr_cell_t** attr_grid);
// function to fill up attractive grid
bool fill_up_attr_grid(attr_cell_t*** attr_grid, int** grid);

#endif //ATTRACTIVENESS_H
