#include <libdragon.h>
#include "../include/config.h"
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "debug.h"
#include "input.h"
#include "player.h"
#include "sound.h"
#include "ui.h"
#include "utils.h"


rspq_block_t *dplScore;
rspq_block_t *dplControls;
rdpq_font_t *font[MAX_NUM_FONTS];
sprite_t *spriteTextWindow;
rdpq_texparms_t textWindowParams = {
    .s.repeats = REPEAT_INFINITE, 
    .t.repeats = REPEAT_INFINITE,
};

bool isPaused;
int nextFont = FONT_8BIT_3;
int xmID = 0;
float textX;
float textY;

void ui_init (void){

    // TODO fontma
    font[3] =  rdpq_font_load("rom:/fonts/abaddon.font64");
    font[4] =  rdpq_font_load("rom:/fonts/8bit0.font64");
    font[5] =  rdpq_font_load("rom:/fonts/8bit1.font64");
    font[6] =  rdpq_font_load("rom:/fonts/8bit2.font64");
    font[7] =  rdpq_font_load("rom:/fonts/8bit3.font64");
    font[8] =  rdpq_font_load("rom:/fonts/8bit4.font64");
    font[9] =  rdpq_font_load("rom:/fonts/8bit5.font64");
    font[10] =  rdpq_font_load("rom:/fonts/at01.font64");
    font[11] =  rdpq_font_load("rom:/fonts/avenuepixel.font64");
    font[12] = rdpq_font_load("rom:/fonts/bitpotion.font64");
    font[13] = rdpq_font_load("rom:/fonts/chunkysans.font64");
    font[14] = rdpq_font_load("rom:/fonts/CyborgSister.font64");
    font[15] = rdpq_font_load("rom:/fonts/divinity.font64");
    font[16] = rdpq_font_load("rom:/fonts/dmsans.font64");
    font[17] = rdpq_font_load("rom:/fonts/droid-sans.font64");
    font[18] = rdpq_font_load("rom:/fonts/EnterCommand.font64");
    font[19] = rdpq_font_load("rom:/fonts/FiraMonoBold.font64");
    font[20] = rdpq_font_load("rom:/fonts/fortzilla.font64");
    font[21] = rdpq_font_load("rom:/fonts/Lato.font64");
    font[22] = rdpq_font_load("rom:/fonts/Liver.font64");
    font[23] = rdpq_font_load("rom:/fonts/m3x6.font64");
    font[24] = rdpq_font_load("rom:/fonts/m5x7.font64");
    font[25] = rdpq_font_load("rom:/fonts/m6x11plus.font64");
    font[26] = rdpq_font_load("rom:/fonts/minimalpixel.font64");
    font[27] = rdpq_font_load("rom:/fonts/monogram.font64");
    font[28] = rdpq_font_load("rom:/fonts/Pacifico.font64");
    font[29] = rdpq_font_load("rom:/fonts/poco.font64");
    font[30] = rdpq_font_load("rom:/fonts/Roboto-Medium.font64");
    font[31] = rdpq_font_load("rom:/fonts/roundabout.font64");
    font[32] = rdpq_font_load("rom:/fonts/Silver.font64");
    font[33] = rdpq_font_load("rom:/fonts/slab.font64");
    font[34] = rdpq_font_load("rom:/fonts/timesplitter.font64");
    font[35] = rdpq_font_load("rom:/fonts/Unbalanced.font64");
    font[36] = rdpq_font_load("rom:/fonts/xolonium.font64");

    for (int i = 3; i < MAX_NUM_FONTS; i++) {
        rdpq_font_style(font[i], STYLE_0, &(rdpq_fontstyle_t){
            .color = WHITE,
            .outline_color = BLACK,
        });
        rdpq_font_style(font[i], STYLE_1, &(rdpq_fontstyle_t){
            .color = GREEN,
            .outline_color = DARK_GREEN,
        });
        rdpq_font_style(font[i], STYLE_2, &(rdpq_fontstyle_t){
            .color = RED,
            .outline_color = DARK_RED,
        });
        rdpq_font_style(font[i], STYLE_3, &(rdpq_fontstyle_t){
            .color = BLACK,
            .outline_color = GREY,
        });
        rdpq_font_style(font[i], STYLE_DEBUG, &(rdpq_fontstyle_t){
            .color = WHITE,
            .outline_color = GREY,
        });
        rdpq_font_style(font[i], STYLE_DB_PASS, &(rdpq_fontstyle_t){
            .color = GREEN,
            .outline_color = DARK_GREEN,
        });
        rdpq_font_style(font[i], STYLE_DB_FAIL, &(rdpq_fontstyle_t){
            .color = RED,
            .outline_color = DARK_RED,
        });
    }
    rdpq_text_register_font(FONT_BUILTIN_DEBUG_MONO, rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_MONO));
    rdpq_text_register_font(FONT_BUILTIN_DEBUG_VAR, rdpq_font_load_builtin(FONT_BUILTIN_DEBUG_VAR));
    rdpq_text_register_font(FONT_abaddon,       font[3]);
    rdpq_text_register_font(FONT_8BIT_0,        font[4]);
    rdpq_text_register_font(FONT_8BIT_1,        font[5]);
    rdpq_text_register_font(FONT_8BIT_2,        font[6]);
    rdpq_text_register_font(FONT_8BIT_3,        font[7]);
    rdpq_text_register_font(FONT_8BIT_4,        font[8]);
    rdpq_text_register_font(FONT_8BIT_5,        font[9]);
    rdpq_text_register_font(FONT_at01,          font[10]);
    rdpq_text_register_font(FONT_avenuepixel,   font[11]);
    rdpq_text_register_font(FONT_bitpotion,     font[12]);
    rdpq_text_register_font(FONT_chunkysans,    font[13]);
    rdpq_text_register_font(FONT_CyborgSister,  font[14]);
    rdpq_text_register_font(FONT_divinty,       font[15]);
    rdpq_text_register_font(FONT_dmsans,        font[16]);
    rdpq_text_register_font(FONT_droidsans,     font[17]);
    rdpq_text_register_font(FONT_EnterCommand,  font[18]);
    rdpq_text_register_font(FONT_FiraMonoBold,  font[19]);
    rdpq_text_register_font(FONT_fortzilla,     font[20]);
    rdpq_text_register_font(FONT_Lato,          font[21]);
    rdpq_text_register_font(FONT_Liver,         font[22]);
    rdpq_text_register_font(FONT_m3x6,          font[23]);
    rdpq_text_register_font(FONT_m5x7,          font[24]);
    rdpq_text_register_font(FONT_m6x11plus,     font[25]);
    rdpq_text_register_font(FONT_minimalpixel,  font[26]);
    rdpq_text_register_font(FONT_monogram,      font[27]);
    rdpq_text_register_font(FONT_Pacifico,      font[28]);
    rdpq_text_register_font(FONT_poco,          font[29]);
    rdpq_text_register_font(FONT_RobotoMedium,  font[30]);
    rdpq_text_register_font(FONT_roundabout,    font[31]);
    rdpq_text_register_font(FONT_Silver,        font[32]);
    rdpq_text_register_font(FONT_slab,          font[33]);
    rdpq_text_register_font(FONT_timesplitter,  font[34]);
    rdpq_text_register_font(FONT_Unbalanced,    font[35]);
    rdpq_text_register_font(FONT_xolonium,      font[36]);

    isPaused = false;
    spriteTextWindow = sprite_load("rom:/BG0.rgba16.sprite");

    dplScore = NULL;
    dplControls = NULL;
}

