#include <stdio.h>
#include "utils.h"
#include "rectangle.h"
#include "zero.h"
#include "dfs.h"

int main() {
    int rows, cols;
    int** matrix;
    if (!allocate_and_read(&rows, &cols, &matrix)) return -1;

    int** aux_matrix;
    if (!my_malloc_int(rows, cols, &aux_matrix)) {
        my_free_int(rows, &matrix);
        return -1;
    }

    for (int col = 0; col < cols; col++) {
        aux_matrix[0][col] = col == 0 ? matrix[0][0] : (aux_matrix[0][col - 1] + matrix[0][col]);
    }

    for (int row = 1; row < rows; row++) {
        aux_matrix[row][0] = aux_matrix[row - 1][0] + matrix[row][0];
    }

    for (int row = 1; row < rows; row++) {
        for (int col = 1; col < cols; col++) {
            aux_matrix[row][col] = matrix[row][col] + aux_matrix[row - 1][col]
                                   + aux_matrix[row][col - 1] - aux_matrix[row - 1][col - 1];
        }
    }

    bool** is_visited;
    if (!my_malloc_bool(rows, cols, &is_visited)) {
        my_free_int(rows, &matrix);
        my_free_int(rows, &aux_matrix);
        return -1;
    }

    int** zero_sectors;
    if (!my_malloc_int(rows * cols / 2, 4, &zero_sectors)) {
        my_free_int(rows, &matrix);
        my_free_int(rows, &aux_matrix);
        my_free_bool(rows, &is_visited);
        return -1;
    }

    int zero_sectors_size = 0;
    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            if (matrix[row][col] == 0 && !is_visited[row][col]) {
                int end_row = row, end_col = col;
                dfs(rows, cols, row, col, matrix, is_visited, &end_row, &end_col);
                zero_sectors[zero_sectors_size][0] = row;
                zero_sectors[zero_sectors_size][1] = col;
                zero_sectors[zero_sectors_size][2] = end_row;
                zero_sectors[zero_sectors_size][3] = end_col;
                zero_sectors_size++;
            }
        }
    }

    my_free_bool(rows, &is_visited);

    matrix_element** aux_zero_matrix;
    if (!my_malloc_aux_zero_matrix(rows, cols, &aux_zero_matrix)) {
        my_free_int(rows, &matrix);
        my_free_int(rows, &aux_matrix);
        my_free_int(rows, &zero_sectors);
        return -1;
    }

    for (int row = 0; row < rows; row++) {
        for (int col = 0; col < cols; col++) {
            aux_zero_matrix[row][col].is_inside_zero_sector = false;
            aux_zero_matrix[row][col].hor_zero_counter = 0;
            aux_zero_matrix[row][col].vert_zero_counter = 0;
            aux_zero_matrix[row][col].inside_zero_counter = 0;
            bool flag = false;
            for (int i = 0; i < zero_sectors_size; i++) {
                int sector_start_row = zero_sectors[i][0];
                int sector_start_col = zero_sectors[i][1];
                int sector_end_row = zero_sectors[i][2];
                int sector_end_col = zero_sectors[i][3];
                if (row >= sector_start_row && row <= sector_end_row && col >= sector_start_col && col <= sector_end_col) {
                    if (!flag) {
                        aux_zero_matrix[row][col].is_inside_zero_sector = true;
                        aux_zero_matrix[row][col].zero_sector_col = sector_end_col;
                        flag = true;
                    }
                    continue;
                }

                if (is_zero_sector_inside_fence(row, col, sector_end_row, sector_end_col)) {
                    aux_zero_matrix[row][col].inside_zero_counter++;
                    continue;
                }

                if (is_zero_sector_horizontally_on_fence(row, col, sector_start_row, sector_end_row, sector_end_col)) {
                    aux_zero_matrix[row][col].hor_zero_counter++;
                    continue;
                }

                if (is_zero_sector_vertically_on_fence(row, col, sector_start_col, sector_end_row, sector_end_col)) {
                    aux_zero_matrix[row][col].vert_zero_counter++;
                    continue;
                }
            }
        }
    }

    int max_sum = 0;
    for (int row1 = 0; row1 < rows - 2; row1++) {
        for (int col1 = 0; col1 < cols - 2; col1++) {
            if (aux_zero_matrix[row1][col1].is_inside_zero_sector) {
                col1 = aux_zero_matrix[row1][col1].zero_sector_col;
                continue;
            }
            for (int row2 = row1 + 2; row2 < rows; row2++) {
                if (aux_zero_matrix[row2][col1].is_inside_zero_sector) {
                    col1 = aux_zero_matrix[row2][col1].zero_sector_col + 1;
                    if (col1 >= cols - 2) break;
                }
                for (int col2 = col1 + 2; col2 < cols; col2++) {
                    if (aux_zero_matrix[row2][col2].is_inside_zero_sector
                        || aux_zero_matrix[row1][col2].is_inside_zero_sector) {
                        break;
                    }

                    if (aux_zero_matrix[row2][col2].inside_zero_counter < zero_sectors_size / 2) {
                        continue;
                    }

                    int sum = shell_sum(aux_matrix, row1, col1, row2, col2);

                    if (sum <= max_sum) continue;

                    if (aux_zero_matrix[row2][col2].hor_zero_counter > aux_zero_matrix[row2][col1].hor_zero_counter
                        || aux_zero_matrix[row1][col2].hor_zero_counter > aux_zero_matrix[row1][col1].hor_zero_counter) {
                        break;
                    }

                    if (aux_zero_matrix[row2][col2].vert_zero_counter > aux_zero_matrix[row1][col2].vert_zero_counter
                        || aux_zero_matrix[row2][col1].vert_zero_counter > aux_zero_matrix[row1][col1].vert_zero_counter) {
                        continue;
                    }

                    int total_zeros = count_zeros_inside_fence(aux_zero_matrix, row1, col1, row2, col2);

                    if (total_zeros > zero_sectors_size / 2) {
                        break;
                    }

                    if (total_zeros == zero_sectors_size / 2) max_sum = sum;
                }
            }
        }
    }

    printf("%d\n", max_sum);

    my_free_int(rows, &matrix);
    my_free_int(rows, &aux_matrix);
    my_free_int(rows * cols / 2, &zero_sectors);
    my_free_zero_matrix(rows, &aux_zero_matrix);

    return 0;
}