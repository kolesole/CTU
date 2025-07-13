/*******************************************************************
  Source file with function to read a knobs state for game of life on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  knobs.c      - source file with function to read a knobs state

 (C) 2024 by Oleksii Kolesnichenko
     e-mail:   kolesole@fel.cvut.cz
     license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#include "knobs.h"

uint32_t filtered_knobs_state(unsigned char* spi_mem_base) {
    return *(volatile uint32_t*)(spi_mem_base + SPILED_REG_KNOBS_8BIT_o);
}

uint32_t red_knob_state(unsigned char* spi_mem_base) {
    return (filtered_knobs_state(spi_mem_base) >> 16) & 0xFF;
}

uint32_t green_knob_state(unsigned char* spi_mem_base) {
    return (filtered_knobs_state(spi_mem_base) >> 8) & 0xFF;
}

uint32_t blue_knob_state(unsigned char* spi_mem_base) {
    return filtered_knobs_state(spi_mem_base) & 0xFF;
}

uint32_t red_button_state(unsigned char* spi_mem_base) {
    return (filtered_knobs_state(spi_mem_base) >> 26) & 0x01;
}

uint32_t green_button_state(unsigned char* spi_mem_base) {
    return (filtered_knobs_state(spi_mem_base) >> 25) & 0x01;
}

uint32_t blue_button_state(unsigned char* spi_mem_base) {
    return (filtered_knobs_state(spi_mem_base) >> 24) & 0x01;
}

void light_up_led_line(unsigned char* spi_mem_base) {
    for (int i = 0; i < 32; i++) {
        *(volatile uint32_t*)(spi_mem_base + SPILED_REG_LED_LINE_o) |= (1 << i);
    }
}

void go_out_led_line(unsigned char* spi_mem_base) {
    *(volatile uint32_t*)(spi_mem_base + SPILED_REG_LED_LINE_o) = 0x000000;
}

void light_up_red_color_rgb1(unsigned char* spi_mem_base) {
    *(volatile uint32_t*)(spi_mem_base + SPILED_REG_LED_RGB1_o) = 0xFF0000;
}

void go_out_rgb1(unsigned char* spi_mem_base){
    *(volatile uint32_t*)(spi_mem_base + SPILED_REG_LED_RGB1_o) = 0x000000;
}

void light_up_green_color_rgb2(unsigned char* spi_mem_base) {
    *(volatile uint32_t*)(spi_mem_base + SPILED_REG_LED_RGB2_o) = 0x00FF00;
}

void go_out_rgb2(unsigned char* spi_mem_base) {
    *(volatile uint32_t*)(spi_mem_base + SPILED_REG_LED_RGB2_o) = 0x000000;
}


