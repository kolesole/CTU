/*******************************************************************
  Header file with function to determine the location of the cursor for game of life on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  cursor.h      - header file with function to determine the location of the cursor

 (C) 2024 by Oleksii Kolesnichenko
     e-mail:   kolesole@fel.cvut.cz
     license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#ifndef CURSOR_H
#define CURSOR_H

#include <stdbool.h>
#include "knobs.h"
//function that calls a functions cursor_horizontal_movement(------//------) & cursor_vertical_movement(------//------)
void set_cursor(unsigned char* spi_mem_base, int* cursor_column, int* cursor_row, int* red_knob_last_state, int* blue_knob_last_state);
//function that adjusts the horizontal cursor position depending on the position of the red switch
void cursor_horizontal_movement(unsigned char* spi_mem_base, int* cursor_column, int* red_knob_last_state);
//function that adjusts the vertical cursor position depending on the position of the blue switch
void cursor_vertical_movement(unsigned char* spi_mem_base, int* cursor_row, int* blue_knob_last_state);

#endif //CURSOR_H
