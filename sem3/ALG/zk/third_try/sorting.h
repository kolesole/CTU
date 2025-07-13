#ifndef SORTING_H
#define SORTING_H

#include <stdlib.h>

#include "tree_utils.h"

typedef struct {
    int indx;
    int num_of_children;
} sorted_node_t;

bool my_malloc_sorted_tree(int N, sorted_node_t** sorted_tree);
void my_free_sorted_tree(sorted_node_t* sorted_tree);
int compare(const void* a, const void* b);
bool sort(sorted_node_t** sorted_tree, node_t** tree, int N);

#endif //SORTING_H
