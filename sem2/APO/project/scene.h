/*******************************************************************
  Header file with functions that set scenes for game of life on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  scene.h      - header file with functions that set scenes

 (C) 2024 by Oleksii Kolesnichenko
     e-mail:   kolesole@fel.cvut.cz
     license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#ifndef SCENE_H
#define SCENE_H

#include <stdbool.h>
#include "mzapo_parlcd.h"
#include "menu.h"
#include "ready_layouts.h"
#include "cell.h"
#include "cursor.h"
#include "knobs.h"

#define DISPLAY_WIDTH 480
#define DISPLAY_HEIGHT 320
#define WHITE 0xFFFF
#define BLACK 0x0000
#define RED 0xF800
#define YELLOW 0xFFE0
//function that turns on the loading screen
void set_loading_scene(unsigned char* parlcd_mem_base, cell* cells_array[32][48]);
//function that turns on the menu
void set_menu_scene(unsigned char* parlcd_mem_base, cell* cells_array[32][48], int* green_knob_last_state, unsigned char* spi_mem_base, bool* button_play);
//function that turns on the ready layouts
void set_ready_layouts_scene(unsigned char* parlcd_mem_base, cell* cells_array[32][48], int* green_knob_last_state, unsigned char* spi_mem_base, int* cursor_state);
//function that sets up the scene during the game
void set_scene(unsigned char* parlcd_mem_base, cell* cells_array[32][48], int cursor_column, int cursor_row);

#endif //SCENE_H
