#ifndef OAVL_TREE_H
#define OAVL_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "oavl_utils.h"
#include "rotation.h"

extern int num_of_vertices;
extern int num_of_marked_vertices;
extern int num_of_unmarked_vertices;
extern vertex_t* root;
extern bool went_down;

// function to insert vertex
bool insert_vertex(int key);
// function to delete vertex
void delete_vertex(int key);
// function to balance the tree
bool try_balance(vertex_t* vertex, int path[2]);
// function to try to move down vertex
void try_move_down(vertex_t* vertex);

#endif //OAVL_TREE_H
