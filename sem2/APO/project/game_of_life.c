/*******************************************************************
  Main source file for game of life on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  game_of_life.c      - main fsource ile

 (C) 2024 by Oleksii Kolesnichenko
     e-mail:   kolesole@fel.cvut.cz
     license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#include "game_of_life.h"

int main(int argc, char *argv[]) {
    cell* cells_array[32][48];
    cell* menu_cells_array[32][48];
    cell* ready_layouts_cells_array[32][48];
    if (!allocate_memory(cells_array, menu_cells_array, ready_layouts_cells_array)) {
        exit(-1);
    }

    unsigned char* parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    unsigned char* spi_mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    if (!map_phys_addresses(parlcd_mem_base, spi_mem_base)) {
        delete_allocated_memory(cells_array, menu_cells_array, ready_layouts_cells_array);
        exit(-1);
    }

    set_loading_scene(parlcd_mem_base, menu_cells_array);

    while (1) {
        bool button_play = true;
        go_out_rgb1(spi_mem_base);
        go_out_rgb2(spi_mem_base);
        go_out_led_line(spi_mem_base);
        start_menu_mode(parlcd_mem_base, menu_cells_array, spi_mem_base, &button_play);
        if (button_play) {
            my_sleep();
            delete_cells_array(cells_array);
            if (!set_start_cells_array(cells_array)) {
                delete_allocated_memory(cells_array, menu_cells_array, ready_layouts_cells_array);
                fprintf(stderr, "ERROR: cannot allocate memory!\n");
                exit(-1);
            }
            int cursor_column = 0;
            int cursor_row = 0;
            start_selection_mode(parlcd_mem_base, cells_array, spi_mem_base, &cursor_column, &cursor_row);
            my_sleep();
            start_play_mode(parlcd_mem_base, cells_array, spi_mem_base, &cursor_column, &cursor_row);
        }
        else if (!button_play) {
            delete_cells_array(cells_array);
            if (!set_start_cells_array(cells_array)) {
                delete_allocated_memory(cells_array, menu_cells_array, ready_layouts_cells_array);
                fprintf(stderr, "ERROR: cannot allocate memory!\n");
                exit(-1);
            }
            my_sleep();
            int cursor_state = 0;
            start_ready_layouts_mode(parlcd_mem_base, ready_layouts_cells_array, spi_mem_base, &cursor_state);
            switch (cursor_state) {
                case 0:
                    set_glider(cells_array);
                    break;
                case 1:
                    set_pulsar(cells_array);
                    break;
                case 2:
                    set_spaceship(cells_array);
                    break;
                case 3:
                    set_glider_gun(cells_array);
                    break;
            }
            my_sleep();
            int cursor_column = 0;
            int cursor_row = 0;
            start_play_mode(parlcd_mem_base, cells_array, spi_mem_base, &cursor_column, &cursor_row);
        }
        my_sleep();
    }
}

void my_sleep() {
    struct timespec ts;
    ts.tv_sec = 0;
    ts.tv_nsec = 350000000;
    nanosleep(&ts, NULL);
}

bool allocate_memory(cell* cells_array[32][48], cell* menu_cells_array[32][48], cell* ready_layouts_cells_array[32][48]) {
    if (!set_start_cells_array(cells_array)) {
        fprintf(stderr, "ERROR: cannot allocate memory!\n");
        return false;
    }

    if (!set_start_cells_array(menu_cells_array)) {
        delete_cells_array(cells_array);
        fprintf(stderr, "ERROR: cannot allocate memory!\n");
        return false;
    }

    if (!set_start_cells_array(ready_layouts_cells_array)) {
        delete_cells_array(cells_array);
        delete_cells_array(menu_cells_array);
        fprintf(stderr, "ERROR: cannot allocate memory!\n");
        return false;
    }
    return true;
}

void delete_allocated_memory(cell* cells_array[32][48], cell* menu_cells_array[32][48], cell* ready_layouts_cells_array[32][48]) {
    delete_cells_array(cells_array);
    delete_cells_array(menu_cells_array);
    delete_cells_array(ready_layouts_cells_array);
}

bool map_phys_addresses(unsigned char* parlcd_mem_base, unsigned char* spi_mem_base) {
    parlcd_hx8357_init(parlcd_mem_base);
    parlcd_mem_base = map_phys_address(PARLCD_REG_BASE_PHYS, PARLCD_REG_SIZE, 0);
    if (parlcd_mem_base == NULL) {
        fprintf(stderr, "ERROR: cannot map LCD physical address to memory!\n");
        return false;
    }

    spi_mem_base = map_phys_address(SPILED_REG_BASE_PHYS, SPILED_REG_SIZE, 0);
    if (spi_mem_base == NULL) {
        fprintf(stderr, "ERROR: cannot map SPI physical address to memory!\n");
        return false;
    }
    return true;
}

void start_menu_mode(unsigned char* parlcd_mem_base, cell* menu_cells_array[32][48], unsigned char* spi_mem_base, bool* button_play) {
    int green_knob_last_state = (int)green_knob_state(spi_mem_base);
    while (green_button_state(spi_mem_base) != 1) {
        my_sleep();
        set_menu_scene(parlcd_mem_base, menu_cells_array, &green_knob_last_state, spi_mem_base, button_play);
    }
}

void start_selection_mode(unsigned char* parlcd_mem_base, cell* cells_array[32][48], unsigned char* spi_mem_base, int* cursor_column, int* cursor_row) {
    int red_knob_last_state = (int)red_knob_state(spi_mem_base);
    int blue_knob_last_state = (int)blue_knob_state(spi_mem_base);
    go_out_rgb1(spi_mem_base);
    go_out_rgb2(spi_mem_base);
    light_up_led_line(spi_mem_base);
    while(green_button_state(spi_mem_base) != 1) {
        set_scene(parlcd_mem_base, cells_array, *cursor_column, *cursor_row);
        set_cursor(spi_mem_base, cursor_column, cursor_row, &red_knob_last_state, &blue_knob_last_state);
        cell_birth(spi_mem_base, *cursor_column, *cursor_row, cells_array);
        cell_die(spi_mem_base, *cursor_column, *cursor_row, cells_array);
    }
    go_out_led_line(spi_mem_base);
}

void start_play_mode(unsigned char* parlcd_mem_base, cell* cells_array[32][48], unsigned char* spi_mem_base, int* cursor_column, int* cursor_row) {
    int red_knob_last_state = (int)red_knob_state(spi_mem_base);
    int blue_knob_last_state = (int)blue_knob_state(spi_mem_base);
    int num_of_cells = 0;
    for (int row = 0; row < 32; row++) {
        for (int column = 0; column < 48; column++) {
            if (cells_array[row][column]->live) num_of_cells++;
        }
    }
    int iteration = 0;
    while (green_button_state(spi_mem_base) != 1) {
        set_scene(parlcd_mem_base, cells_array, *cursor_column, *cursor_row);
        set_cells_array(cells_array);
        cell_die(spi_mem_base, *cursor_column, *cursor_row, cells_array);
        if (iteration == 50) {
            if (get_population_growth(cells_array, &num_of_cells)){
                go_out_rgb1(spi_mem_base);
                light_up_green_color_rgb2(spi_mem_base);
            } else {
                go_out_rgb2(spi_mem_base);
                light_up_red_color_rgb1(spi_mem_base);
            }
            iteration = 0;
        }
        set_cursor(spi_mem_base, cursor_column, cursor_row, &red_knob_last_state, &blue_knob_last_state);
        if (cell_birth(spi_mem_base, *cursor_column, *cursor_row, cells_array)) {
            start_selection_mode(parlcd_mem_base, cells_array, spi_mem_base, cursor_column, cursor_row);
            for (int row = 0; row < 32; row++) {
                for (int column = 0; column < 48; column++) {
                    if (cells_array[row][column]->live) num_of_cells++;
                }
            }
            go_out_led_line(spi_mem_base);
            my_sleep();
        }
        set_scene(parlcd_mem_base, cells_array, *cursor_column, *cursor_row);
        iteration++;
    }
}

void start_ready_layouts_mode(unsigned char* parlcd_mem_base, cell* ready_layouts_array[32][48], unsigned char* spi_mem_base, int* cursor_state) {
    int green_knob_last_state = (int)green_knob_state(spi_mem_base);
    while (green_button_state(spi_mem_base) != 1) {
        my_sleep();
        set_ready_layouts_scene(parlcd_mem_base, ready_layouts_array, &green_knob_last_state, spi_mem_base, cursor_state);
    }
}
