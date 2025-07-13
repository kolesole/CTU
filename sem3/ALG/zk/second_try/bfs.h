#ifndef BFS_H
#define BFS_H

#include <stdbool.h>

#include "grid.h"
#include "queue.h"

extern int min_path_len;
extern int min_num_of_noisy_points;

bool bfs(grid_point** grid, int start_mouse_pos, int end_mouse_pos, int start_cat_pos, int num_of_cat_jmps);


#endif //BFS_H
