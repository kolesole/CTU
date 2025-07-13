/*******************************************************************
  Source file with functions that perform all related actions with cells
  for game of life on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  cell.c      - source file with functions that perform all related actions with cells

 (C) 2024 by Oleksii Kolesnichenko
     e-mail:   kolesole@fel.cvut.cz
     license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#include "cell.h"

void set_cell(cell* cells_array[32][48], int raw, int column) {
    for (int r = raw - 1; r <= raw + 1; r++) {
        for (int c = column - 1; c <= column + 1; c++) {
            if (r == raw && c == column) continue;
            int r_wrap = (r + 32) % 32;
            int c_wrap = (c + 48) % 48;
            if (cells_array[r_wrap][c_wrap]->live) {
                cells_array[raw][column]->quantity_of_neighbors++;
            }
        }
    }
}

bool cell_birth(unsigned char* spi_mem_base, int cursor_column, int cursor_row, cell* cells_array[32][48]) {
    if (red_button_state(spi_mem_base) == 1) {
        cells_array[cursor_row][cursor_column]->live = true;
        return true;
    }
    return false;
}

void cell_die(unsigned char* spi_mem_base, int cursor_column, int cursor_row, cell* cells_array[32][48]) {
    if (blue_button_state(spi_mem_base) == 1) {
        cells_array[cursor_row][cursor_column]->live = false;
    }
}

bool set_start_cells_array(cell* cells_array[32][48]) {
    for (int raw = 0; raw < 32; raw++) {
        for (int column = 0; column < 48; column++) {
            cells_array[raw][column] = (cell*)malloc(sizeof(cell));
            if (cells_array[raw][column] == NULL) {
                for (int r = 0; r < raw; r++) {
                    for (int c = 0; c < column; c++) {
                        free (cells_array[r][c]);
                    }
                }
                return false;
            }
            cells_array[raw][column]->quantity_of_neighbors = 0;
            cells_array[raw][column]->live = false;
        }
    }
    return true;
}

void set_cells_array(cell* cells_array[32][48]) {
    for (int raw = 0; raw < 32; raw++) {
        for (int column = 0; column < 48; column++) {
            cells_array[raw][column]->quantity_of_neighbors = 0;
            set_cell(cells_array, raw, column);
        }
    }
    for (int raw = 0; raw < 32; raw++) {
        for (int column = 0; column < 48; column++) {
            if (cells_array[raw][column]->live && (cells_array[raw][column]->quantity_of_neighbors < 2 || cells_array[raw][column]->quantity_of_neighbors > 3)) cells_array[raw][column]->live = false;
            else if (!cells_array[raw][column]->live && (cells_array[raw][column]->quantity_of_neighbors == 3)) cells_array[raw][column]->live = true;
        }
    }
}

bool get_population_growth(cell* cells_array[32][48], int* num_of_cells) {
    int new_num_of_cells = 0;
    for (int row = 0; row < 32; row++) {
        for (int column = 0; column < 48; column++) {
            if (cells_array[row][column]->live) new_num_of_cells++;
        }
    }
    bool ret = new_num_of_cells >= *num_of_cells;
    *num_of_cells = new_num_of_cells;
    return ret;
}

void delete_cells_array(cell* cells_array[32][48]) {
    for (int raw = 0; raw < 32; raw++) {
        for (int column = 0; column < 48; column++) {
            free(cells_array[raw][column]);
        }
    }
}

