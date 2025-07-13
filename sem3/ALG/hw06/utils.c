#include "utils.h"

bool my_malloc_cmds(int num_of_cmds, cmd_t** cmds) {
    *cmds = (cmd_t*)malloc(num_of_cmds * sizeof(cmd_t));
    if (*cmds == NULL) {
        fprintf(stderr, "ERROR: Cannot allocate memory!\n");
        return false;
    }

    return true;
}

void free_cmds(cmd_t* cmds) {
    free(cmds);
}

bool read_input(int* num_of_cmds, cmd_t** cmds) {
    if (scanf("%d", num_of_cmds) != 1) {
        fprintf(stderr, "ERROR: Cannot read number of commands!\n");
        return false;
    }

    if (!my_malloc_cmds(*num_of_cmds, cmds)) return false;

    for (int i = 0; i < *num_of_cmds; i++) {
        if (scanf("%d %d", &(*cmds)[i].cmd, &(*cmds)[i].key) != 2) {
            fprintf(stderr, "ERROR: Cannot read command!\n");
            free_cmds(*cmds);
            return false;
        }
    }

    return true;
}
