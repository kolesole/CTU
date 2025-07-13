#include "sorting.h"

bool my_malloc_sorted_tree(int N, sorted_node_t** sorted_tree) {
    *sorted_tree = (sorted_node_t*)malloc(sizeof(sorted_node_t) * N);
    if (*sorted_tree == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory for sorted tree!\n");
        return false;
    }

    return true;
}

void my_free_sorted_tree(sorted_node_t* sorted_tree) {
    free(sorted_tree);
}

int compare(const void* a, const void* b) {
    return ((sorted_node_t*)b)->num_of_children - ((sorted_node_t*)a)->num_of_children;
}

bool sort(sorted_node_t** sorted_tree, node_t** tree, int N) {
    if (!my_malloc_sorted_tree(N, sorted_tree)) return false;

    for (int i = 0; i < N; i++) {
        (*sorted_tree)[i].indx = tree[i]->indx;
        (*sorted_tree)[i].num_of_children = tree[i]->num_of_children;
    }

    qsort(*sorted_tree, N, sizeof(sorted_node_t), compare);

    return true;
}
