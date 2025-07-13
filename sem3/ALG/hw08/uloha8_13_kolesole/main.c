#include <stdio.h>
#include <limits.h>

#include "utils.h"
#include "attractiveness.h"
#include "converter.h"

int N;
int DH;
int H1;
int H2;

int main() {
    int** grid;
    if (!read_input(&grid)) return -1;

    attr_cell_t** attr_grid;
    if (!fill_up_attr_grid(&attr_grid, grid)) {
        my_free_int_grid(grid);
        return - 1;
    }
    my_free_int_grid(grid);

    arr_attr_point_t* attr_arr;
    if (!convert_attr_grid_to_arr(&attr_arr, attr_grid)) {
        my_free_attr_grid(attr_grid);
        return -1;
    }
    my_free_attr_grid(attr_grid);

    int max_path_len = INT_MIN;
    long long max_path_attr = INT_MIN;
    attr_arr[0].max_path_attr = attr_arr[0].attr;
    attr_arr[0].max_path_len = 1;
    for (int i = 0; i < N * N; i++) {
        arr_attr_point_t point = attr_arr[i];
        for (int j = i + 1; j < N * N; j++) {
            int diff = attr_arr[j].elevation - point.elevation;

            if (diff > H2) break;

            if (diff < H1) continue;

            if (attr_arr[j].max_path_len < point.max_path_len + 1) {
                attr_arr[j].max_path_len = point.max_path_len + 1;
                attr_arr[j].max_path_attr = point.max_path_attr + attr_arr[j].attr;

                if (max_path_len < attr_arr[j].max_path_len) {
                    max_path_len = attr_arr[j].max_path_len;
                    max_path_attr = attr_arr[j].max_path_attr;
                }
            }
            else if (attr_arr[j].max_path_len == point.max_path_len + 1) {
                if (attr_arr[j].max_path_attr < point.max_path_attr + attr_arr[j].attr) {
                    attr_arr[j].max_path_attr = point.max_path_attr + attr_arr[j].attr;
                }

                if (max_path_len == attr_arr[j].max_path_len && max_path_attr < attr_arr[j].max_path_attr) {
                    max_path_attr = attr_arr[j].max_path_attr;
                }
            }
        }
    }

    printf("%d %lld\n", max_path_len, max_path_attr);
    my_free_attr_array(attr_arr);
    return 0;
}