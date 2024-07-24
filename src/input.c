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
bool rumble_supported[MAX_PLAYERS];
bool rumble_active[MAX_PLAYERS];
bool rumbleLong[MAX_PLAYERS];
bool rumbleShort[MAX_PLAYERS];
bool rumbleWave[MAX_PLAYERS];

// Init joypads and check how many are plugged in
void input_init(void){
    joypad_init();

/*  Ares always sets every port as connected when loading,
    so until I finding a good way to detect Ares vs console,
    use this define for testing in various modes */
#ifdef FORCE_PLAYERS
    numPlayers = FORCE_PLAYERS;
#else
    for(int port = 1; port <= 4; port++) {
        if(joypad_is_connected(port)) {
            numPlayers++;
        }
    }
#endif
}


int shortTimer = 0;
// Simple 5 frame rumble
void rumble_short(int numPlayer){
    joypad_set_rumble_active(numPlayer, true);
    rumble_active[numPlayer] = true;
    shortTimer++;
    if(shortTimer >= 5){
        joypad_set_rumble_active(numPlayer, false);
        rumbleShort[numPlayer] = false;
        rumble_active[numPlayer] = false;
        shortTimer = 0;
    }
}

int longTimer = 0;
// Simple 7 frame rumble
void rumble_long(int numPlayer){
    joypad_set_rumble_active(numPlayer, true);
    rumble_active[numPlayer] = true;
    longTimer++;
    if(longTimer >= 7){
        joypad_set_rumble_active(numPlayer, false);
        rumble_active[numPlayer] = false;
        rumbleLong[numPlayer] = false;
        longTimer = 0;
    }
}


int sineTimer = 0;
const float freq = 0.8f;
const float threshold = 0.0f;
// Rumble that has a sine wave pulse
void rumble_wave(int numPlayer) {
    float sineValue = sinf(sineTimer * freq * 2 * T3D_PI);
    sineTimer++;
    if(sineTimer < 60){
        if (sineValue > threshold) {
            // Turn rumble on
            joypad_set_rumble_active(numPlayer, true);
            rumbleWave[numPlayer] = true;
            rumble_active[numPlayer] = true;
        } else {
            // Turn rumble off
            joypad_set_rumble_active(numPlayer, false);
            rumble_active[numPlayer] = false;
            rumbleWave[numPlayer] = false;
        }
    } else {
        // Turn rumble off
        joypad_set_rumble_active(numPlayer, false);
        rumble_active[numPlayer] = false;
        rumbleWave[numPlayer] = false;
        sineTimer = 0;
        sineValue = 0;
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

    for(int np = 0; np < numPlayers; ++np){
        rumble_supported[np] = joypad_get_rumble_supported(np);
        if(rumbleLong[np]) {
            rumble_long(np);
        }
        if(rumbleShort[np]){
            rumble_short(np);
        }
        if(rumbleWave[np]){
            rumble_wave(np);
        }
        if(btn[np].l){
            joypad_set_rumble_active(np, false);
            rumble_active[np] = false;
        }
    }

}
