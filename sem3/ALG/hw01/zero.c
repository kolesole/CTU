#include "zero.h"

bool is_zero_sector_inside_fence(int fence_row2, int fence_col2, int rectangle_row2, int rectangle_col2) {
    return  fence_row2 > rectangle_row2 && fence_col2 > rectangle_col2;
}

bool is_zero_sector_vertically_on_fence(int fence_row2, int fence_col2, int zero_sector_col1, int zero_sector_row2, int zero_sector_col2) {
    return fence_row2 > zero_sector_row2 && fence_col2 >= zero_sector_col1 && fence_col2 <= zero_sector_col2;
}

bool is_zero_sector_horizontally_on_fence(int fence_row2, int fence_col2, int zero_sector_row1, int zero_sector_row2, int zero_sector_col2) {
    return fence_col2 > zero_sector_col2 && fence_row2 >= zero_sector_row1 && fence_row2 <= zero_sector_row2;
}

int count_zeros_inside_fence(matrix_element** aux_zero_matrix, int fence_row1, int fence_col1, int fence_row2, int fence_col2) {
    int total_zeros = aux_zero_matrix[fence_row2][fence_col2].inside_zero_counter;

    total_zeros -= aux_zero_matrix[fence_row1][fence_col2].inside_zero_counter;

    total_zeros -= aux_zero_matrix[fence_row2][fence_col1].inside_zero_counter;

    total_zeros += aux_zero_matrix[fence_row1][fence_col1].inside_zero_counter;

    return total_zeros;
}