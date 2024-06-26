#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3ddebug.h>
#include "../include/globals.h"
#include "../include/types.h"
#include "camera.h"
#include "debug.h"
#include "input.h"
#include "player.h"

T3DModel *modelDebugBox;
T3DModel *modelDebugSphere;
int col_debug;

void debug_models_init(void){
  col_debug = 0;
  modelDebugBox = t3d_model_load("rom:/box.t3dm");
  modelDebugSphere = t3d_model_load("rom:/testsphere.t3dm");
}
void draw_debug_ui(void){
  t3d_debug_print_start();

  float posX = 12;
  float posY = 12;

  int text_debug = 0;
  int text_controls = 0;

  if(btnheld[0].r){
    text_debug = 1;
  } else {
    text_debug = 0;
  }

  if(btnheld[0].l){
    col_debug = 1;
  } else {
    col_debug = 0;
  }

  if(btnheld[0].start){
    text_controls = 1;
  } else {
    text_controls = 0;
  }

  rdpq_set_prim_color(RGBA32(0xFF, 0xFF, 0xFF, 0xFF));
  if (text_debug){
    t3d_debug_printf(posX, posY, "X %.2f", player[0].playerPos.v[0]);posY+=10;
    t3d_debug_printf(posX, posY, "Y %.2f", player[0].playerPos.v[1]);posY+=10;
    t3d_debug_printf(posX, posY, "Z %.2f", player[0].playerPos.v[2]);posY+=10;
    t3d_debug_printf(posX, posY, "TH Y %.2f", player[0].tongue[0].hitbox.center.v[1]);posY+=10;
    t3d_debug_printf(posX, posY, "TP Y %.2f", player[0].tongue[0].pos.v[1]);posY+=10;
    t3d_debug_printf(posX, posY, "DT %.2f", deltaTime);posY+=10;
    t3d_debug_printf(posX, posY, "JT %.2f", jumpTime);
  }
  
  posY = 200;
  rdpq_set_prim_color(RGBA32(0xAA, 0xAA, 0xAA, 0xFF));
  if(NUM_PLAYERS > 1) {
    if(NUM_PLAYERS == 2) {
      t3d_debug_printf(posX, posY/2, "SCORE %d", player[0].score);
      t3d_debug_printf(posX, posY, "SCORE %d", player[1].score);
    }
    if(NUM_PLAYERS == 3) {
      t3d_debug_printf(posX, posY/2, "SCORE %d", player[0].score);
      t3d_debug_printf(posX, posY, "SCORE %d", player[1].score);
      t3d_debug_printf((posX*14)+4,  posY, "SCORE %d", player[2].score);
    }
    if(NUM_PLAYERS == 4) {
      t3d_debug_printf(posX, posY/2, "SCORE %d", player[0].score);
      t3d_debug_printf((posX*14)+4,  posY/2, "SCORE %d", player[1].score);
      t3d_debug_printf(posX, posY, "SCORE %d", player[2].score);
      t3d_debug_printf((posX*14)+4, posY+20, "SCORE %d", player[3].score);
    }
  } else {
    t3d_debug_printf(posX, posY, "SCORE %d", player[0].score);
  }


  t3d_debug_printf(posX, posY+20, "FPS %.1f", display_get_fps());
  

  if(text_controls){
    posX = 80;
    posY = 50;
    rdpq_set_prim_color(RGBA32(0xAA, 0xFF, 0xAA, 0xFF));
    t3d_debug_printf(posX, posY, "Happy Little Frog Game");posY+=10;
    t3d_debug_printf(posX+55, posY, "v%.1f.%u", VERSION, VERSION_SUFFIX);posY+=10;
    rdpq_set_prim_color(RGBA32(0xFF, 0xAA, 0xAA, 0xFF));posY+=10;
    t3d_debug_printf(posX+50, posY, "by s4ys");posY+=10;
    rdpq_set_prim_color(RGBA32(0xFF, 0xFF, 0xFF, 0xFF));
    t3d_debug_printf(posX, posY, "Control Stick : Move");posY+=10;
    t3d_debug_printf(posX, posY, "A : Jump");posY+=10;
    t3d_debug_printf(posX, posY, "B : Attack");posY+=10;
    t3d_debug_printf(posX, posY, "C Down : Normal Cam");posY+=10;
    t3d_debug_printf(posX, posY, "C Left & Right :");posY+=10;
    t3d_debug_printf(posX+10, posY, "Rotate Fixed Cam");posY+=10;
    t3d_debug_printf(posX, posY, "C Up : Top Down Cam");posY+=10;
    t3d_debug_printf(posX, posY, "Z : Recenter Cam");posY+=10;
    t3d_debug_printf(posX, posY, "Hold R : Debug");
  }
}