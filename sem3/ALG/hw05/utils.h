#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>

//structure to save information about cmd
typedef struct {
    char cmd[4];
    int num;
} input_array_node;

//function to allocate memory for input array
bool malloc_input_array(int num_of_cmds, input_array_node*** input_array);
//function to read input
bool read_input(int* num_of_cmds, input_array_node*** input_array);
//function to free memory for input array
void free_input_array(int num_of_cmds, input_array_node** input_array);

#endif //UTILS_H
