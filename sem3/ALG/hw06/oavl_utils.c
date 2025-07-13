#include "oavl_utils.h"

bool create_new_vertex(vertex_t** vertex, int key) {
    *vertex = (vertex_t*)malloc(sizeof(vertex_t));
    if (*vertex == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory!\n");
        return false;
    }

    (*vertex)->key = key;
    (*vertex)->left_depth = 0;
    (*vertex)->right_depth = 0;
    (*vertex)->depth = 0;
    (*vertex)->is_marked = false;
    (*vertex)->left = NULL;
    (*vertex)->right = NULL;

    return true;
}

void free_vertex(vertex_t* vertex) {
    free(vertex);
}

void free_tree(vertex_t* root) {
    if (root == NULL) return;

    free_tree(root->left);
    free_tree(root->right);
    free_vertex(root);
}
