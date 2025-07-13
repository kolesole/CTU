#include "rectangle.h"

int sum_rectangle(int** aux_matrix, int row1, int col1, int row2, int col2) {
    int sum = aux_matrix[row2][col2];

    sum -= (row1 > 0 ? aux_matrix[row1 - 1][col2] : 0);

    sum -= (col1 > 0 ? aux_matrix[row2][col1 - 1] : 0);

    sum += (row1 > 0 && col1 > 0 ? aux_matrix[row1 - 1][col1 - 1] : 0);

    return sum;
}

int shell_sum(int** aux_matrix, int row1, int col1, int row2, int col2) {
    int outside_sum = sum_rectangle(aux_matrix, row1, col1, row2, col2);

    if (row2 - row1 > 1 && col2 - col1 > 1) {
        int inside_sum = sum_rectangle(aux_matrix, row1 + 1, col1 + 1, row2 - 1, col2 - 1);
        return outside_sum - inside_sum;
    }

    return outside_sum;
}