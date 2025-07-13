#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdbool.h>
//function to allocate memory for int_matrix
bool my_malloc_int_matrix(int rows, int cols, int*** matrix);
//function to free memory for int_matrix
void my_free_int_matrix(int rows, int** matrix);
//function to read input
bool read_input(int* rows, int* cols, int* max_speed, int*** matrix);

#endif //UTILS_H