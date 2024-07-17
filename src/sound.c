#include <libdragon.h>
#include "../include/enums.h"
#include "sound.h"

char *xm_fn = NULL;
xm64player_t xm;
wav64_t sfx_jump, sfx_attack, sfx_bounce, sfx_boing;


// Configure depending on number of channels in xm



const char* xmFileNames[5] = {
    "rom:/sound/ene.xm64",
    "rom:/sound/Floating-Down.xm64",
    "rom:/sound/hand-over-hand.xm64",
    "rom:/sound/Systematic.xm64",
    "rom:/sound/turned-around.xm64"
};


void sound_load(void) {
	xm64player_open(&xm, xmFileNames[0]);

	wav64_open(&sfx_jump, "rom:/sound/jump.wav64");
	wav64_open(&sfx_attack, "rom:/sound/attack.wav64");
	wav64_open(&sfx_bounce, "rom:/sound/bounce.wav64");
	wav64_open(&sfx_boing, "rom:/sound/boing.wav64");
}

void sound_init(void) {
	audio_init(48000, 4);
	mixer_init(NUM_CHANNELS+29); // sfx1, sfx 2, and music channel + 29 for 32 max
	sound_load();
	xm64player_set_loop(&xm, true);
	xm64player_set_vol(&xm, 0.3f);
	xm64player_play(&xm, MUSIC_CHANNEL);
}

void switch_xm(int songID){
	xm64player_close(&xm);
	xm64player_open(&xm, xmFileNames[songID]);
	xm64player_set_loop(&xm, true);
	xm64player_set_vol(&xm, 0.3f);
	xm64player_play(&xm, MUSIC_CHANNEL);
}

void sound_update_buffer(void) {
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

