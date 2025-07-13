/*******************************************************************
  Source file with functions that set scenes for game of life on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  scene.c      - source file with functions that set scenes

 (C) 2024 by Oleksii Kolesnichenko
     e-mail:   kolesole@fel.cvut.cz
     license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#include "scene.h"

void set_loading_scene(unsigned char* parlcd_mem_base, cell* cells_array[32][48]) {
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (int r = 0; r < 32 / 2; r++) {
        for (int c = 0; c < 48 / 2; c++) {
            cells_array[r][c]->live = true;
            cells_array[31 - r][47 - c]->live = true;
            cells_array[31 - r][c]->live = true;
            cells_array[r][47 - c]->live = true;
            for (int row = 0; row < DISPLAY_HEIGHT; row++) {
                for (int column = 0; column < DISPLAY_WIDTH; column++) {
                    if (row % 10 != 0 && column % 10 != 0 && cells_array[row / 10][column / 10]->live) {
                        parlcd_write_data(parlcd_mem_base, RED);
                    }
                    else if (column % 10 == 0 || row % 10 == 0 || row == DISPLAY_HEIGHT - 1 || column == DISPLAY_WIDTH - 1) {
                        parlcd_write_data(parlcd_mem_base, WHITE);
                    } else {
                        parlcd_write_data(parlcd_mem_base, BLACK);
                    }
                }
            }
        }
    }
    for (int row = 0; row < 32; row++) {
        for (int column = 0; column < 48; column++) {
            cells_array[row][column]->live = false;
        }
    }
}

void set_menu_scene(unsigned char* parlcd_mem_base, cell* cells_array[32][48], int* green_knob_last_state, unsigned char* spi_mem_base, bool* button_play) {
    set_menu(cells_array);
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    int green_knob_new_state = (int)green_knob_state(spi_mem_base);
    if (green_knob_new_state != *green_knob_last_state) {
        *button_play = !(*button_play);
    }
    for (int row = 0; row < DISPLAY_HEIGHT; row++) {
        for (int column = 0; column < DISPLAY_WIDTH; column++) {
            if (*button_play) {
                if (row % 10 != 0 && column % 10 != 0 && cells_array[row / 10][column / 10]->live) {
                    parlcd_write_data(parlcd_mem_base, RED);
                }
                else if (column % 10 == 0 || row % 10 == 0 || row == DISPLAY_HEIGHT - 1 || column == DISPLAY_WIDTH - 1
                         || (row / 10 == 3 && column / 10 > 13 && column / 10 < 34)
                         || (column / 10 == 14 && row / 10 > 3 && row / 10 < 12)
                         || (row / 10 == 12 && column / 10 > 13 && column / 10 < 34)
                         || (column / 10 == 33 && row / 10 > 3 && row / 10 < 12)) {
                    parlcd_write_data(parlcd_mem_base, WHITE);
                } else {
                    parlcd_write_data(parlcd_mem_base, BLACK);
                }
            } else {
                if (row % 10 != 0 && column % 10 != 0 && cells_array[row / 10][column / 10]->live) {
                    parlcd_write_data(parlcd_mem_base, RED);
                }
                else if (column % 10 == 0 || row % 10 == 0 || row == DISPLAY_HEIGHT - 1 || column == DISPLAY_WIDTH - 1
                         || (row / 10 == 12 && column / 10 > 9 && column / 10 < 39) ||
                         (column / 10 == 10 && row / 10 > 12 && row / 10 < 28)
                         || (row / 10 == 28 && column / 10 > 9 && column / 10 < 39) ||
                         (column / 10 == 38 && row / 10 > 12 && row / 10 < 28)) {
                    parlcd_write_data(parlcd_mem_base, WHITE);
                } else {
                    parlcd_write_data(parlcd_mem_base, BLACK);
                }
            }
        }
    }
    *green_knob_last_state = green_knob_new_state;
}

void set_ready_layouts_scene(unsigned char* parlcd_mem_base, cell* cells_array[32][48], int* green_knob_last_state, unsigned char* spi_mem_base, int* cursor_state) {
    set_ready_layouts(cells_array);
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    int green_knob_new_state = (int)green_knob_state(spi_mem_base);
    bool overflowing = (*green_knob_last_state > 200 && green_knob_state(spi_mem_base) < 50) || (*green_knob_last_state < 50 && green_knob_state(spi_mem_base) > 200);
    if (!overflowing) {
        if (green_knob_new_state > *green_knob_last_state) {
            *cursor_state = (*cursor_state + 1) % 4;
        } else if (green_knob_new_state < *green_knob_last_state) {
            *cursor_state = (*cursor_state - 1) < 0 ? 3 : (*cursor_state - 1);
        }
    }
    for (int row = 0; row < DISPLAY_HEIGHT; row++) {
        for (int column = 0; column < DISPLAY_WIDTH; column++) {
            if (row % 10 != 0 && column % 10 != 0 && cells_array[row / 10][column / 10]->live) {
                parlcd_write_data(parlcd_mem_base, RED);
            } else if (*cursor_state == 0 &&
                       (column % 10 == 0 || row % 10 == 0 || row == DISPLAY_HEIGHT - 1 || column == DISPLAY_WIDTH - 1
                        || (row / 10 == 0 && column / 10 > -1 && column / 10 < 16)
                        || (column / 10 == 0 && row / 10 > -1 && row / 10 < 16)
                        || (row / 10 == 15 && column / 10 > -1 && column / 10 < 16)
                        || (column / 10 == 15 && row / 10 > -1 && row / 10 < 16))) {
                parlcd_write_data(parlcd_mem_base, WHITE);
            } else if (*cursor_state == 1 &&
                       (column % 10 == 0 || row % 10 == 0 || row == DISPLAY_HEIGHT - 1 || column == DISPLAY_WIDTH - 1
                        || (row / 10 == 0 && column / 10 > 15 && column / 10 < 32)
                        || (column / 10 == 16 && row / 10 > -1 && row / 10 < 16)
                        || (row / 10 == 15 && column / 10 > 15 && column / 10 < 32)
                        || (column / 10 == 31 && row / 10 > -1 && row / 10 < 16))) {
                parlcd_write_data(parlcd_mem_base, WHITE);
            } else if (*cursor_state == 2 &&
                       (column % 10 == 0 || row % 10 == 0 || row == DISPLAY_HEIGHT - 1 || column == DISPLAY_WIDTH - 1
                        || (row / 10 == 0 && column / 10 > 31 && column / 10 < 48)
                        || (column / 10 == 32 && row / 10 > -1 && row / 10 < 16)
                        || (row / 10 == 15 && column / 10 > 31 && column / 10 < 48)
                        || (column / 10 == 47 && row / 10 > -1 && row / 10 < 16))) {
                parlcd_write_data(parlcd_mem_base, WHITE);
            } else if (*cursor_state == 3 &&
                       (column % 10 == 0 || row % 10 == 0 || row == DISPLAY_HEIGHT - 1 || column == DISPLAY_WIDTH - 1
                        || (row / 10 == 16)
                        || (column / 10 == 0 && row / 10 > 15 && row / 10 < 32)
                        || (row / 10 == 31)
                        || (column / 10 == 47 && row / 10 > 15 && row / 10 < 32))) {
                parlcd_write_data(parlcd_mem_base, WHITE);
            } else {
                parlcd_write_data(parlcd_mem_base, BLACK);
            }
        }
    }
    *green_knob_last_state = green_knob_new_state;
}


void set_scene(unsigned char* parlcd_mem_base, cell* cells_array[32][48], int cursor_column, int cursor_row) {
    parlcd_write_cmd(parlcd_mem_base, 0x2c);
    for (int row = 0; row < DISPLAY_HEIGHT; row++) {
        for (int column = 0; column < DISPLAY_WIDTH; column++) {
            if (cursor_column == column/10 && cursor_row == row/10) {
                parlcd_write_data(parlcd_mem_base, YELLOW);
            }
            else if (row % 10 != 0 && column % 10 != 0 && cells_array[row/10][column/10]->live) {
                parlcd_write_data(parlcd_mem_base, RED);
            }
            else if (row % 10 == 0 || column % 10 == 0 || row == DISPLAY_HEIGHT - 1 || column == DISPLAY_WIDTH - 1) {
                parlcd_write_data(parlcd_mem_base, WHITE);
            } else {
                parlcd_write_data(parlcd_mem_base, BLACK);
            }
        }
    }
}