#ifndef ZERO_H
#define ZERO_H

#include <stdbool.h>
#include "utils.h"
//function that checks whether a given zero sector is in a rectangle with certain coordinates
bool is_zero_sector_inside_fence(int fence_row2, int fence_col2, int rectangle_row2, int rectangle_col2);
//function that checks whether a given zero sector is on the side edge of a rectangle with given coordinates
bool is_zero_sector_vertically_on_fence(int fence_row2, int fence_col2, int zero_sector_col1, int zero_sector_row2, int zero_sector_col2);
//function that checks whether a given zero sector is on the upper edge of a rectangle with given coordinates
bool is_zero_sector_horizontally_on_fence(int fence_row2, int fence_col2, int zero_sector_row1, int zero_sector_row2, int zero_sector_col2);
//function that counts how many zero sectors are in a rectangle with certain coordinates
int count_zeros_inside_fence(matrix_element** aux_zero_matrix, int fence_row1, int fence_col1, int fence_row2, int fence_col2);

#endif //ZERO_H