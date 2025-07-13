#ifndef BVS_TREE_H
#define BVS_TREE_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

//structure for representing a tree node
typedef struct node_t {
    int num;
    bool is_deleted;
    struct node_t* left;
    struct node_t* right;
} node_t;

extern int num_of_del_nodes;
extern int depth_of_del_nodes;
extern int num_of_undel_nodes;
extern int depth_of_undel_nodes;
extern int cur_depth;

//function to create a new node
bool create_new_node(node_t** node, int num);
//function to free memory for tree
void free_tree(node_t* root);
//function to insert a new node
void insert_node(node_t** root, node_t* new_node);
//function to mark a node, that its deleted
void delete_node(node_t* root, int num);
//function to compact tree
void compact_tree(node_t* root, node_t** new_root);
//help dfs function
void dfs(node_t* root, node_t** new_root);

#endif //BVS_TREE_H
