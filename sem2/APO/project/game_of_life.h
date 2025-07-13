/*******************************************************************
  Main header file for game of life on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  game_of_life.h      - main header file

 (C) 2024 by Oleksii Kolesnichenko
     e-mail:   kolesole@fel.cvut.cz
     license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#ifndef GAME_OF_LIFE_H
#define GAME_OF_LIFE_H

#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <bits/types/struct_timespec.h>
#include "mzapo_phys.h"
#include "scene.h"
#include "cell.h"
#include "knobs.h"
#include "cursor.h"

void my_sleep();
//function that allocates all the necessary memory for the game
bool allocate_memory(cell* cells_array[32][48], cell* menu_cells_array[32][48], cell* ready_layouts_cells_array[32][48]);
//function that delete all allocated memory
void delete_allocated_memory(cell* cells_array[32][48], cell* menu_cells_array[32][48], cell* ready_layouts_cells_array[32][48]);
//function that maps to all necessary addresses for the game
bool map_phys_addresses(unsigned char* parlcd_mem_base, unsigned char* spi_mem_base);
//function that displays a menu and updates it
void start_menu_mode(unsigned char* parlcd_mem_base, cell* menu_cells_array[32][48], unsigned char* spi_mem_base, bool* button_play);
//function that displays selection mode and updates it
void start_selection_mode(unsigned char* parlcd_mem_base, cell* cells_array[32][48], unsigned char* spi_mem_base, int* cursor_column, int* cursor_row);
//function that displays play mode and updates it
void start_play_mode(unsigned char* parlcd_mem_base, cell* cells_array[32][48], unsigned char* spi_mem_base, int* cursor_column, int* cursor_row);
//function that displays  ready layouts mode and updates it
void start_ready_layouts_mode(unsigned char* parlcd_mem_base, cell* ready_layouts_array[32][48], unsigned char* spi_mem_base, int* cursor_state);

#endif //GAME_OF_LIFE_H
