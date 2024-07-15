#include <libdragon.h>
#include "../include/enums.h"
#include "sound.h"

wav64_t sfx_jump, sfx_attack, sfx_bounce, sfx_boing, bgm;


// Configure depending on number of channels in xm
#define MAX_BGM_CHANNELS 8
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

// based on SFX channels (currently 2) plus BGM channels
#define MAX_CHANNELS 10

void sound_load(void) {
	wav64_open(&bgm, "rom:/sound/ene.wav64");
	wav64_set_loop(&bgm, true);
	wav64_open(&sfx_jump, "rom:/sound/jump.wav64");
	wav64_open(&sfx_attack, "rom:/sound/attack.wav64");
	wav64_open(&sfx_bounce, "rom:/sound/bounce.wav64");
	wav64_open(&sfx_boing, "rom:/sound/boing.wav64");
}

void sound_init(void) {
	audio_init(44100, 4);
	mixer_init(MAX_CHANNELS);
	sound_load();
	wav64_play(&bgm, MUSIC_CHANNEL[0]);
	
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

