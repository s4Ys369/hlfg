#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>
#include "../include/config.h"
#include "input.h"

joypad_inputs_t joypad[NUM_PLAYERS];
joypad_buttons_t btn[NUM_PLAYERS];
joypad_buttons_t btnheld[NUM_PLAYERS];

void input_init(void){
    joypad_init();
}

void input_update(void){
    joypad_poll();
    switch(NUM_PLAYERS){
        case 1:
            joypad[0] = joypad_get_inputs(JOYPAD_PORT_1);
            btn[0] = joypad_get_buttons_pressed(JOYPAD_PORT_1);
            btnheld[0] = joypad_get_buttons_held(JOYPAD_PORT_1);
            break;
        case 2:
            joypad[0] = joypad_get_inputs(JOYPAD_PORT_1);
            btn[0] = joypad_get_buttons_pressed(JOYPAD_PORT_1);
            btnheld[0] = joypad_get_buttons_held(JOYPAD_PORT_1);
            joypad[1] = joypad_get_inputs(JOYPAD_PORT_2);
            btn[1] = joypad_get_buttons_pressed(JOYPAD_PORT_2);
            btnheld[1] = joypad_get_buttons_held(JOYPAD_PORT_2);
            break;
        case 3:
            joypad[0] = joypad_get_inputs(JOYPAD_PORT_1);
            btn[0] = joypad_get_buttons_pressed(JOYPAD_PORT_1);
            btnheld[0] = joypad_get_buttons_held(JOYPAD_PORT_1);
            joypad[1] = joypad_get_inputs(JOYPAD_PORT_2);
            btn[1] = joypad_get_buttons_pressed(JOYPAD_PORT_2);
            btnheld[1] = joypad_get_buttons_held(JOYPAD_PORT_2);
            joypad[2] = joypad_get_inputs(JOYPAD_PORT_3);
            btn[2] = joypad_get_buttons_pressed(JOYPAD_PORT_3);
            btnheld[2] = joypad_get_buttons_held(JOYPAD_PORT_3);
            break;
        case 4:
            joypad[0] = joypad_get_inputs(JOYPAD_PORT_1);
            btn[0] = joypad_get_buttons_pressed(JOYPAD_PORT_1);
            btnheld[0] = joypad_get_buttons_held(JOYPAD_PORT_1);
            joypad[1] = joypad_get_inputs(JOYPAD_PORT_2);
            btn[1] = joypad_get_buttons_pressed(JOYPAD_PORT_2);
            btnheld[1] = joypad_get_buttons_held(JOYPAD_PORT_2);
            joypad[2] = joypad_get_inputs(JOYPAD_PORT_3);
            btn[2] = joypad_get_buttons_pressed(JOYPAD_PORT_3);
            btnheld[2] = joypad_get_buttons_held(JOYPAD_PORT_3);
            joypad[3] = joypad_get_inputs(JOYPAD_PORT_4);
            btn[3] = joypad_get_buttons_pressed(JOYPAD_PORT_4);
            btnheld[3] = joypad_get_buttons_held(JOYPAD_PORT_4);
            break;
    }
}
