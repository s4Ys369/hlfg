#ifndef INPUT_H
#define INPUT_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include "../include/config.h"
#include "../include/globals.h"
#include "../include/enums.h"

extern joypad_inputs_t joypad[MAX_PLAYERS];
extern joypad_buttons_t btn[MAX_PLAYERS];
extern joypad_buttons_t btnheld[MAX_PLAYERS];
extern int numPlayers;
extern bool rumble_supported[MAX_PLAYERS];
extern bool rumble_active[MAX_PLAYERS];
extern bool rumbleLong[MAX_PLAYERS];
extern bool rumbleShort[MAX_PLAYERS];
extern bool rumbleWave[MAX_PLAYERS];

void input_init(void);
void rumble_short(int numPlayer);
void rumble_long(int numPlayer);
void rumble_wave(int numPlayer);
void pd_set_rumble(int device, float numsecs, int32_t onduration, int32_t offduration);
void input_update(void);

#endif // INPUT_H