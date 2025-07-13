#include "utils.h"

#include <stdlib.h>

bool malloc_input_array(int num_of_cmds, input_array_node*** input_array) {
    *input_array = (input_array_node**)malloc(num_of_cmds * sizeof(input_array_node*));
    if (*input_array == NULL) {
        fprintf(stderr, "ERROR: cannot allocate memory for input array!\n");
        return false;
    }

    for (int i = 0; i < num_of_cmds; i++) {
        (*input_array)[i] = (input_array_node*)malloc(num_of_cmds * sizeof(input_array_node));
        if ((*input_array)[i] == NULL) {
            fprintf(stderr, "ERROR: cannot allocate memory for input array!\n");
            free_input_array(i, *input_array);
            return false;
        }
    }

    return true;
}

bool read_input(int* num_of_cmds, input_array_node*** input_array) {
    if (scanf("%d", num_of_cmds) != 1) {
        fprintf(stderr, "ERROR: cannot read number of commands!\n");
        return false;
    }

    if (!malloc_input_array(*num_of_cmds, input_array)) return false;

    for (int i = 0; i < *num_of_cmds; i++) {
        if (scanf("%s %d", (*input_array)[i]->cmd, &(*input_array)[i]->num) != 2) {
            fprintf(stderr, "ERROR: cannot read command!\n");
            free_input_array(*num_of_cmds, *input_array);
            return false;
        }
    }

    return true;
}

void free_input_array(int num_of_cmds, input_array_node** input_array) {
    for (int i = 0; i < num_of_cmds; i++) {
        free(input_array[i]);
    }

    free(input_array);
}