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

extern sprite_t *spriteTextWindow;
extern rdpq_texparms_t textWindowParams;
extern bool isPaused;
extern int nextFont;

void ui_init(void);
void print_controls(int fontIdx);
void print_score(int fontIdx);
void ui_update(void);

#endif // UI_H