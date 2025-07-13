#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "grid.h"

bool read_input(int* N, int* H, int* E, int* S, int* C, int* K, int* M, grid_point*** grid);

#endif //UTILS_H
