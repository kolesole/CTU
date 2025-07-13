/*******************************************************************
  Header file with function for set menu for game of life on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  menu.h      - header file with function for set menu

 (C) 2024 by Oleksii Kolesnichenko
     e-mail:   kolesole@fel.cvut.cz
     license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#ifndef MENU_H
#define MENU_H

#include "cell.h"
//function that configures menu
void set_menu(cell* cells_array[32][48]);

#endif //MENU_H
