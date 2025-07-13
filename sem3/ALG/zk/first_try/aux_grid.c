#include "aux_grid.h"

void my_free_aux_grid(int m, aux_grid_point_t** aux_grid) {
    for (int i = 0; i < m; i++) {
        free(aux_grid[i]);
    }

    free(aux_grid);
}

bool my_malloc_aux_grid(int m, int n, aux_grid_point_t*** aux_grid) {
    *aux_grid = (aux_grid_point_t**)malloc(sizeof(aux_grid_point_t*) * m);
    if (*aux_grid == NULL) {
        fprintf(stderr, "ERROR: cannot allocate memory!\n");
        return false;
    }

    for (int i = 0; i < m; i++) {
        (*aux_grid)[i] = (aux_grid_point_t*)malloc(sizeof(aux_grid_point_t) * n);
        if ((*aux_grid)[i] == NULL) {
            my_free_aux_grid(i, *aux_grid);
            fprintf(stderr, "ERROR: cannot allocate memory!\n");
            return false;
        }
    }

    return true;
}

bool create_aux_grid(int m, int n, int** grid, aux_grid_point_t*** aux_grid) {
    if (!my_malloc_aux_grid(m + 1, n + 1, aux_grid)) {
        return false;
    }

    for (int i = 0; i < n + 1; i++) {
        (*aux_grid)[0][i].bnum = 0;
        (*aux_grid)[0][i].wnum = 0;
        (*aux_grid)[0][i].mnum = 0;
        (*aux_grid)[0][i].is_visited = true;
    }

    for (int i = 0; i < m + 1; i++) {
        (*aux_grid)[i][0].bnum = 0;
        (*aux_grid)[i][0].wnum = 0;
        (*aux_grid)[i][0].mnum = 0;
        (*aux_grid)[i][0].is_visited = true;
    }

    for (int row = 0; row < m; row++) {
        for (int col = 0; col < n; col++) {
            switch (grid[row][col]) {
                case 0:
                    (*aux_grid)[row + 1][col + 1].bnum = 1;
                    (*aux_grid)[row + 1][col + 1].wnum = 0;
                    (*aux_grid)[row + 1][col + 1].mnum = 0;
                    break;
                case 1:
                    (*aux_grid)[row + 1][col + 1].bnum = 0;
                    (*aux_grid)[row + 1][col + 1].wnum = 1;
                    (*aux_grid)[row + 1][col + 1].mnum = 0;
                    break;
                case 2:
                    (*aux_grid)[row + 1][col + 1].bnum = 0;
                    (*aux_grid)[row + 1][col + 1].wnum = 0;
                    (*aux_grid)[row + 1][col + 1].mnum = 1;
                    break;
                default:
                    break;
            }

            (*aux_grid)[row + 1][col + 1].bnum += (*aux_grid)[row][col + 1].bnum + (*aux_grid)[row + 1][col].bnum - (*aux_grid)[row][col].bnum;
            (*aux_grid)[row + 1][col + 1].wnum += (*aux_grid)[row][col + 1].wnum + (*aux_grid)[row + 1][col].wnum - (*aux_grid)[row][col].wnum;
            (*aux_grid)[row + 1][col + 1].mnum += (*aux_grid)[row][col + 1].mnum + (*aux_grid)[row + 1][col].mnum - (*aux_grid)[row][col].mnum;
            (*aux_grid)[row + 1][col + 1].is_visited = false;
            (*aux_grid)[row + 1][col + 1].color = grid[row][col];
        }
    }

    return true;
}
