#include "utils.h"

bool read_input(int* N, int* H, int* E, int* S, int* C, int* K, int* M, grid_point*** grid) {
    if (scanf("%d %d %d", N, H, E) != 3) {
        fprintf(stderr, "ERROR: Wrong input!\n");
        return false;
    }

    if (scanf("%d %d %d %d", S, C, K, M) != 4) {
        fprintf(stderr, "ERROR: Wrong input!\n");
        return false;
    }

    if (!my_malloc_grid(grid, *N, *H)) return false;

    for (int i = 0; i < *H; i++) {
        int noisy_point;
        if (scanf("%d", &noisy_point) != 1) {
            fprintf(stderr, "ERROR: Wrong input!\n");
            my_free_grid(*grid, *N);
            return false;
        }

        (*grid)[noisy_point]->is_noisy = true;
    }

    for (int i = 0; i < *E; i++) {
        int first_point, second_point;
        if (scanf("%d %d", &first_point, &second_point) != 2) {
            fprintf(stderr, "ERROR: Wrong input!\n");
            my_free_grid(*grid, *N);
            return false;
        }

        if ((*grid)[first_point]->children_size <= (*grid)[first_point]->num_of_children) {
            if (!my_realloc_grid_point(&(*grid)[first_point], (*grid)[first_point]->children_size * 2)) {
                my_free_grid(*grid, *N);
                return false;
            }
        }

        if ((*grid)[second_point]->children_size <= (*grid)[second_point]->num_of_children) {
            if (!my_realloc_grid_point(&(*grid)[second_point], (*grid)[second_point]->children_size * 2)) {
                my_free_grid(*grid, *N);
                return false;
            }
        }

        (*grid)[first_point]->children[(*grid)[first_point]->num_of_children++] = second_point;
        (*grid)[second_point]->children[(*grid)[second_point]->num_of_children++] = first_point;
    }

    return true;
}
