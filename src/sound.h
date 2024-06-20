#ifndef SOUND_H
#define SOUND_H

#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>

extern char *xm_fn;
extern xm64player_t xm;
extern wav64_t sfx_jump, sfx_attack, sfx_bounce, sfx_boing;

void sound_load(void);
void sound_init(void);
void sound_update_buffer(void);

#endif // SOUND_H
