#include "tree_utils.h"

bool my_malloc_node(node_t** node, int indx) {
    *node = (node_t*)malloc(sizeof(node_t));
    if (*node == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for node!\n");
        return false;
    }

    (*node)->indx = indx;
    (*node)->colour = -1;
    (*node)->num_of_children = 0;
    (*node)->size_of_children = 20;
    (*node)->children = (int*)malloc(sizeof(int) * 20);
    (*node)->cur_score = 0;
    (*node)->num_of_unmarked_children = 0;
    if ((*node)->children == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for children!\n");
        free(*node);
        return false;
    }

    return true;
}

bool my_realloc_node(node_t** node, int new_size_of_children) {
    int* tmp = (int*)realloc((*node)->children, new_size_of_children * sizeof(int));
    if (tmp == NULL) {
        fprintf(stderr, "ERROR: Cannot reallocate memory for children!\n");
        return false;
    }

    (*node)->children = tmp;
    (*node)->size_of_children = new_size_of_children;

    return true;
}

void my_free_node(node_t* node) {
    free(node->children);
    free(node);
}

bool my_malloc_tree(int N, node_t*** tree) {
    *tree = (node_t**)malloc(sizeof(node_t*) * N);
    if (*tree == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for the tree!\n");
        return false;
    }

    for (int i = 0; i < N; i++) {
        if (!my_malloc_node(&(*tree)[i], i)) {
            my_free_tree(i, *tree);
        }
    }

    return true;
}

void my_free_tree(int N, node_t** tree) {
    for (int i = 0; i < N; i++) {
        my_free_node(tree[i]);
    }
    free(tree);
}
