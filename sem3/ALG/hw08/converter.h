#ifndef CONVERTER_H
#define CONVERTER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "attractiveness.h"

extern int N;

// structure to represent attractive array point
typedef struct {
    int row, col;
    int elevation;
    long long attr;
    int max_path_len;
    long long max_path_attr;
} arr_attr_point_t;

// comparator for sorting attractive array
int compare(const void* a, const void* b);
// function to allocate memory for attractive array
bool my_malloc_attr_array(arr_attr_point_t** attr_array);
// function to free memory for attractive array
void my_free_attr_array(arr_attr_point_t* attr_array);
// function to convert attractive grid to attractive array and sort array
bool convert_attr_grid_to_arr(arr_attr_point_t** attr_array, attr_cell_t** attr_grid);

#endif //CONVERTER_H
