/*******************************************************************
  Header file with functions that perform all related actions with cells
  for game of life on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  cell.h      - header file with functions that perform all related actions with cells

 (C) 2024 by Oleksii Kolesnichenko
     e-mail:   kolesole@fel.cvut.cz
     license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#ifndef CELL_H
#define CELL_H

#include <stdbool.h>
#include <stdlib.h>
#include "knobs.h"
//structure that represents a cell
typedef struct {
    bool live;
    int quantity_of_neighbors;
} cell;
//function that recalculates the number of neighbors of a given cell
void set_cell(cell* cells_array[32][48], int raw, int column);
//function that revives the cell if red switch is pressed
bool cell_birth(unsigned char* spi_mem_base, int cursor_column, int cursor_row, cell* cells_array[32][48]);
//function that kills the cell if blue switch is pressed on cell that is alive
void cell_die(unsigned char* spi_mem_base, int cursor_column, int cursor_row, cell* cells_array[32][48]);
//function that returns true if managed to allocate memory for cells_array otherwise returns false
bool set_start_cells_array(cell* cells_array[32][48]);
//function that revives or kills cells depending on the rules
//rules: 1) if the cell is alive & quantity of neighbors < 2 or > 3 ----> the cell dies
//       2) if the cell is dead & quantity of neighbors = 3 ----> the cell is reborn
void set_cells_array(cell* cells_array[32][48]);
//function that deletes allocated memory for cells_array
void delete_cells_array(cell* cells_array[32][48]);
//function that tracks population growth & returns true if population is growing otherwise returns false
bool get_population_growth(cell* cells_array[32][48], int* num_of_cells);

#endif //CELL_H
