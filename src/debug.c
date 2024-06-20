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

  if(btnheld.r){
    text_debug = 1;
    col_debug = 1;
  } else {
    text_debug = 0;
    col_debug = 0;
  }

  if(btnheld.start){
    text_controls = 1;
  } else {
    text_controls = 0;
  }

  rdpq_set_prim_color(RGBA32(0xFF, 0xFF, 0xFF, 0xFF));
  if (text_debug){
    t3d_debug_printf(posX, posY, "X %.1f", tongue.hitbox.center.v[0]);
    t3d_debug_printf(posX, posY+10, "Y %.1f", tongue.hitbox.center.v[1]);
    t3d_debug_printf(posX, posY+20, "Z %.1f", tongue.hitbox.center.v[2]);
    t3d_debug_printf(posX, posY+30, "isGrounded: %s\n", isGrounded ? "true" : "false");
    if (isJumping)
    {
      t3d_debug_printf(posX, posY+40, "Jump");
    } else
    if (isWalking)
    {
      t3d_debug_printf(posX, posY+40, "Walk");
    } else
    if (isFalling)
    {
      t3d_debug_printf(posX, posY+40, "Fall");
    } else
    if (isJumpStart)
    {
      t3d_debug_printf(posX, posY+40, "JumpStart");
    } else { 
      t3d_debug_printf(posX, posY+40, "Idle");
    }
    t3d_debug_printf(posX, posY+50, "camPos\n");
    t3d_debug_printf(posX, posY+60, "%.0f %.0f %.0f\n", camPos.v[0], camPos.v[1], camPos.v[2]);
    t3d_debug_printf(posX, posY+70, "camFocus\n");
    t3d_debug_printf(posX, posY+80, "%.0f %.0f %.0f\n", camTarget.v[0], camTarget.v[1], camTarget.v[2]);
    t3d_debug_printf(posX, posY+90, "camMode%u", cam_mode);

    posY = 210;
    rdpq_set_prim_color(RGBA32(0xAA, 0xAA, 0xAA, 0xFF));
    t3d_debug_printf(posX, posY, "Speed: %.4f", currSpeed); posY += 10;
    t3d_debug_printf(posX, posY, "Blend: %.4f", animBlend); posY += 10;
  } else {
    rdpq_set_prim_color(RGBA32(0xAA, 0xAA, 0xAA, 0xFF));
    if (score < NUM_FLYS){
      t3d_debug_printf(posX, 200, "SCORE %d", score);
    } else {
      t3d_debug_printf(posX, 200, "You got em all!");
    }
    t3d_debug_printf(posX, 220, "FPS %.1f", display_get_fps());
  }

  if(text_controls){
    posX = 80;
    rdpq_set_prim_color(RGBA32(0xAA, 0xFF, 0xAA, 0xFF));
    t3d_debug_printf(posX, 50, "Happy Little Frog Game");
    t3d_debug_printf(posX+60, 60, "v%.1f", VERSION);
    rdpq_set_prim_color(RGBA32(0xFF, 0xAA, 0xAA, 0xFF));
    t3d_debug_printf(posX+50, 70, "by s4ys");
    rdpq_set_prim_color(RGBA32(0xFF, 0xFF, 0xFF, 0xFF));
    t3d_debug_printf(posX, 80, "Control Stick : Move");
    t3d_debug_printf(posX, 90, "A : Jump");
    t3d_debug_printf(posX, 100, "B : Attack");
    t3d_debug_printf(posX, 110, "C Down : Normal Cam");
    t3d_debug_printf(posX, 120, "C Left & Right :");
    t3d_debug_printf(posX+10, 130, "Rotate Fixed Cam");
    t3d_debug_printf(posX, 140, "C Up : Top Down Cam");
    t3d_debug_printf(posX, 150, "Z : Recenter Cam");
    t3d_debug_printf(posX, 160, "Hold R : Debug");
  }
}