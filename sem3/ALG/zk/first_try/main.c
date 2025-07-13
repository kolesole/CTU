#include <limits.h>
#include <stdio.h>

#include "utils.h"
#include "aux_grid.h"
#include "placement.h"

int backtracking(int m, int n, int** grid, aux_grid_point_t*** aux_grid, int row, int col);
int main() {
    int m, n;
    int** grid;
    if (!read(&m, &n, &grid)) {
        return -1;
    }

    aux_grid_point_t** aux_grid;
    if (!create_aux_grid(m, n, grid, &aux_grid)) {
        my_free(m, grid);
        return -1;
    }

    //int max = 0;
    int counter = INT_MAX;
    int counter2 = 0;
    /*for (int i = m; i > 0; i--) {
        for (int j = n; j > 0; j--) {
            counter2++;
            find_best_placement(m, n, grid, &aux_grid, i, j);
            for (int k = m; k > 0; k--) {
                for (int l = n; l > 0; l--) {
                    counter2 += find_best_placement(m, n, grid, &aux_grid, k, l) ? 1 : 0;

                    bool flag = false;
                    for (int row = m; row > 0; row--) {
                        for (int col = n; col > 0; col--) {
                            counter2 += find_best_placement(m, n, grid, &aux_grid, row, col) ? 1 : 0;
                            if (counter2 > counter) {
                                flag = true;
                                break;
                            }
                        }
                        if (flag) break;
                    }
                    unmark_points(m, n, &aux_grid);
                    counter = counter < counter2 ? counter : counter2;
                    find_best_placement(m, n, grid, &aux_grid, i, j);
                    counter2 = 1;
                }
            }

            unmark_points(m, n, &aux_grid);
            //counter = counter < counter2 ? counter : counter2;
            counter2 = 0;
        }
    }
    */
    counter = backtracking(m, n, grid, &aux_grid, m, n);
    printf("%d\n", counter);



    /*for (int row = 1; row < m + 1; row++) {
        for (int col = 1; col < n + 1; col++) {
            aux_grid[row][col].is_visited = false;
        }
    }
    int counter2 = 0;
    for (int row = 1; row <= m; row++) {
        for (int col = 1; col <= n; col++) {
            counter2 += find_best_placement2(m, n, grid, &aux_grid, row, col) ? 1 : 0;
        }
    }

    for (int row = 1; row < m + 1; row++) {
        for (int col = 1; col < n + 1; col++) {
            aux_grid[row][col].is_visited = false;
        }
    }
    int counter3 = 0;
    for (int row = m; row > 0; row--) {
        for (int col = 1; col <= n; col++) {
            counter3 += find_best_placement2(m, n, grid, &aux_grid, row, col) ? 1 : 0;
        }
    }


    printf("%d %d %d\n", counter, counter2, counter3);
    printf("%d\n", counter < counter2 ? counter : counter2);
    */

    /*for (int row = 0; row < m + 1; row++) {
        for (int col = 0; col < n + 1; col++) {
            printf("%d %d %d      ", aux_grid[row][col].bnum, aux_grid[row][col].wnum, aux_grid[row][col].mnum);
        }
        printf("\n");
    }*/

    my_free_aux_grid(m + 1, aux_grid);
    my_free(m, grid);
    return 0;
}

int backtracking(int m, int n, int** grid, aux_grid_point_t*** aux_grid, int row, int col) {
    if (row <= 0 || col <= 0 || row > m || col > n) return 0;
    int min = INT_MAX;
    int min_row, min_col;

    //if ((*aux_grid)[row][col].is_visited) return 0;

    int counter = 0;
    for (int i = row; i > 0; i--) {
        for (int j = col; j > 0; j--) {
            counter += find_best_placement(m, n, grid, aux_grid, i, j, &min_row,  &min_col) ? 1 : 0;
            bool flag = false;
            if (counter == 0) flag = true;

            counter += backtracking(m, n, grid, aux_grid, i - 1, j);
            counter +=  backtracking(m, n, grid, aux_grid,i, j - 1);
            counter += backtracking(m, n, grid, aux_grid, i + 1, j);
            counter += backtracking(m, n, grid, aux_grid,i, j + 1);
            //printf("%d\n", min);
            if (counter < min) min = counter;
            if (!flag) unmark_points1(min_row, min_col, i, j, aux_grid);
            counter = 0;
        }
    }

    return min;
}