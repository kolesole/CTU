/*******************************************************************
  Source file with function to set cells_array after selecting a ready layout
  for game of life on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  ready_layouts.c      - source file with function to set cells_array after selecting a ready layout

 (C) 2024 by Oleksii Kolesnichenko
     e-mail:   kolesole@fel.cvut.cz
     license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#include "ready_layouts.h"

void set_ready_layouts(cell* cells_array[32][48]) {
    set_glider(cells_array);
    set_pulsar(cells_array);
    set_spaceship(cells_array);
    set_glider_gun(cells_array);
}

void set_glider(cell* cells_array[32][48]) {
    cells_array[2][1]->live = true;
    cells_array[3][2]->live = true;
    cells_array[1][3]->live = true;
    cells_array[2][3]->live = true;
    cells_array[3][3]->live = true;
}

void set_pulsar(cell* cells_array[32][48]) {
    cells_array[1][19]->live = true;
    cells_array[1][20]->live = true;
    cells_array[1][21]->live = true;
    cells_array[3][17]->live = true;
    cells_array[4][17]->live = true;
    cells_array[5][17]->live = true;
    cells_array[6][19]->live = true;
    cells_array[6][20]->live = true;
    cells_array[6][21]->live = true;
    cells_array[3][22]->live = true;
    cells_array[4][22]->live = true;
    cells_array[5][22]->live = true;

    cells_array[8][19]->live = true;
    cells_array[8][20]->live = true;
    cells_array[8][21]->live = true;
    cells_array[9][17]->live = true;
    cells_array[10][17]->live = true;
    cells_array[11][17]->live = true;
    cells_array[13][19]->live = true;
    cells_array[13][20]->live = true;
    cells_array[13][21]->live = true;
    cells_array[11][22]->live = true;
    cells_array[10][22]->live = true;
    cells_array[9][22]->live = true;

    cells_array[1][27]->live = true;
    cells_array[1][26]->live = true;
    cells_array[1][25]->live = true;
    cells_array[3][24]->live = true;
    cells_array[4][24]->live = true;
    cells_array[5][24]->live = true;
    cells_array[6][25]->live = true;
    cells_array[6][26]->live = true;
    cells_array[6][27]->live = true;
    cells_array[5][29]->live = true;
    cells_array[4][29]->live = true;
    cells_array[3][29]->live = true;

    cells_array[8][25]->live = true;
    cells_array[8][26]->live = true;
    cells_array[8][27]->live = true;
    cells_array[9][24]->live = true;
    cells_array[10][24]->live = true;
    cells_array[11][24]->live = true;
    cells_array[13][25]->live = true;
    cells_array[13][26]->live = true;
    cells_array[13][27]->live = true;
    cells_array[11][29]->live = true;
    cells_array[10][29]->live = true;
    cells_array[9][29]->live = true;
}

void set_spaceship(cell* cells_array[32][48]) {
    cells_array[3][33]->live = true;
    cells_array[4][33]->live = true;

    cells_array[3][34]->live = true;
    cells_array[4][34]->live = true;
    cells_array[5][34]->live = true;

    cells_array[3][35]->live = true;
    cells_array[4][35]->live = true;
    cells_array[5][35]->live = true;

    cells_array[3][36]->live = true;
    cells_array[4][36]->live = true;
    cells_array[5][36]->live = true;

    cells_array[2][37]->live = true;
    cells_array[4][37]->live = true;
    cells_array[5][37]->live = true;

    cells_array[2][38]->live = true;
    cells_array[3][38]->live = true;
    cells_array[4][38]->live = true;

    cells_array[3][39]->live = true;
}

void set_glider_gun(cell* cells_array[32][48]) {
    cells_array[25][1]->live = true;
    cells_array[26][1]->live = true;
    cells_array[25][2]->live = true;
    cells_array[26][2]->live = true;

    cells_array[25][11]->live = true;
    cells_array[26][11]->live = true;
    cells_array[27][11]->live = true;

    cells_array[24][12]->live = true;
    cells_array[28][12]->live = true;

    cells_array[23][13]->live = true;
    cells_array[29][13]->live = true;

    cells_array[23][14]->live = true;
    cells_array[29][14]->live = true;

    cells_array[26][15]->live = true;

    cells_array[24][16]->live = true;
    cells_array[28][16]->live = true;

    cells_array[25][17]->live = true;
    cells_array[26][17]->live = true;
    cells_array[27][17]->live = true;

    cells_array[26][18]->live = true;

    cells_array[23][21]->live = true;
    cells_array[24][21]->live = true;
    cells_array[25][21]->live = true;

    cells_array[23][22]->live = true;
    cells_array[24][22]->live = true;
    cells_array[25][22]->live = true;

    cells_array[22][23]->live = true;
    cells_array[26][23]->live = true;

    cells_array[21][25]->live = true;
    cells_array[22][25]->live = true;
    cells_array[26][25]->live = true;
    cells_array[27][25]->live = true;

    cells_array[23][35]->live = true;
    cells_array[24][35]->live = true;

    cells_array[23][36]->live = true;
    cells_array[24][36]->live = true;
}


