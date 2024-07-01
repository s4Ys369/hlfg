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
int nextFont = FONT_8BIT_3;

void ui_init (void){

    font[1] =  rdpq_font_load("rom:/abaddon.font64");
    font[2] =  rdpq_font_load("rom:/8bit0.font64");
    font[3] =  rdpq_font_load("rom:/8bit1.font64");
    font[4] =  rdpq_font_load("rom:/8bit2.font64");
    font[5] =  rdpq_font_load("rom:/8bit3.font64");
    font[6] =  rdpq_font_load("rom:/8bit4.font64");
    font[7] =  rdpq_font_load("rom:/8bit5.font64");
    font[8] =  rdpq_font_load("rom:/at01.font64");
    font[9] =  rdpq_font_load("rom:/avenuepixel.font64");
    font[10] = rdpq_font_load("rom:/bitpotion.font64");
    font[11] = rdpq_font_load("rom:/chunkysans.font64");
    font[12] = rdpq_font_load("rom:/CyborgSister.font64");
    font[13] = rdpq_font_load("rom:/divinity.font64");
    font[14] = rdpq_font_load("rom:/dmsans.font64");
    font[15] = rdpq_font_load("rom:/droid-sans.font64");
    font[16] = rdpq_font_load("rom:/EnterCommand.font64");
    font[17] = rdpq_font_load("rom:/FiraMonoBold.font64");
    font[18] = rdpq_font_load("rom:/fortzilla.font64");
    font[19] = rdpq_font_load("rom:/Lato.font64");
    font[20] = rdpq_font_load("rom:/Liver.font64");
    font[21] = rdpq_font_load("rom:/m3x6.font64");
    font[22] = rdpq_font_load("rom:/m5x7.font64");
    font[23] = rdpq_font_load("rom:/m6x11plus.font64");
    font[24] = rdpq_font_load("rom:/minimalpixel.font64");
    font[25] = rdpq_font_load("rom:/monogram.font64");
    font[26] = rdpq_font_load("rom:/Pacifico.font64");
    font[27] = rdpq_font_load("rom:/poco.font64");
    font[28] = rdpq_font_load("rom:/Roboto-Medium.font64");
    font[29] = rdpq_font_load("rom:/roundabout.font64");
    font[30] = rdpq_font_load("rom:/Silver.font64");
    font[31] = rdpq_font_load("rom:/slab.font64");
    font[32] = rdpq_font_load("rom:/timesplitter.font64");
    font[33] = rdpq_font_load("rom:/Unbalanced.font64");
    font[34] = rdpq_font_load("rom:/xolonium.font64");

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
    rdpq_text_register_font(FONT_abaddon,       font[1]);
    rdpq_text_register_font(FONT_8BIT_0,        font[2]);
    rdpq_text_register_font(FONT_8BIT_1,        font[3]);
    rdpq_text_register_font(FONT_8BIT_2,        font[4]);
    rdpq_text_register_font(FONT_8BIT_3,        font[5]);
    rdpq_text_register_font(FONT_8BIT_4,        font[6]);
    rdpq_text_register_font(FONT_8BIT_5,        font[7]);
    rdpq_text_register_font(FONT_at01,          font[8]);
    rdpq_text_register_font(FONT_avenuepixel,   font[9]);
    rdpq_text_register_font(FONT_bitpotion,     font[10]);
    rdpq_text_register_font(FONT_chunkysans,    font[11]);
    rdpq_text_register_font(FONT_CyborgSister,  font[12]);
    rdpq_text_register_font(FONT_divinty,       font[13]);
    rdpq_text_register_font(FONT_dmsans,        font[14]);
    rdpq_text_register_font(FONT_droidsans,     font[15]);
    rdpq_text_register_font(FONT_EnterCommand,  font[16]);
    rdpq_text_register_font(FONT_FiraMonoBold,  font[17]);
    rdpq_text_register_font(FONT_fortzilla,     font[18]);
    rdpq_text_register_font(FONT_Lato,          font[19]);
    rdpq_text_register_font(FONT_Liver,         font[20]);
    rdpq_text_register_font(FONT_m3x6,          font[21]);
    rdpq_text_register_font(FONT_m5x7,          font[22]);
    rdpq_text_register_font(FONT_m6x11plus,     font[23]);
    rdpq_text_register_font(FONT_minimalpixel,  font[24]);
    rdpq_text_register_font(FONT_monogram,      font[25]);
    rdpq_text_register_font(FONT_Pacifico,      font[26]);
    rdpq_text_register_font(FONT_poco,          font[27]);
    rdpq_text_register_font(FONT_RobotoMedium,  font[28]);
    rdpq_text_register_font(FONT_roundabout,    font[29]);
    rdpq_text_register_font(FONT_Silver,        font[30]);
    rdpq_text_register_font(FONT_slab,          font[31]);
    rdpq_text_register_font(FONT_timesplitter,  font[32]);
    rdpq_text_register_font(FONT_Unbalanced,    font[33]);
    rdpq_text_register_font(FONT_xolonium,      font[34]);

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
            if(nextFont > FONT_RESERVED + 1){
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