#ifndef TREE_H
#define TREE_H

#include <stdio.h>
#include <stdlib.h>

//node structure
typedef struct node_t {
    struct node_t* left_child;
    struct node_t* right_child;
    int color;
} node_t;

//function to create node
node_t* create_node(int color);
//function to connect nodes
node_t* create_tree(node_t** tree, int size, int index_in_array, int** blue_counters);
//function to free memory
void free_tree_from_array(node_t** tree, int size);

#endif //TREE_H