void print_score(int fontIdx){
    textX = 12;
    textY = 220;

    // Set up block for score
    if(!dplScore){
        rspq_block_begin();

        rdpq_sync_pipe();
        rdpq_sync_tile();

        rdpq_set_mode_standard();
        rdpq_mode_combiner(RDPQ_COMBINER1((0,0,0,PRIM), (PRIM,0,TEX0,0)));
        rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);

        rdpq_set_prim_color(T_BLACK);
        rdpq_sprite_upload(TILE1, spriteTextWindow, &textWindowParams);
        rdpq_sync_load(); //?

        rdpq_texture_rectangle(TILE1, textX-2, textY-30, textX+52, textY+4, 0, 0);

        dplScore = rspq_block_end();
    }

    rdpq_textparms_t scoreTextParams = {
        .disable_aa_fix = true, 
        .style_id = STYLE_DEBUG,
    };

    // Run text window block
    rspq_block_run(dplScore); 


    if(numPlayers > 1) {
        if(numPlayers == 2) {
            rdpq_text_printf(&scoreTextParams, fontIdx, textX, textY/2, "SCORE %d", player[0]->score);
            rdpq_text_printf(&scoreTextParams, fontIdx, textX, textY, "SCORE %d", player[1]->score);
        }
        if(numPlayers == 3) {
            rdpq_text_printf(&scoreTextParams, fontIdx, textX, textY/2, "SCORE %d", player[0]->score);
            rdpq_text_printf(&scoreTextParams, fontIdx, textX, textY, "SCORE %d", player[1]->score);
            rdpq_text_printf(&scoreTextParams, fontIdx, (textX*14)+4,  textY, "SCORE %d", player[2]->score);
        }
        if(numPlayers == 4) {
            rdpq_text_printf(&scoreTextParams, fontIdx, textX, textY/2, "SCORE %d", player[0]->score);
            rdpq_text_printf(&scoreTextParams, fontIdx, (textX*14)+4,  textY/2, "SCORE %d", player[1]->score);
            rdpq_text_printf(&scoreTextParams, fontIdx, textX, textY, "SCORE %d", player[2]->score);
            rdpq_text_printf(&scoreTextParams, fontIdx, (textX*14)+4, textY, "SCORE %d", player[3]->score);
        }
    } else {
        rdpq_text_printf(&scoreTextParams, fontIdx, textX, textY-18, "FPS\n""SCORE %d", player[0]->score);
    }

}

