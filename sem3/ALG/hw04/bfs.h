#ifndef BFS_H
#define BFS_H

#include <stdio.h>
#include <stdbool.h>

#include "aux_matrix.h"
#include "queue.h"

extern const int directions[4][2];
//bfs function
bool bfs(int rows, int cols, aux_point_t** aux_matrix, int max_speed, int* min_path);
//function to check if jump is possible from one point to other
bool jmp_is_possible(int rows, int cols, int point1_row, int point1_col, int point2_row, int point2_col, int speed, int direction, aux_point_t** aux_matrix);

#endif //BFS_H
