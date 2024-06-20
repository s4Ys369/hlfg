#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdint.h>
#include <libdragon.h>
#include "sound.h"

char *xm_fn = NULL;
xm64player_t xm;
wav64_t sfx_jump, sfx_attack, sfx_bounce, sfx_boing;

#define MAX_CHANNELS 10
#define MAX_BGM_CHANNELS 8


enum {
	SFX1 = 0,
	SFX2 = 1,
	BGM1 = 2,
	BGM2 = 3,
	BGM3 = 4,
	BGM4 = 5,
	BGM5 = 6,
	BGM6 = 7,
	BGM7 = 8,
	BGM8 = 9,
    // add more?
} SOUND_CHANNEL;

int MUSIC_CHANNEL[] = {
	BGM1,
	BGM2,
	BGM3,
	BGM4,
	BGM5,
	BGM6,
	BGM7,
	BGM8
};

void sound_load(void) {
	xm64player_open(&xm, "rom:/TOYS.xm64");

	wav64_open(&sfx_jump, "rom:/jump.wav64");
	wav64_open(&sfx_attack, "rom:/attack.wav64");
	wav64_open(&sfx_bounce, "rom:/bounce.wav64");
	wav64_open(&sfx_boing, "rom:/boing.wav64");
}

void sound_init(void) {
	audio_init(44100, 4);
	mixer_init(MAX_CHANNELS);
	sound_load();
	xm64player_play(&xm, MUSIC_CHANNEL[0]);
	
}

void sound_update_buffer(void) {
	mixer_try_play();
    if (audio_can_write()) {
		short *buf = audio_write_begin();
		mixer_poll(buf, audio_get_buffer_length());
		audio_write_end();
	}
}