void print_controls(int fontIdx){
    textX  = 100;
    textY = 35;

    // Set up block for score
    if(!dplControls){
        rspq_block_begin();

        rdpq_sync_pipe();
        rdpq_sync_tile();

        rdpq_set_mode_standard();
        rdpq_mode_combiner(RDPQ_COMBINER1((0,0,0,PRIM), (PRIM,0,TEX0,0)));
        rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);

        rdpq_set_prim_color(T_BLACK);
        rdpq_sprite_upload(TILE1, spriteTextWindow, &textWindowParams);
        rdpq_sync_load(); //?

        // unhardcode?
        rdpq_texture_rectangle(TILE1, 85, 20, 235, 220, 0, 0);

        rdpq_text_print(&(rdpq_textparms_t){.disable_aa_fix = true, .align= ALIGN_CENTER, .style_id = STYLE_1,}, 
            fontIdx, 
            textX, textY, 
            "IBE: Itty Bitty Engine\n"
            "Game Engine for Tiny3D\n"
        );
        textY+=25;
        rdpq_text_printf(&(rdpq_textparms_t){.disable_aa_fix = true, .style_id = STYLE_1,}, fontIdx, textX+45, textY, "v%.1f.%u", VERSION, VERSION_SUFFIX);
        textY+=10;
        rdpq_text_print(&(rdpq_textparms_t){.disable_aa_fix = true, .style_id = STYLE_2,}, fontIdx, textX+40, textY, "by s4ys");
        textY+=15;

        rdpq_text_print(&(rdpq_textparms_t){.width = 125, .style_id = STYLE_0,}, 
            fontIdx, 
            textX, textY,   
            "Control Stick : Move\n"
            "A : Jump\n"
            "B : Attack\n"
            "C Down : Normal Cam\n"
            "C Left & Right :\n"
            "   Rotate Fixed Cam\n"
            "C Up : Top Down Cam\n"
            "Z : Recenter Cam\n"
            "Hold R : Debug\n"
            "Hold L : HitBoxes\n"
            //"Change font with D Pad"
        );

        dplControls = rspq_block_end();
    }

    rspq_block_run(dplControls);
}

void ui_update(void){

    print_score(nextFont);
    
    if(btn[0].start){
        if(isPaused == false){
            isPaused = true;
        } else {
            isPaused = false;
        }
    }

    if(isPaused){

        if(btn[0].d_left){
            if(nextFont > FONT_RESERVED_2 + 1){
                nextFont--;
            }
        }
        if(btn[0].d_right){
            if(nextFont < MAX_NUM_FONTS - 1){
                nextFont++;
            }
        }
        if(btn[0].d_down){
            if(xmID > 0){
                xmID--;
                switch_xm(xmID);
            }
        }
        if(btn[0].d_up){
            if(xmID < 4){
                xmID++;
                switch_xm(xmID);
            }
        }
        print_controls(nextFont);
    }
}