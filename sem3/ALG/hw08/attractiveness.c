#include "attractiveness.h"

bool my_malloc_attr_grid(attr_cell_t*** attr_grid, int** grid) {
    *attr_grid = (attr_cell_t**)malloc(N * sizeof(attr_cell_t*));
    if (*attr_grid == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory!\n");
        return false;
    }

    int max_elevation = grid[N - 1][N - 1];

    for (int row = 0; row < N; row++) {
        (*attr_grid)[row] = (attr_cell_t*)malloc(N * sizeof(attr_cell_t));
        if ((*attr_grid)[row] == NULL) {
            fprintf(stderr, "ERROR: Cannot allocate memory!\n");
            my_free_attr_grid(*attr_grid);
            return false;
        }

        for (int col = 0; col < N; col++) {
            (*attr_grid)[row][col].size_of_attrs = max_elevation - grid[row][col] + 1;
            (*attr_grid)[row][col].elevation = grid[row][col];
            (*attr_grid)[row][col].attrs = (long long*)malloc(((*attr_grid)[row][col].size_of_attrs) * sizeof(long long));
            if ((*attr_grid)[row][col].attrs == NULL) {
                fprintf(stderr, "ERROR: Cannot allocate memory!\n");
                my_free_attr_grid(*attr_grid);
                return false;
            }
        }
    }

    return true;
}

void my_free_attr_grid(attr_cell_t** attr_grid) {
    for (int row = 0; row < N; row++) {
        if (attr_grid[row] == NULL) break;

        for (int col = 0; col < N; col++) {
            if (attr_grid[row][col].attrs == NULL) break;

            free(attr_grid[row][col].attrs);
        }

        free(attr_grid[row]);
    }
    free(attr_grid);
}

bool fill_up_attr_grid(attr_cell_t*** attr_grid, int** grid) {
    if (!my_malloc_attr_grid(attr_grid, grid)) return false;

    (*attr_grid)[0][0].elevation = grid[0][0];
    (*attr_grid)[0][0].attr = 0;
    for (int i = 0; i < (*attr_grid)[0][0].size_of_attrs; i++) {
        (*attr_grid)[0][0].attrs[i] = 0;
    }

    for (int i = 1; i < N; i++) {
        (*attr_grid)[i][0].elevation = grid[i][0];
        for (int j = 0; j < (*attr_grid)[i][0].size_of_attrs; j++) {
            (*attr_grid)[i][0].attrs[j] = (*attr_grid)[i - 1][0].attrs[grid[i][0] - grid[i - 1][0] + j];
        }
        (*attr_grid)[i][0].attr = (*attr_grid)[i][0].attrs[0];

        (*attr_grid)[0][i].elevation = grid[0][i];
        for (int j = 0; j < (*attr_grid)[0][i].size_of_attrs; j++) {
            (*attr_grid)[0][i].attrs[j] = (*attr_grid)[0][i - 1].attrs[grid[0][i] - grid[0][i - 1] + j];
        }
        (*attr_grid)[0][i].attr = (*attr_grid)[0][i].attrs[0];

        for (int j = 0; j < N; j++) {
            for (int k = 0; k < (*attr_grid)[i][0].size_of_attrs; k++) {
                (*attr_grid)[i][0].attrs[k] += (grid[i][0] + k - DH > grid[i - 1][j]) ? grid[i - 1][j] : - grid[i - 1][j];
            }
            (*attr_grid)[i][0].attr = (*attr_grid)[i][0].attrs[0];

            for (int k = 0; k < (*attr_grid)[0][i].size_of_attrs; k++) {
                (*attr_grid)[0][i].attrs[k] += (grid[0][i] + k - DH > grid[j][i - 1]) ? grid[j][i - 1] : - grid[j][i - 1];
            }
            (*attr_grid)[0][i].attr = (*attr_grid)[0][i].attrs[0];
        }
    }

    for (int row = 1; row < N; row++) {
        for (int col = 1; col < N; col++) {
            for (int i = 0; i < (*attr_grid)[row][col].size_of_attrs; i++) {
                (*attr_grid)[row][col].attrs[i] = (*attr_grid)[row - 1][col].attrs[grid[row][col] - grid[row - 1][col] + i] +
                                                  (*attr_grid)[row][col - 1].attrs[grid[row][col] - grid[row][col - 1] + i] -
                                                  (*attr_grid)[row - 1][col - 1].attrs[grid[row][col] - grid[row - 1][col - 1] + i] -
                                                  (grid[row][col] + i - DH > grid[row - 1][col - 1] ? grid[row - 1][col - 1] : - grid[row - 1][col - 1]);
            }
            (*attr_grid)[row][col].attr = (*attr_grid)[row][col].attrs[0];
        }
    }

    /*printf("\n");
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++) {
            printf("%d\t ", (*attr_grid)[row][col].attr);
        }
        printf("\n");
    }
    printf("\n");*/

    return true;
}