#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3ddebug.h>
#include <t3d/t3dmath.h>
#include "../include/config.h"
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "camera.h"
#include "collision.h"
#include "debug.h"
#include "input.h"
#include "player.h"
#include "utils.h"

T3DModel *modelDebugBox;
T3DModel *modelDebugSphere;
T3DVertPacked* triVerts;
T3DMat4FP* triangleMatFP;
rspq_block_t *dplTri;
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
    "Land",
    "Slide"
};

void debug_models_init(void){
  col_debug = 0;
  modelDebugBox = t3d_model_load("rom:/box.t3dm");
  modelDebugSphere = t3d_model_load("rom:/sphere.t3dm");

  triVerts = malloc_uncached(sizeof(T3DVertPacked) * 2);

  uint16_t norm = t3d_vert_pack_normal(&(T3DVec3){{ 0, 0, 1}});
  triVerts[0] = (T3DVertPacked){
    .posA = {0,0,0}, .rgbaA = 0xFF0000'FF, .normA = norm,
    .posB = {32,0,32}, .rgbaB = 0x00FF00'FF, .normB = norm,
  };
  triVerts[1] = (T3DVertPacked){
    .posA = {64,0,64}, .rgbaA = 0x0000FF'FF, .normA = norm,
    .posB = {0,0,0}, .rgbaB = 0xFF00FF'FF, .normB = norm,
  };
 
  triangleMatFP = malloc_uncached(sizeof(T3DMat4FP));
  t3d_mat4fp_from_srt_euler(triangleMatFP, (float[3]){1.0f, 1.0f, 1.0f}, (float[3]){0, 0, 0}, (float[3]){0, 0, 0});
  
  rspq_block_begin();
    t3d_matrix_push_pos(1);
    t3d_matrix_set(triangleMatFP, true);
    t3d_vert_load(triVerts, 62, 4);
    t3d_tri_draw(0, 1, 2);
    t3d_tri_sync();
    t3d_matrix_pop(1);

  dplTri = rspq_block_end();

  rspq_block_run(dplTri);

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
    // Player
    t3d_debug_printf(posX, posY, "X %.2f", player[0]->pos.v[0]);posY+=10;
    t3d_debug_printf(posX, posY, "Y %.2f", player[0]->pos.v[1]);posY+=10;
    t3d_debug_printf(posX, posY, "Z %.2f", player[0]->pos.v[2]);posY+=10;
    t3d_debug_printf(posX, posY, "State %s", playerStateStrings[playerState[0]]);posY+=10;
    t3d_debug_printf(posX, posY, "Grounded %d", player[0]->isGrounded);posY+=10;

    // Surfaces
    Surface dWall = find_closest_surface(player[0]->hitbox.center, Wall, wallCount);
    float dWf = distance_to_surface(player[0]->hitbox.center,dWall);
    float dWc = t3d_vec3_distance(&player[0]->hitbox.center, &dWall.center);
    Surface dFloor = find_closest_surface(player[0]->hitbox.center, Floor, floorCount);
    float dFf = distance_to_surface(player[0]->hitbox.center,dFloor);
    float dFc = t3d_vec3_distance(&player[0]->hitbox.center, &dFloor.normal);
    Surface dSlope = find_closest_surface(player[0]->hitbox.center, Slope, slopeCount);
    float dSf = distance_to_surface(player[0]->hitbox.center,dSlope);
    float dSc = t3d_vec3_distance(&player[0]->hitbox.center, &dSlope.center);
    t3d_debug_printf(posX, posY, "Wall %d", check_sphere_surface_collision(player[0]->hitbox, dWall));posY+=10;
    t3d_debug_printf(posX, posY, "%.2f", dWf);posY+=10;
    t3d_debug_printf(posX, posY, "%.2f", dWc);posY+=10;
    t3d_debug_printf(posX, posY, "Floor %d", check_sphere_surface_collision(player[0]->hitbox, dFloor));posY+=10;
    t3d_debug_printf(posX, posY, "%.2f", dFf);posY+=10;
    t3d_debug_printf(posX, posY, "%.2f", dFc);posY+=10;
    t3d_debug_printf(posX, posY, "Slope %d", check_sphere_surface_collision(player[0]->hitbox, dSlope));posY+=10;
    t3d_debug_printf(posX, posY, "%.2f", dSf);posY+=10;
    t3d_debug_printf(posX, posY, "%.2f", dSc);posY+=10;

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

    
  //.posA = {dWall.posA.v[0],dWall.posA.v[1],dWall.posA.v[2]}, .rgbaA = 0xFF0000'FF, .normA = norm,
  //.posB = {dWall.posB.v[0],dWall.posB.v[1],dWall.posB.v[2]}, .rgbaB = 0x00FF00'FF, .normB = norm,

  //.posA = {dWall.posC.v[0],dWall.posC.v[1],dWall.posC.v[2]}, .rgbaA = 0x0000FF'FF, .normA = norm,
  //.posB = {dWall.posA.v[0],dWall.posA.v[1],dWall.posA.v[2]}, .rgbaB = 0xFF00FF'FF, .normB = norm,
    
  
}