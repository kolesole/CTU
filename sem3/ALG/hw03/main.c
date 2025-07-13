#include "dfs.h"
#include "read.h"
#include "tree.h"

int main() {
    int size;
    node_t** tree;
    int* blue_counters;
    if (!read_input(&size, &tree, &blue_counters)) {
        return -1;
    }

    node_t* root = create_tree(tree, size, 0, &blue_counters);
    if (root == NULL) {
        fprintf(stderr, "Error: cannot create tree\n");
        free_tree_from_array(tree, size);
        free(blue_counters);
        return -1;
    }
    free(blue_counters);

    int max_sum = 0;
    for (int i = 0; i < size; i++) {
        node_t* cur = tree[i];
        if (cur->color == 2) continue;

        if (cur->color == cur->left_child->color && cur->color == cur->right_child->color) continue;

        int cur_sum = dfs(cur, -1, 0, true);

        max_sum = cur_sum > max_sum ? cur_sum : max_sum;
    }
    printf("%d\n", max_sum);

    free_tree_from_array(tree, size);

    return 0;
}