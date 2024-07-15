#ifndef SOUND_H
#define SOUND_H

#include <libdragon.h>
#include "../include/enums.h"

extern wav64_t sfx_jump, sfx_attack, sfx_bounce, sfx_boing, bgm;

void sound_load(void);
void sound_init(void);
void sound_update_buffer(void);
void sound_bounce(void);
void sound_jump(void);
void sound_attack(void);

#endif // SOUND_H
