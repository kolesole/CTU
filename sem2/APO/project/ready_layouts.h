/*******************************************************************
  Header file with function to set cells_array after selecting a ready layout
  for game of life on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  ready_layouts.h      - header file with function to set cells_array after selecting a ready layout

 (C) 2024 by Oleksii Kolesnichenko
     e-mail:   kolesole@fel.cvut.cz
     license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#ifndef READY_LAYOUTS_H
#define READY_LAYOUTS_H

#include "cell.h"
//function that calls all functions from this file for creating menu_array
void set_ready_layouts(cell* cells_array[32][48]);
//function that configures cells_array to the glider
void set_glider(cell* cells_array[32][48]);
//function that configures cells_array to the pulsar
void set_pulsar(cell* cells_array[32][48]);
//function that configures cells_array to the spaceship
void set_spaceship(cell* cells_array[32][48]);
//function that configures cells_array to the glider_gun
void set_glider_gun(cell* cells_array[32][48]);

#endif //READY_LAYOUTS_H
