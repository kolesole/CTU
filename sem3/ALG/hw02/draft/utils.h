#ifndef READ_H
#define READ_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

bool my_malloc(int rows, int cols, int*** grid);
void my_free_int(int rows, int** grid);
bool read_input(int* rows, int* cols, int*** grid, int* num_of_sensors, int** sensor_ranges);

#endif //READ_H
