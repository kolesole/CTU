#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// function that represents command from the input
typedef struct {
    int cmd;
    int key;
} cmd_t;

// function to allocate commands array
bool my_malloc_cmds(int num_of_cmds, cmd_t** cmds);
// function to free commands array
void free_cmds(cmd_t* cmds);
// function to read input
bool read_input(int* num_of_cmds, cmd_t** cmds);



#endif //UTILS_H
