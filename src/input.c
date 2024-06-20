#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>
#include "input.h"

joypad_inputs_t joypad;
joypad_buttons_t btn;
joypad_buttons_t btnheld;

void input_init(void){
    joypad_init();
}

void input_update(void){
    joypad_poll();
    joypad = joypad_get_inputs(JOYPAD_PORT_1);
    btn = joypad_get_buttons_pressed(JOYPAD_PORT_1);
    btnheld = joypad_get_buttons_held(JOYPAD_PORT_1);
}
