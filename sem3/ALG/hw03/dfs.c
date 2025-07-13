#include "dfs.h"

int dfs(node_t* node, int prev_color, int color_counter, bool flag) {
    if (node->color == 2) return 1;

    if (node->color == prev_color) {
        color_counter++;
        if (color_counter > 2) return -1;
    } else {
        color_counter = 1;
        prev_color = node->color;
    }

    int left_sum = dfs(node->left_child, prev_color, color_counter, false);
    int right_sum = dfs(node->right_child, prev_color, color_counter, false);
    if (!flag) {
        return left_sum > right_sum ? left_sum + 1 : right_sum + 1;
    }
    if (left_sum == -1 || right_sum == -1) return -1;
    return left_sum + right_sum + 1;
}
