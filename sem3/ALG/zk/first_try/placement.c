#include "placement.h"

bool find_best_placement(int m, int n, int** grid, aux_grid_point_t*** aux_grid, int row, int col, int* min_row, int* min_col) {
    if (row > m || col > n || row <= 0 || col <= 0) return false;
    if ((*aux_grid)[row][col].is_visited) return false;

    int max = 0;
    int color = (*aux_grid)[row][col].color;
    aux_grid_point_t point = (*aux_grid)[row][col];
    int i = 0, j = 0;
    for (int cur_row = row; cur_row > i; cur_row--) {
        for (int cur_col = col; cur_col > j; cur_col--) {
            if ((*aux_grid)[cur_row][cur_col].is_visited) {
                j = cur_col;
                break;
            }
            aux_grid_point_t help_point;
            help_point.bnum = point.bnum - (*aux_grid)[row][cur_col - 1].bnum - (*aux_grid)[cur_row - 1][col].bnum + (*aux_grid)[cur_row - 1][cur_col - 1].bnum;
            help_point.wnum = point.wnum - (*aux_grid)[row][cur_col - 1].wnum - (*aux_grid)[cur_row - 1][col].wnum + (*aux_grid)[cur_row - 1][cur_col - 1].wnum;
            help_point.mnum = point.mnum - (*aux_grid)[row][cur_col - 1].mnum - (*aux_grid)[cur_row - 1][col].mnum + (*aux_grid)[cur_row - 1][cur_col - 1].mnum;

            int sum = help_point.bnum + help_point.wnum + help_point.mnum;

            if (color == 0) {
                if (help_point.wnum == 0 && sum > max) {
                    max = sum;
                    *min_row = cur_row;
                    *min_col = cur_col;
                }
            }

            if (color == 1) {
                if (help_point.bnum == 0 && sum > max) {
                    max = sum;
                    *min_row = cur_row;
                    *min_col = cur_col;
                }
            }

            if (color == 2) {
                if ((help_point.wnum == 0 || help_point.bnum == 0) && sum > max) {
                    max = sum;
                    *min_row = cur_row;
                    *min_col = cur_col;
                }
            }
        }
    }

    mark_points(*min_row, *min_col, row, col, aux_grid);
    /*printf("%d %d %d %d\n", max_row, max_col, row, col);*/
    return true;
}

void mark_points(int row1, int col1, int row2, int col2, aux_grid_point_t*** aux_grid) {
    for (int row = row1; row <= row2; row++) {
        for (int col = col1; col <= col2; col++) {
            (*aux_grid)[row][col].is_visited = true;
        }
    }
}

void unmark_points(int m, int n, aux_grid_point_t*** aux_grid) {
    for (int row = 1; row <= m; row++) {
        for (int col = 1; col <= n; col++) {
            (*aux_grid)[row][col].is_visited = false;
        }
    }
}

void unmark_points1(int row1, int col1, int row2, int col2, aux_grid_point_t*** aux_grid) {
    for (int row = row1; row <= row2; row++) {
        for (int col = col1; col <= col2; col++) {
            (*aux_grid)[row][col].is_visited = false;
        }
    }
}
