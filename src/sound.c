#include <libdragon.h>
#include "../include/enums.h"
#include "sound.h"

char *xm_fn = NULL;
xm64player_t xm;
wav64_t sfx_jump, sfx_attack, sfx_bounce, sfx_boing;


// Configure depending on number of channels in xm
#define MAX_BGM_CHANNELS 16
int MUSIC_CHANNEL[] = {
	BGM1,
	BGM2,
	BGM3,
	BGM4,
	BGM5,
	BGM6,
	BGM7,
	BGM8,
	BGM9,
	BGM10,
	BGM11,
	BGM12,
	BGM13,
	BGM14,
	BGM15,
	BGM16
};


void sound_load(void) {
	xm64player_open(&xm, "rom:/sound/ene.xm64");

	wav64_open(&sfx_jump, "rom:/sound/jump.wav64");
	wav64_open(&sfx_attack, "rom:/sound/attack.wav64");
	wav64_open(&sfx_bounce, "rom:/sound/bounce.wav64");
	wav64_open(&sfx_boing, "rom:/sound/boing.wav64");
}

void sound_init(void) {
	audio_init(48000, 4);
	mixer_init(NUM_CHANNELS);
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

void sound_bounce(void){
	wav64_play(&sfx_bounce, 0);
	wav64_play(&sfx_boing, 1);
	mixer_try_play();
}

void sound_jump(void){
	wav64_play(&sfx_jump, 0);
	mixer_try_play();
}

void sound_attack(void){
	wav64_play(&sfx_attack, 0);
	mixer_try_play();
}

