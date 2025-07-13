#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct {
    int indx;
    int colour;
    int* children;
    int num_of_children;
    int size_of_children;
    int cur_score;
    int num_of_unmarked_children;
} node_t;

bool my_malloc_node(node_t** node, int indx);
bool my_realloc_node(node_t** node, int new_size_of_children);
void my_free_node(node_t* node);
bool my_malloc_tree(int N, node_t*** tree);
void my_free_tree(int N, node_t** tree);

#endif //TREE_H
