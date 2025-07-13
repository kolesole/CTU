#ifndef ATTRACTIVENESS_H
#define ATTRACTIVENESS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

extern int N;
extern int DH;

typedef struct {
    int elevation;
    int attr;
    int* attrs;
    int size_of_attrs;
} attr_cell_t;

bool my_malloc_attr_grid(attr_cell_t*** attr_grid, int** grid);
void my_free_attr_grid(attr_cell_t** attr_grid);
bool fill_up_attr_grid(attr_cell_t*** attr_grid, int** grid);

#endif //ATTRACTIVENESS_H
