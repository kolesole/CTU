/*******************************************************************
  Source file with function for set menu for game of life on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  menu.c      - source file with function for set menu

 (C) 2024 by Oleksii Kolesnichenko
     e-mail:   kolesole@fel.cvut.cz
     license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#include "menu.h"

void set_menu(cell* cells_array[32][48]) {
    //PLAY****************************************************************
    //P
    cells_array[5][16]->live = true;
    cells_array[6][16]->live = true;
    cells_array[7][16]->live = true;
    cells_array[8][16]->live = true;
    cells_array[9][16]->live = true;
    cells_array[10][16]->live = true;
    cells_array[5][17]->live = true;
    cells_array[5][18]->live = true;
    cells_array[6][19]->live = true;
    cells_array[7][17]->live = true;
    cells_array[7][18]->live = true;
    //L
    cells_array[5][20]->live = true;
    cells_array[6][20]->live = true;
    cells_array[7][20]->live = true;
    cells_array[8][20]->live = true;
    cells_array[9][20]->live = true;
    cells_array[10][20]->live = true;
    cells_array[10][21]->live = true;
    cells_array[10][22]->live = true;
    //A
    cells_array[6][23]->live = true;
    cells_array[7][23]->live = true;
    cells_array[8][23]->live = true;
    cells_array[9][23]->live = true;
    cells_array[10][23]->live = true;
    cells_array[5][24]->live = true;
    cells_array[5][25]->live = true;
    cells_array[8][24]->live = true;
    cells_array[8][25]->live = true;
    cells_array[6][26]->live = true;
    cells_array[7][26]->live = true;
    cells_array[8][26]->live = true;
    cells_array[9][26]->live = true;
    cells_array[10][26]->live = true;
    //Y
    cells_array[5][27]->live = true;
    cells_array[6][28]->live = true;
    cells_array[7][29]->live = true;
    cells_array[8][29]->live = true;
    cells_array[9][29]->live = true;
    cells_array[10][29]->live = true;
    cells_array[6][30]->live = true;
    cells_array[5][31]->live = true;
//READY***************************************************************
    //R
    cells_array[14][14]->live = true;
    cells_array[15][14]->live = true;
    cells_array[16][14]->live = true;
    cells_array[17][14]->live = true;
    cells_array[18][14]->live = true;
    cells_array[19][14]->live = true;
    cells_array[14][15]->live = true;
    cells_array[14][16]->live = true;
    cells_array[15][17]->live = true;
    cells_array[16][16]->live = true;
    cells_array[16][15]->live = true;
    cells_array[17][15]->live = true;
    cells_array[18][16]->live = true;
    cells_array[19][17]->live = true;
    //E
    cells_array[14][18]->live = true;
    cells_array[14][19]->live = true;
    cells_array[14][20]->live = true;
    cells_array[14][21]->live = true;
    cells_array[15][18]->live = true;
    cells_array[16][18]->live = true;
    cells_array[17][18]->live = true;
    cells_array[18][18]->live = true;
    cells_array[19][18]->live = true;
    cells_array[16][19]->live = true;
    cells_array[16][20]->live = true;
    cells_array[16][21]->live = true;
    cells_array[16][22]->live = true;
    /*cells_array[14][19]->live = true;
    cells_array[14][20]->live = true;*/
    cells_array[19][19]->live = true;
    cells_array[19][20]->live = true;
    cells_array[19][21]->live = true;
    //A
    cells_array[14][23]->live = true;
    cells_array[14][24]->live = true;
    cells_array[15][22]->live = true;
    cells_array[16][22]->live = true;
    cells_array[17][22]->live = true;
    cells_array[18][22]->live = true;
    cells_array[19][22]->live = true;
    cells_array[17][23]->live = true;
    cells_array[17][24]->live = true;
    cells_array[15][25]->live = true;
    cells_array[16][25]->live = true;
    cells_array[17][25]->live = true;
    cells_array[18][25]->live = true;
    cells_array[19][25]->live = true;
    //D
    cells_array[14][26]->live = true;
    cells_array[15][26]->live = true;
    cells_array[16][26]->live = true;
    cells_array[17][26]->live = true;
    cells_array[18][26]->live = true;
    cells_array[19][26]->live = true;
    cells_array[14][27]->live = true;
    cells_array[14][28]->live = true;
    cells_array[15][29]->live = true;
    cells_array[16][29]->live = true;
    cells_array[17][29]->live = true;
    cells_array[18][29]->live = true;
    cells_array[19][28]->live = true;
    cells_array[19][27]->live = true;
    //Y
    cells_array[14][30]->live = true;
    cells_array[15][31]->live = true;
    cells_array[16][32]->live = true;
    cells_array[17][32]->live = true;
    cells_array[18][32]->live = true;
    cells_array[19][32]->live = true;
    cells_array[15][33]->live = true;
    cells_array[14][34]->live = true;
//LAYOUT***************************************************************
    //L
    cells_array[21][12]->live = true;
    cells_array[22][12]->live = true;
    cells_array[23][12]->live = true;
    cells_array[24][12]->live = true;
    cells_array[25][12]->live = true;
    cells_array[26][12]->live = true;
    cells_array[26][13]->live = true;
    cells_array[26][14]->live = true;
    //A
    cells_array[26][15]->live = true;
    cells_array[25][15]->live = true;
    cells_array[24][15]->live = true;
    cells_array[23][15]->live = true;
    cells_array[22][15]->live = true;
    cells_array[21][16]->live = true;
    cells_array[21][17]->live = true;
    cells_array[24][16]->live = true;
    cells_array[24][17]->live = true;
    cells_array[26][18]->live = true;
    cells_array[25][18]->live = true;
    cells_array[24][18]->live = true;
    cells_array[23][18]->live = true;
    cells_array[22][18]->live = true;
    //Y
    cells_array[21][19]->live = true;
    cells_array[22][20]->live = true;
    cells_array[23][21]->live = true;
    cells_array[24][21]->live = true;
    cells_array[25][21]->live = true;
    cells_array[26][21]->live = true;
    cells_array[22][22]->live = true;
    cells_array[21][23]->live = true;
    //O
    cells_array[22][24]->live = true;
    cells_array[23][24]->live = true;
    cells_array[24][24]->live = true;
    cells_array[25][24]->live = true;
    cells_array[26][25]->live = true;
    cells_array[26][26]->live = true;
    cells_array[25][27]->live = true;
    cells_array[24][27]->live = true;
    cells_array[23][27]->live = true;
    cells_array[22][27]->live = true;
    cells_array[21][26]->live = true;
    cells_array[21][25]->live = true;
    //U
    cells_array[21][28]->live = true;
    cells_array[22][28]->live = true;
    cells_array[23][28]->live = true;
    cells_array[24][28]->live = true;
    cells_array[25][28]->live = true;
    cells_array[26][29]->live = true;
    cells_array[26][30]->live = true;
    cells_array[25][31]->live = true;
    cells_array[24][31]->live = true;
    cells_array[23][31]->live = true;
    cells_array[22][31]->live = true;
    cells_array[21][31]->live = true;
    //T
    cells_array[21][32]->live = true;
    cells_array[21][33]->live = true;
    cells_array[21][34]->live = true;
    cells_array[21][35]->live = true;
    cells_array[21][36]->live = true;
    cells_array[22][34]->live = true;
    cells_array[23][34]->live = true;
    cells_array[24][34]->live = true;
    cells_array[25][34]->live = true;
    cells_array[26][34]->live = true;
//*********************************************************************
}
