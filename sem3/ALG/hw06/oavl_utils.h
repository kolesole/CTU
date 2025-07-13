#ifndef OAVL_UTILS_H
#define OAVL_UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// structure that represents vertex
typedef struct vertex_t {
    int key;
    int left_depth, right_depth;
    int depth;
    bool is_marked;
    struct vertex_t* left;
    struct vertex_t* right;
    struct vertex_t* parent;
} vertex_t;

// function to create new vertex
bool create_new_vertex(vertex_t** vertex, int key);
// function to free vertex
void free_vertex(vertex_t* vertex);
//function to free tree
void free_tree(vertex_t* root);

#endif //OAVL_UTILS_H
