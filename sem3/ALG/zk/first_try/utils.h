#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void my_free(int m, int** grid);
bool my_malloc_int(int m, int n, int*** grid);
bool read(int* m, int* n, int*** grid);

#endif //UTILS_H
