#ifndef UI_H
#define UI_H

#include <libdragon.h>
#include "../include/config.h"
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "debug.h"
#include "input.h"
#include "player.h"
#include "utils.h"

extern bool isPaused;
extern int nextFont;
extern sprite_t *BG0;
extern sprite_t *BG1;

void ui_init(void);
void print_controls(int fontIdx);
void print_score(int fontIdx);
void ui_update(void);

#endif // UI_H