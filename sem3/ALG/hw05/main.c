#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "utils.h"
#include "bvs_tree.h"

int num_of_del_nodes = 0;        //global variable to count the number of deleted nodes
int depth_of_del_nodes = 0;      //global variable to count the number of depths of deleted nodes
int num_of_undel_nodes = 0;      //global variable to count the number of undeleted nodes
int depth_of_undel_nodes = 0;    //global variable to count the number of depths of undeleted nodes
int cur_depth = 0;               //global variable to count the depth from root to leaves

int main() {
    int num_of_cmds;
    input_array_node** input_array;
    if (!read_input(&num_of_cmds, &input_array)) return -1;

    node_t* root = NULL;

    int num_of_compacts = 0;
    for (int i = 0; i < num_of_cmds; i++) {
        if (strcmp(input_array[i]->cmd, "ins") == 0) {
            node_t* new_node;
            if (!create_new_node(&new_node, input_array[i]->num)) break;
            insert_node(&root, new_node);

            if (abs(depth_of_del_nodes - num_of_del_nodes * cur_depth) >
                abs(depth_of_undel_nodes - num_of_undel_nodes * cur_depth)) {
                node_t* new_root = NULL;
                compact_tree(root, &new_root);
                root = new_root;
                num_of_compacts++;
            }
        }

        else if (strcmp(input_array[i]->cmd, "del") == 0) {
            delete_node(root, input_array[i]->num);

            if (abs(depth_of_del_nodes - num_of_del_nodes * cur_depth) >
                abs(depth_of_undel_nodes - num_of_undel_nodes * cur_depth)) {
                node_t* new_root = NULL;
                compact_tree(root, &new_root);
                root = new_root;
                num_of_compacts++;
            }
        }
    }

    printf("%d %d\n", num_of_compacts, cur_depth);

    free_tree(root);
    free_input_array(num_of_cmds, input_array);
    return 0;
}