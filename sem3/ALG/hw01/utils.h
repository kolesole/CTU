#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
//struct that represents a cell in an aux zero matrix
typedef struct {
    bool is_inside_zero_sector;

    int zero_sector_col;

    int inside_zero_counter, hor_zero_counter, vert_zero_counter;
} matrix_element;
//function that allocates a matrix of int type
bool my_malloc_int(int rows, int cols, int*** matrix);
//function that allocates a matrix of bool type
bool my_malloc_bool(int rows, int cols, bool*** matrix);
//function that allocates an aux zero matrix
bool my_malloc_aux_zero_matrix(int rows, int cols, matrix_element*** matrix);
//function that frees up memory(int type)
void my_free_int(int rows, int*** matrix);
//function that frees up memory(bool type)
void my_free_bool(int rows, bool*** matrix);
//function that frees up memory(aux zero matrix)
void my_free_zero_matrix(int rows, matrix_element*** matrix);
//function to read input and to allocate memory for start matrix
bool allocate_and_read(int* rows, int* cols, int*** matrix);

#endif //UTILS_H
