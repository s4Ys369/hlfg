#include <libdragon.h>
#include <t3d/t3d.h>
#include "../include/config.h"
#include "../include/globals.h"
#include "../include/enums.h"
#include "input.h"

joypad_inputs_t joypad[MAX_PLAYERS];
joypad_buttons_t btn[MAX_PLAYERS];
joypad_buttons_t btnheld[MAX_PLAYERS];

int numPlayers;

// Init joypads and check how many are plugged in
void input_init(void){
    if(joypad_is_connected(JOYPAD_PORT_1)){
        numPlayers++;
    }
    if(joypad_is_connected(JOYPAD_PORT_2)){
        numPlayers++;
    }
    if(joypad_is_connected(JOYPAD_PORT_3)){
        numPlayers++;
    }
    if(joypad_is_connected(JOYPAD_PORT_4)){
        numPlayers++;
    }
}

// Poll joypads based on number of players
void input_update(void){
    joypad_poll();
    switch(numPlayers){
        case PLAYERS_0:
        case PLAYERS_1:
            joypad[0] = joypad_get_inputs(JOYPAD_PORT_1);
            btn[0] = joypad_get_buttons_pressed(JOYPAD_PORT_1);
            btnheld[0] = joypad_get_buttons_held(JOYPAD_PORT_1);
            break;
        case PLAYERS_2:
            joypad[0] = joypad_get_inputs(JOYPAD_PORT_1);
            btn[0] = joypad_get_buttons_pressed(JOYPAD_PORT_1);
            btnheld[0] = joypad_get_buttons_held(JOYPAD_PORT_1);
            joypad[1] = joypad_get_inputs(JOYPAD_PORT_2);
            btn[1] = joypad_get_buttons_pressed(JOYPAD_PORT_2);
            btnheld[1] = joypad_get_buttons_held(JOYPAD_PORT_2);
            break;
        case PLAYERS_3:
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
        case PLAYERS_4:
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
