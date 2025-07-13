#ifndef DFS_H
#define DFS_H

#include <stdbool.h>

#include "tree.h"

//dfs function
int dfs(node_t* node, int prev_color, int color_counter, bool flag);

#endif //DFS_H
