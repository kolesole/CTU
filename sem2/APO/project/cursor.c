/*******************************************************************
  Source file with function to determine the location of the cursor for game of life on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  cursor.c      - source file with function to determine the location of the cursor

 (C) 2024 by Oleksii Kolesnichenko
     e-mail:   kolesole@fel.cvut.cz
     license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#include "cursor.h"

void set_cursor(unsigned char* spi_mem_base, int* cursor_column, int* cursor_row, int* red_knob_last_state, int* blue_knob_last_state) {
    cursor_horizontal_movement(spi_mem_base, cursor_column, red_knob_last_state);
    cursor_vertical_movement(spi_mem_base, cursor_row, blue_knob_last_state);
}

void cursor_horizontal_movement(unsigned char* spi_mem_base, int* cursor_column, int* red_knob_last_state) {
    bool overflowing = (*red_knob_last_state > 200 && red_knob_state(spi_mem_base) < 50) || (*red_knob_last_state < 50 && red_knob_state(spi_mem_base) > 200);
    if (!overflowing) {
        if (red_knob_state(spi_mem_base) + 1 < *red_knob_last_state) {
            *cursor_column = (*cursor_column - 1 + 48) % 48;
        }
        else if (red_knob_state(spi_mem_base) > *red_knob_last_state + 1) {
            *cursor_column = (*cursor_column + 1) % 48;
        }
    }
    *red_knob_last_state = (int)red_knob_state(spi_mem_base);
}

void cursor_vertical_movement(unsigned char* spi_mem_base, int* cursor_row, int* blue_knob_last_state) {
    bool overflowing = (*blue_knob_last_state > 200 && blue_knob_state(spi_mem_base) < 50) || (*blue_knob_last_state < 50 && blue_knob_state(spi_mem_base) > 200);
    if (!overflowing) {
        if (blue_knob_state(spi_mem_base) + 1 < *blue_knob_last_state) {
            *cursor_row = (*cursor_row - 1 + 32) % 32;
        }
        else if (blue_knob_state(spi_mem_base) > *blue_knob_last_state + 1) {
            *cursor_row = (*cursor_row + 1) % 32;
        }
    }
    *blue_knob_last_state = (int)blue_knob_state(spi_mem_base);
}
