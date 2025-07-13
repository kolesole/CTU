#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

extern int N;
extern int DH;
extern int H1;
extern int H2;

// function to allocate memory for int grid
bool my_malloc_int_grid(int*** grid);
// function to free memory for int grid
void my_free_int_grid(int** grid);
// function to read input
bool read_input(int*** grid);

#endif //UTILS_H
