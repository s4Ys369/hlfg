#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3ddebug.h>
#include "../include/config.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "camera.h"
#include "debug.h"
#include "input.h"
#include "player.h"

T3DModel *modelDebugBox;
T3DModel *modelDebugSphere;
int col_debug;
float posX = 12;
float posY = 12;
int matCount = 0;
uint64_t timeMS = 0;

const char* playerStateStrings[NUM_PLAYER_STATES] = {
    "Idle",
    "Walk",
    "Jump Start",
    "Jump",
    "Attack Start",
    "Attack",
    "Fall",
    "Land"
};

void debug_models_init(void){
  col_debug = 0;
  modelDebugBox = t3d_model_load("rom:/box.t3dm");
  modelDebugSphere = t3d_model_load("rom:/sphere.t3dm");
}

// Function to print the contents of the stack memory as uint32_t values
void print_stack_memory_uint32(void *start, size_t size) {
    uint32_t *p = (uint32_t *)start;
    size_t num_elements = size / sizeof(uint32_t);
    for (size_t i = 0; i < num_elements; i++) {
        t3d_debug_printf(posX, posY, "0x%08x ", p[i]);posY+=10;
        if ((i + 1) % 4 == 0) {
            t3d_debug_printf(posX, posY, "\n");posY+=10;
        }
    }
    t3d_debug_printf(posX, posY, "\n");posY+=10;
}

void draw_debug_ui(void){
  t3d_debug_print_start();

  int text_debug = 0;

#ifndef DEBUG_PRINT
  if(btnheld[0].r){
    text_debug = 1;
  } else {
    text_debug = 0;
  }
#else
  text_debug = 1;
#endif

  if(btnheld[0].l){
    col_debug = 1;
  } else {
    col_debug = 0;
  }


  rdpq_set_prim_color(RGBA32(0xFF, 0xFF, 0xFF, 0xFF));
  if (text_debug){
    posY = 12;
    //player
    t3d_debug_printf(posX, posY, "X %.2f", player[0]->pos.v[0]);posY+=10;
    t3d_debug_printf(posX, posY, "Y %.2f", player[0]->pos.v[1]);posY+=10;
    t3d_debug_printf(posX, posY, "Z %.2f", player[0]->pos.v[2]);posY+=10;
    t3d_debug_printf(posX, posY, "State %s", playerStateStrings[playerState[0]]);posY+=10;
    t3d_debug_printf(posX, posY, "Grounded %d", player[0]->isGrounded);posY+=20;

    T3DVec3 NormA =find_closest_quad_from_verts(player[0]->pos, modelMap, 1);
    T3DVec3 NormB =find_closest_quad_from_verts(player[0]->pos, modelCrate, numCrates);
    T3DVec3 NormC =find_closest_quad_from_verts(player[0]->pos, modelBall, numBalls);
    t3d_debug_printf(posX, posY, "Map %.2f%.2f%.2f", NormA.v[0],NormA.v[1],NormA.v[2]);posY+=10;
    t3d_debug_printf(posX, posY, "Crate %.2f%.2f%.2f", NormB.v[0],NormB.v[1],NormB.v[2]);posY+=10;
    t3d_debug_printf(posX, posY, "Ball %.2f%.2f%.2f", NormC.v[0],NormC.v[1],NormC.v[2]);posY+=10;

    /*t3d_debug_printf(posX, posY, "Mat Count %u", matCount);posY+=10;
      if(matCount >= 8 && timeMS == 0){
        uint64_t nowMS = get_ticks_ms();
        timeMS = nowMS;
      }
      t3d_debug_printf(posX, posY, "Stack FULL at %llu", timeMS);posY+=10;
      print_stack_memory_uint32(???, 8 * sizeof(T3DMat4FP));
    */

    t3d_debug_printf(posX, 200, "FPS %.1f", display_get_fps());
  }
  
}