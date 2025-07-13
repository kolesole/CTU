#include <limits.h>
#include <stdio.h>

#include "grid.h"
#include "utils.h"
#include "bfs.h"

int min_path_len = INT_MAX;
int min_num_of_noisy_points = INT_MAX;

int main() {
    int N, H, E;
    int S, C, K, M;
    grid_point** grid;

    if (!read_input(&N, &H, &E, &S, &C, &K, &M, &grid)) return -1;

    for (int i = 0; i < N; i++) {
        grid[i]->is_visited = (int*)malloc(sizeof(int) * grid[i]->num_of_children);
        for (int j = 0; j < grid[i]->num_of_children; j++) {
            grid[i]->is_visited[j] = INT_MAX;
        }
    }

    /*for (int i = 0; i < N; i++) {
        grid[i]->v = (bool**)malloc(sizeof(bool*) * grid[i]->num_of_children));
    }
    */

    for (int i = 0; i < N; i++) {
        grid[i]->v = INT_MAX;
    }

    /*if (!bfs(grid, S, C, K, M)) {
        my_free_grid(grid, N);
        return -1;
    }*/

    printf("%d %d\n", min_path_len, min_num_of_noisy_points);

    my_free_grid(grid, N);
    return 0;
}
