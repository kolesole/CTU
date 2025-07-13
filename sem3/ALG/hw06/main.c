#include <stdio.h>

#include "utils.h"
#include "oavl_utils.h"
#include "oavl_tree.h"

int num_of_vertices = 0;                       // number of all vertices
int num_of_marked_vertices = 0;                // number of marked vertices
int num_of_unmarked_vertices = 0;              // number of unmarked vertices
vertex_t* root = NULL;                         // tree root
bool went_down;

int main() {
    int num_of_cmds;
    cmd_t* cmds;
    if (!read_input(&num_of_cmds, &cmds)) return -1;

    for (int i = 0; i < num_of_cmds; i++) {
        cmd_t cmd = cmds[i];
        switch (cmd.cmd) {
            case 1:
                went_down = false;
                insert_vertex(cmd.key);
                break;
            case 2:
                delete_vertex(cmd.key);
                break;
            default:
                break;
        }
    }

    printf("%d %d %d\n", root->depth, num_of_vertices - num_of_unmarked_vertices, num_of_unmarked_vertices);

    free_cmds(cmds);
    free_tree(root);

    return 0;
}
