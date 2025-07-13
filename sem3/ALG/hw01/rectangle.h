#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <stdbool.h>
//function to calculate the sum in rectangle with certain coordinates
int sum_rectangle(int** aux_matrix, int row1, int col1, int row2, int col2);
//function to calculate the sum of the envelope of a rectangle with certain coordinates
int shell_sum(int** aux_matrix, int row1, int col1, int row2, int col2);

#endif //RECTANGLE_H
