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

void input_init(void);
void input_update(void);

#endif // INPUT_H