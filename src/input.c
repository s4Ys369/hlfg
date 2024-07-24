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
// Simple 10 frame rumble
void rumble_short(int numPlayer){
    joypad_set_rumble_active(numPlayer, true);
    rumble_active[numPlayer] = true;
    shortTimer++;
    if(shortTimer >= 10){
        joypad_set_rumble_active(numPlayer, false);
        rumbleShort[numPlayer] = false;
        rumble_active[numPlayer] = false;
        shortTimer = 0;
    }
}

int longTimer = 0;
// Simple 13 frame rumble
void rumble_long(int numPlayer){
    joypad_set_rumble_active(numPlayer, true);
    rumble_active[numPlayer] = true;
    longTimer++;
    if(longTimer >= 13){
        joypad_set_rumble_active(numPlayer, false);
        rumble_active[numPlayer] = false;
        rumbleLong[numPlayer] = false;
        longTimer = 0;
    }
}


int sineTimer = 0;
const float freq = 0.2f;
const float amplitude = 15.0f;
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


// PERFECT DARK RUMBLE TEST
enum RUMBLE_STATE {
    RUMBLESTATE_NONE,
    RUMBLESTATE_DETECTED,
    RUMBLESTATE_ENABLED_STOPPED,  
    RUMBLESTATE_ENABLED_STARTING,  
    RUMBLESTATE_ENABLED_RUMBLING,  
    RUMBLESTATE_ENABLED_STOPPING, 
    RUMBLESTATE_DISABLED_STOPPING,
    RUMBLESTATE_DISABLED_STOPPED, 
    RUMBLESTATE_ENABLING          
};

struct pakParams {
	uint32_t rumblestate;
	int32_t rumblepulsestopat;
	uint32_t rumblepulselen;
	uint32_t rumblepulsetimer; 
    float rumblettl;
};

struct pakParams g_Paks[MAX_PLAYERS];

const char* rumbleStateStrings[9] = {
    "NOT DETECTED",
    "DETECTED",
    "ENABLED STOPPED",  
    "ENABLED STARTING",  
    "ENABLED RUMBLING",  
    "ENABLED STOPPING", 
    "DISABLED STOPPING",
    "DISABLED STOPPED", 
    "ENABLING" 
};

void pd_rumble_update(void){

	for (int i = 0; i < numPlayers; i++) {
		switch (g_Paks[i].rumblestate) {
			case RUMBLESTATE_ENABLED_STARTING:
				g_Paks[i].rumblestate = RUMBLESTATE_ENABLED_RUMBLING;
				joypad_set_rumble_active(i, true);
                rumble_active[i] = true;
				break;
			case RUMBLESTATE_ENABLED_RUMBLING:
				if (g_Paks[i].rumblepulsestopat != -1) {
					if (g_Paks[i].rumblepulsetimer == 0) {
						joypad_set_rumble_active(i, true);
                        rumble_active[i] = true;
					} else if (g_Paks[i].rumblepulsestopat == g_Paks[i].rumblepulsetimer) {
						joypad_set_rumble_active(i, false);
                        rumble_active[i] = false;
					}

                g_Paks[i].rumblepulsetimer++;

					if (g_Paks[i].rumblepulselen == g_Paks[i].rumblepulsetimer) {
						g_Paks[i].rumblepulsetimer = 0;
					}
				}

				g_Paks[i].rumblettl--;

				if (g_Paks[i].rumblettl < 0) {
					g_Paks[i].rumblestate = RUMBLESTATE_ENABLED_STOPPING;
				}
				break;
			case RUMBLESTATE_ENABLED_STOPPING:
				g_Paks[i].rumblestate = RUMBLESTATE_ENABLED_STOPPED;
				joypad_set_rumble_active(i, false);
                rumble_active[i] = false;
                rumbleLong[i] = false;
                rumbleShort[i] = false;
				break;
			case RUMBLESTATE_DISABLED_STOPPING:
				joypad_set_rumble_active(i, false);
                rumble_active[i] = false;
                rumbleLong[i] = false;
                rumbleShort[i] = false;
				g_Paks[i].rumblestate = RUMBLESTATE_DISABLED_STOPPED;
				break;
			case RUMBLESTATE_ENABLING:
				g_Paks[i].rumblestate = RUMBLESTATE_ENABLED_STOPPED;
				g_Paks[i].rumblettl = -1;
				break;
			}
		}
}

void pd_stop_rumble(int numPlayer) {

    if(rumble_active[numPlayer]){
        joypad_set_rumble_active(numPlayer, false);
        rumble_active[numPlayer] = false;
    }


    if (g_Paks[numPlayer].rumblestate != RUMBLESTATE_DISABLED_STOPPING
            && g_Paks[numPlayer].rumblestate != RUMBLESTATE_DISABLED_STOPPED) {
        g_Paks[numPlayer].rumblestate = RUMBLESTATE_ENABLED_STOPPING;
    }

    g_Paks[numPlayer].rumblettl = -1;
}

void pd_set_rumble(int numPlayer, float numsecs, int32_t onduration, int32_t offduration){

	if (g_Paks[numPlayer].rumblestate != RUMBLESTATE_DISABLED_STOPPING
			&& g_Paks[numPlayer].rumblestate != RUMBLESTATE_DISABLED_STOPPED
			&& g_Paks[numPlayer].rumblettl < 60 * numsecs) {
		g_Paks[numPlayer].rumblestate = RUMBLESTATE_ENABLED_STARTING;
		g_Paks[numPlayer].rumblettl = 60 * numsecs;
		g_Paks[numPlayer].rumblepulsestopat = onduration;
		g_Paks[numPlayer].rumblepulselen = onduration + offduration;
		g_Paks[numPlayer].rumblepulsetimer = 0;
	}
}

void pd_rumble_param_clear(int numPlayer){
    g_Paks[numPlayer].rumblettl = 0;
    g_Paks[numPlayer].rumblepulsestopat = 0;
    g_Paks[numPlayer].rumblepulselen = 0;
    g_Paks[numPlayer].rumblepulsetimer = 0;
}

void pd_rumble_disabled(int numPlayer){
    g_Paks[numPlayer].rumblestate = RUMBLESTATE_DISABLED_STOPPED;
    pd_rumble_param_clear(numPlayer);
}

void pd_rumble_kill(int numPlayer){
    g_Paks[numPlayer].rumblestate = RUMBLESTATE_DISABLED_STOPPING;
    pd_rumble_disabled(numPlayer);
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
        pd_rumble_update();
        if(rumbleWave[np]){
            rumble_wave(np);
        }
        if(btn[np].l){
            pd_stop_rumble(np);
            pd_rumble_param_clear(np);
        }
        
        //debugf("%u %s ", np, rumbleStateStrings[g_Paks[np].rumblestate]);
        //debugf("%lu %lu %lu %.1f\n", g_Paks[np].rumblepulsestopat, g_Paks[np].rumblepulselen, g_Paks[np].rumblepulsetimer, g_Paks[np].rumblettl);
    }

}
