#ifndef INPUT_H
#define INPUT_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>

extern joypad_inputs_t joypad;
extern joypad_buttons_t btn;
extern joypad_buttons_t btnheld;

void input_init(void);
void input_update(void);

#endif // INPUT_H