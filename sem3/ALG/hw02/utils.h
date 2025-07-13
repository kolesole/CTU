#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//function to allocate memory for int matrix
bool my_malloc(int rows, int cols, int*** grid);
//function to allocate memory for bool matrix
bool my_malloc_bool(int rows, int cols, bool*** grid);
//function to free memory for int matrix
void my_free_int(int rows, int** grid);
//function to free memory for bool matrix
void my_free_bool(int rows, bool** grid);
//function to read input
bool read_input(int* rows, int* cols, int*** grid, int* num_of_sensors, int** sensor_ranges);

#endif //UTILS_H
