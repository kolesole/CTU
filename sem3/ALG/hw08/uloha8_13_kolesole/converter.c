#include "converter.h"

int compare(const void* a, const void* b) {
    return ((arr_attr_point_t*)a)->elevation - ((arr_attr_point_t*)b)->elevation;
}

bool my_malloc_attr_array(arr_attr_point_t** attr_array) {
    (*attr_array) = (arr_attr_point_t*)malloc(N * N * sizeof(arr_attr_point_t));
    if (*attr_array == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for attr_array!\n");
        return false;
    }

    return true;
}

void my_free_attr_array(arr_attr_point_t* attr_array) {
    free(attr_array);
}

bool convert_attr_grid_to_arr(arr_attr_point_t** attr_array, attr_cell_t** attr_grid) {
    if (!my_malloc_attr_array(attr_array)) return false;

    int indx = 0;
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            (*attr_array)[indx].row = row;
            (*attr_array)[indx].col = col;
            (*attr_array)[indx].elevation = attr_grid[row][col].elevation;
            (*attr_array)[indx].attr = attr_grid[row][col].attr;
            (*attr_array)[indx].max_path_len = INT_MIN;
            (*attr_array)[indx].max_path_attr = INT_MIN;
            indx++;
        }
    }

    qsort(*attr_array, N * N, sizeof(arr_attr_point_t), compare);

    return true;
}
