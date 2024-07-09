#include <libdragon.h>
#include <t3d/t3d.h>
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
#include "ui.h"
#include "utils.h"
#include "test_level.h"

T3DModel *modelDebugBox;
T3DModel *modelDebugSphere;
T3DVertPacked* triVerts;
T3DMat4FP* triangleMatFP;
rspq_block_t *dplTri;
rspq_block_t *dplDebugText;
int col_debug;
int text_debug;
float posX = 12;
float posY = 12;
int matCount = 0;
uint64_t timeMS = 0;
rspq_syncpoint_t syncPoint;


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
  text_debug = 0;
  col_debug = 0;
  modelDebugBox = t3d_model_load("rom:/models/box.t3dm");
  modelDebugSphere = t3d_model_load("rom:/models/sphere.t3dm");

  dplDebugText = NULL;

  //triVerts = malloc_uncached(sizeof(T3DVertPacked) * 2);
  //
  //uint16_t norm = t3d_vert_pack_normal(&(T3DVec3){{ 0, 0, 1}});
  //triVerts[0] = (T3DVertPacked){
  //  .posA = {0,0,0}, .rgbaA = 0xFF0000'FF, .normA = norm,
  //  .posB = {32,0,32}, .rgbaB = 0x00FF00'FF, .normB = norm,
  //};
  //triVerts[1] = (T3DVertPacked){
  //  .posA = {64,0,64}, .rgbaA = 0x0000FF'FF, .normA = norm,
  //  .posB = {0,0,0}, .rgbaB = 0xFF00FF'FF, .normB = norm,
  //};
  //
  //triangleMatFP = malloc_uncached(sizeof(T3DMat4FP));
  //t3d_mat4fp_from_srt_euler(triangleMatFP, (float[3]){1.0f, 1.0f, 1.0f}, (float[3]){0, 0, 0}, (float[3]){0, 0, 0});
  //
  //rspq_block_begin();
  //  t3d_matrix_push_pos(1);
  //  t3d_matrix_set(triangleMatFP, true);
  //  t3d_vert_load(triVerts, 62, 4);
  //  t3d_tri_draw(0, 1, 2);
  //  t3d_tri_sync();
  //  t3d_matrix_pop(1);
  //
  //dplTri = rspq_block_end();
  //
  //rspq_block_run(dplTri);

}

// Function to print the contents of the stack memory as uint32_t values
void print_stack_memory_uint32(void *start, size_t size) {
    uint32_t *p = (uint32_t *)start;
    size_t num_elements = size / sizeof(uint32_t);
    for (size_t i = 0; i < num_elements; i++) {
        rdpq_text_printf(NULL, nextFont, posX, posY, "%lu", p[i]);posY+=10;
        if ((i + 1) % 4 == 0) {
            rdpq_text_printf(NULL, nextFont, posX, posY, "\n");posY+=10;
        }
    }
    rdpq_text_printf(NULL, nextFont, posX, posY, "\n");posY+=10;
}

void draw_debug_ui(void){

  float fps = display_get_fps();
  uint8_t fpsCheck = STYLE_DEBUG;
  if (fps >= 30){
      fpsCheck = STYLE_DB_PASS;
  } else if (fps >= 20) {
      fpsCheck = STYLE_DEBUG;
  } else {
      fpsCheck = STYLE_DB_FAIL;
  }

  rdpq_textparms_t textParams = {
    .width = 100,
    .height = 100,
    .disable_aa_fix = true,
    .style_id = STYLE_DEBUG,
  };

  // Print FPS
  rdpq_text_printf(&(rdpq_textparms_t){
      .width = 30,
      .height = 20,
      .align = ALIGN_RIGHT,
      .disable_aa_fix = true,
      .style_id = fpsCheck,
  }, nextFont, 32, 191, "%.2f", display_get_fps());


  // Set debug text block
  if(!dplDebugText){
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
    rdpq_texture_rectangle(TILE1, 10, 10, 80, 190, 0, 0);

    dplDebugText = rspq_block_end();

  }

  if(text_debug){
    posY=12;
    rspq_block_run(dplDebugText);

    // Player
    rdpq_text_printf(
      &textParams, 
      nextFont,
      posX, posY, 
      "X %.2f\n"
      "Y %.2f\n"
      "Z %.2f\n"
      "State %s\n"
      "Grounded %d", 
      player[0]->pos.v[0],
      player[0]->pos.v[1],
      player[0]->pos.v[2],
      playerStateStrings[playerState[0]],
      player[0]->isGrounded
    );

    posY+=65;

    // Surfaces
    Surface dWall = find_closest_surface(player[0]->hitbox.center, testLevelWall, testLevelWallCount);
    Surface dFloor = find_closest_surface(player[0]->hitbox.center, testLevelFloor, testLevelFloorCount);
    Surface dSlope = find_closest_surface(player[0]->hitbox.center, testLevelSlope, testLevelSlopeCount);
    rdpq_text_printf(
      &textParams, 
      nextFont,
      posX, posY, 
      "Wall %d\n"
      "Floor %d\n"
      "Slope %d", 
      check_sphere_surface_collision(player[0]->hitbox, dWall),
      check_sphere_surface_collision(player[0]->hitbox, dFloor),
      check_sphere_surface_collision(player[0]->hitbox, dSlope)
    );

    posY+=45;

    // Actors
    int dBall = find_closest(player[0]->hitbox.center, balls, numBalls);
    float dDistBall = t3d_vec3_distance(&player[0]->hitbox.center, &balls[dBall]->hitbox.shape.sphere.center);
    bool dHitBall = check_sphere_collision(player[0]->hitbox, balls[dBall]->hitbox.shape.sphere);
    int dCrate = find_closest(player[0]->hitbox.center, crates, numCrates);
    float dDistCrate = t3d_vec3_distance(&player[0]->hitbox.center, &crates[dCrate]->hitbox.shape.aabb.min);
    bool dHitCrate = check_sphere_box_collision(player[0]->hitbox, crates[dCrate]->hitbox.shape.aabb);

    rdpq_text_printf(
      &textParams, 
      nextFont,
      posX, posY, 
      "Ball %d\n"
      "   Dist %.2f\n"
      "Box %d\n"
      "   Dist %.2f", 
      dHitBall,
      dDistBall,
      dHitCrate,
      dDistCrate
    );

    posY+=55;
    
    rdpq_text_printf(&textParams, nextFont, posX, posY, "Mats %u", matCount);
    
    /*
    posY+=10;
    print_stack_memory_uint32(???, 8 * sizeof(T3DMat4FP));
    */

  }

#ifndef FORCE_DEBUG_PRINT
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

}