#ifndef READ_H
#define READ_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#include "tree.h"

//function to read input
bool read_input(int* size, node_t*** tree, int** blue_counters);

#endif //READ_H
