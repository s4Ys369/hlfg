#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3ddebug.h>
#include "../include/config.h"
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "camera.h"
#include "collision.h"
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
    t3d_debug_printf(posX, posY, "Grounded %d", player[0]->isGrounded);posY+=10;
    t3d_debug_printf(posX, posY, "VX %.2f", player[0]->vel.v[0]);posY+=10;
    t3d_debug_printf(posX, posY, "VZ %.2f", player[0]->vel.v[2]);posY+=10;
    Surface dWall = find_closest_surface(player[0]->hitbox.center, Wall, wallCount);
    float dWf = distance_to_surface(player[0]->hitbox.center,dWall);
    Surface dFloor = find_closest_surface(player[0]->hitbox.center, Floor, floorCount);
    float dFf = distance_to_surface(player[0]->hitbox.center,dFloor);
    Surface dSlope = find_closest_surface(player[0]->hitbox.center, Slope, slopeCount);
    float dSf = distance_to_surface(player[0]->hitbox.center,dSlope);
    t3d_debug_printf(posX, posY, "Wall %d", check_sphere_surface_collision(player[0]->hitbox, dWall));posY+=10;
    t3d_debug_printf(posX, posY, "%.2f", dWf);posY+=10;
    t3d_debug_printf(posX, posY, "Floor %d", check_sphere_surface_collision(player[0]->hitbox, dFloor));posY+=10;
    t3d_debug_printf(posX, posY, "%.2f", dFf);posY+=10;
    t3d_debug_printf(posX, posY, "Slope %d", check_sphere_surface_collision(player[0]->hitbox, dSlope));posY+=10;
    t3d_debug_printf(posX, posY, "%.2f", dSf);posY+=10;

    /*
    t3d_debug_printf(posX, posY, "Mat Count %u", matCount);posY+=10;
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