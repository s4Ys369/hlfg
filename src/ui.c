#include <libdragon.h>
#include "../include/config.h"
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "debug.h"
#include "input.h"
#include "player.h"
#include "ui.h"
#include "utils.h"

float textX;
float textY;
rdpq_font_t *font[MAX_NUM_FONTS];
bool isPaused;
int nextFont = 1;

void ui_init (void){

    font[1] = rdpq_font_load("rom:/pac.font64");
    font[2] = rdpq_font_load("rom:/8bit0.font64");
    font[3] = rdpq_font_load("rom:/8bit1.font64");
    font[4] = rdpq_font_load("rom:/8bit2.font64");
    font[5] = rdpq_font_load("rom:/8bit3.font64");
    font[6] = rdpq_font_load("rom:/8bit4.font64");
    font[7] = rdpq_font_load("rom:/8bit5.font64");

    for (int i = 1; i < MAX_NUM_FONTS; i++) {
        rdpq_font_style(font[i], STYLE_0, &(rdpq_fontstyle_t){
            .color = GREY,
        });
        rdpq_font_style(font[i], STYLE_1, &(rdpq_fontstyle_t){
            .color = GREEN,
        });
        rdpq_font_style(font[i], STYLE_2, &(rdpq_fontstyle_t){
            .color = RED,
        });
    }
    rdpq_text_register_font(FONT_PACIFICO, font[1]);
    rdpq_text_register_font(FONT_8BIT_0, font[2]);
    rdpq_text_register_font(FONT_8BIT_1, font[3]);
    rdpq_text_register_font(FONT_8BIT_2, font[4]);
    rdpq_text_register_font(FONT_8BIT_3, font[5]);
    rdpq_text_register_font(FONT_8BIT_4, font[6]);
    rdpq_text_register_font(FONT_8BIT_5, font[7]);

    isPaused = false;
}

void print_score(int fontIdx){
    textX = 12;
    textY = 210;

    if(numPlayers > 1) {
        if(numPlayers == 2) {
          rdpq_text_printf(NULL, fontIdx, textX, textY/2, "SCORE %d", player[0]->score);
          rdpq_text_printf(NULL, fontIdx, textX, textY, "SCORE %d", player[1]->score);
        }
        if(numPlayers == 3) {
          rdpq_text_printf(NULL, fontIdx, textX, textY/2, "SCORE %d", player[0]->score);
          rdpq_text_printf(NULL, fontIdx, textX, textY, "SCORE %d", player[1]->score);
          rdpq_text_printf(NULL, fontIdx, (textX*14)+4,  textY+10, "SCORE %d", player[2]->score);
        }
        if(numPlayers == 4) {
          rdpq_text_printf(NULL, fontIdx, textX, textY/2, "SCORE %d", player[0]->score);
          rdpq_text_printf(NULL, fontIdx, (textX*14)+4,  textY/2, "SCORE %d", player[1]->score);
          rdpq_text_printf(NULL, fontIdx, textX, textY, "SCORE %d", player[2]->score);
          rdpq_text_printf(NULL, fontIdx, (textX*14)+4, textY+10, "SCORE %d", player[3]->score);
        }
    } else {
        rdpq_text_printf(NULL, fontIdx, textX, textY, "SCORE %d", player[0]->score);
    }   
}

void print_controls(int fontIdx){
    textX  = 80;
    textY = 40;
    rdpq_text_printf(&(rdpq_textparms_t){.style_id = STYLE_1,}, fontIdx, textX, textY, "IBE: Itty Bitty Engine");textY+=10;
    rdpq_text_printf(&(rdpq_textparms_t){.style_id = STYLE_1,}, fontIdx, textX, textY, "Game Engine for Tiny3D");textY+=10;
    rdpq_text_printf(&(rdpq_textparms_t){.style_id = STYLE_1,}, fontIdx, textX+55, textY, "v%.1f.%u", VERSION, VERSION_SUFFIX);textY+=10;
    rdpq_text_printf(&(rdpq_textparms_t){.style_id = STYLE_2,}, fontIdx, textX+50, textY, "by s4ys");textY+=10;
    

    rdpq_text_printf(&(rdpq_textparms_t){.style_id = STYLE_0,}, fontIdx, textX, textY, "Control Stick : Move");textY+=10;
    rdpq_text_printf(&(rdpq_textparms_t){.style_id = STYLE_0,}, fontIdx, textX, textY, "A : Jump");textY+=10;
    rdpq_text_printf(&(rdpq_textparms_t){.style_id = STYLE_0,}, fontIdx, textX, textY, "B : Attack");textY+=10;
    rdpq_text_printf(&(rdpq_textparms_t){.style_id = STYLE_0,}, fontIdx, textX, textY, "C Down : Normal Cam");textY+=10;
    rdpq_text_printf(&(rdpq_textparms_t){.style_id = STYLE_0,}, fontIdx, textX, textY, "C Left & Right :");textY+=10;
    rdpq_text_printf(&(rdpq_textparms_t){.style_id = STYLE_0,}, fontIdx, textX+10, textY, "Rotate Fixed Cam");textY+=10;
    rdpq_text_printf(&(rdpq_textparms_t){.style_id = STYLE_0,}, fontIdx, textX, textY, "C Up : Top Down Cam");textY+=10;
    rdpq_text_printf(&(rdpq_textparms_t){.style_id = STYLE_0,}, fontIdx, textX, textY, "Z : Recenter Cam");textY+=10;
    rdpq_text_printf(&(rdpq_textparms_t){.style_id = STYLE_0,}, fontIdx, textX, textY, "Hold R : Debug");textY+=10;
    rdpq_text_printf(&(rdpq_textparms_t){.style_id = STYLE_0,}, fontIdx, textX, textY, "Hold L : HitBoxes");textY+=20;
    rdpq_text_printf(&(rdpq_textparms_t){.style_id = STYLE_0,}, fontIdx, textX-20, textY, "Change font with D Pad Left and Right");textY+=10;
}

void ui_update(void){
    
    if(btn[0].start){
        if(isPaused == false){
            isPaused = true;
        } else {
            isPaused = false;
        }
    }

    

    if(isPaused){
        rdpq_set_mode_fill(BLACK);
        rdpq_fill_rectangle(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        if(btn[0].d_left){
            if(nextFont > 1){
                nextFont--;
            }
        }
        if(btn[0].d_right){
            if(nextFont < MAX_NUM_FONTS - 1){
                nextFont++;
            }
        }
        print_controls(nextFont);
    } else {
        print_score(nextFont);
    }
}