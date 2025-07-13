#include "dfs.h"

void dfs(int rows, int cols, int row, int col, int** matrix, bool** is_visited, int* end_row, int* end_col) {
    if (row < 0 || row >= rows || col < 0 || col >= cols || is_visited[row][col] || matrix[row][col] != 0) return;

    is_visited[row][col] = true;

    if (row > *end_row) *end_row = row;

    if (col > *end_col) *end_col = col;

    dfs(rows, cols, row - 1, col, matrix, is_visited, end_row, end_col);
    dfs(rows, cols, row + 1, col, matrix, is_visited, end_row, end_col);
    dfs(rows, cols, row, col - 1, matrix, is_visited, end_row, end_col);
    dfs(rows, cols, row, col + 1, matrix, is_visited, end_row, end_col);
}

