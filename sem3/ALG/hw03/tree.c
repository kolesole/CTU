#include "tree.h"

node_t* create_node(int color) {
    node_t* node = (node_t*)malloc(sizeof(node_t));
    if (node == NULL) {
        fprintf(stderr, "ERROR: cannot allocate memory!\n");
        return NULL;
    }

    node->left_child = NULL;
    node->right_child = NULL;
    node->color = color;

    return node;
}

node_t* create_tree(node_t** tree, int size, int index_in_array, int** blue_counters) {
    if (index_in_array >= size) {
        return NULL;
    }

    node_t* node = tree[index_in_array];

    if (node->color == 2) return node;

    node->left_child = create_tree(tree, size, (index_in_array - (*blue_counters)[index_in_array])  * 2 + 1, blue_counters);
    node->right_child = create_tree(tree, size, (index_in_array - (*blue_counters)[index_in_array])  * 2 + 2, blue_counters);

    return node;
}

void free_tree_from_array(node_t** tree, int size) {
    for (int i = 0; i < size; i++) {
        free(tree[i]);
    }

    free(tree);
}
