#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <limits.h>

#include "attractiveness.h"

extern int N;
extern int H1;
extern int H2;

typedef struct {
    int row, col;
    int elevation;
    int attr;
    int max_path_len;
    long long max_path_attr;
} arr_attr_point_t;

int compare(const void* a, const void* b);
bool my_malloc_attr_array(arr_attr_point_t** attr_array);
void my_free_attr_array(arr_attr_point_t* attr_array);
bool convert_attr_grid_to_arr(arr_attr_point_t** attr_array, attr_cell_t** attr_grid);

#endif //CONVERTER_H
