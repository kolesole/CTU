#include "read.h"

bool read_input(int* size, node_t*** tree, int** blue_counters) {
    if (scanf("%d", size) != 1) {
        fprintf(stderr, "Error: cannot read size!\n");
        return false;
    }

    *tree = (node_t**)malloc(*size * sizeof(node_t*));
    if (*tree == NULL) {
        fprintf(stderr, "Error: cannot allocate memory!\n");
        return false;
    }

    *blue_counters = (int*)malloc(*size * sizeof(int));
    if (*blue_counters == NULL) {
        free(*tree);
        fprintf(stderr, "Error: cannot allocate memory!\n");
        return false;
    }

    int blue_counter = 0;
    for (int i = 0; i < *size; i++) {
        int color;
        if (scanf("%d", &color) != 1) {
            fprintf(stderr, "Error: cannot read tree node color!\n");
            free_tree_from_array(*tree, i);
            free(*blue_counters);
            return false;
        }

        (*tree)[i] = create_node(color);
        if ((*tree)[i] == NULL) {
            free_tree_from_array(*tree, i);
            return false;
        }

        if (color == 2) blue_counter++;

        (*blue_counters)[i] = blue_counter;
    }

    return true;
}
