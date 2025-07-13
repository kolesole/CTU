/*******************************************************************
  Header file with function to read a knobs state for game of life on MicroZed
  based MZ_APO board designed by Petr Porazil at PiKRON

  knobs.h      - header file with function to read a knobs state

 (C) 2024 by Oleksii Kolesnichenko
     e-mail:   kolesole@fel.cvut.cz
     license:  any combination of GPL, LGPL, MPL or BSD licenses
 *******************************************************************/

#ifndef KNOBS_H
#define KNOBS_H

#include <stdint.h>
#include "mzapo_regs.h"
//function that returns filtered knobs state
uint32_t filtered_knobs_state(unsigned char* spi_mem_base);
//function that returns red switch state
uint32_t red_knob_state(unsigned char* spi_mem_base);
//function that returns green switch state
uint32_t green_knob_state(unsigned char* spi_mem_base);
//function that returns blue switch state
uint32_t blue_knob_state(unsigned char* spi_mem_base);
//function that returns red button state
uint32_t red_button_state(unsigned char* spi_mem_base);
//function that returns green button state
uint32_t green_button_state(unsigned char* spi_mem_base);
//function that returns blue button state
uint32_t blue_button_state(unsigned char* spi_mem_base);
//function that lights up led line
void light_up_led_line(unsigned char* spi_mem_base);
//function that turns off led line
void go_out_led_line(unsigned char* spi_mem_base);
//function that lights up rgb1 in red
void light_up_red_color_rgb1(unsigned char* spi_mem_base);
//function that turns off rgb1
void go_out_rgb1(unsigned char* spi_mem_base);
//function that lights up rgb2 in green
void light_up_green_color_rgb2(unsigned char* spi_mem_base);
//function that turns off rgd2
void go_out_rgb2(unsigned char* spi_mem_base);

#endif //KNOBS_H
