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
  modelDebugBox = t3d_model_load("rom:/models/box.t3dm");
  modelDebugSphere = t3d_model_load("rom:/models/sphere.t3dm");

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
        rdpq_text_printf(NULL, nextFont, posX, posY, "%lu", p[i]);posY+=10;
        if ((i + 1) % 4 == 0) {
            rdpq_text_printf(NULL, nextFont, posX, posY, "\n");posY+=10;
        }
    }
    rdpq_text_printf(NULL, nextFont, posX, posY, "\n");posY+=10;
}

void draw_debug_ui(void){

  int text_debug = 0;

  rdpq_textparms_t textParams = {
    .width = 100,
    .height = 100,
    .disable_aa_fix = true,
    .style_id = STYLE_DEBUG,
  };

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

  float fps = display_get_fps();
  uint8_t fpsCheck = STYLE_DEBUG;
  if (fps >= 40){
    fpsCheck = STYLE_DB_PASS;
  } else if (fps >= 25) {
    fpsCheck = STYLE_DEBUG;
  } else {
    fpsCheck = STYLE_DB_FAIL;
  }

  rdpq_load_tile(TILE5,0,0,32,32);
  rdpq_set_prim_color(T_BLACK);
  rdp_draw_textured_rectangle_scaled(TILE5, 10, 191, 56, 205, 1,1, MIRROR_XY);
  // not sure why RDP & RDPQ don't like the tiles
  //rdpq_texture_rectangle_raw(TILE5, 12, 203, 55, 211, 0,0,1,1); // pos[n] * 13.33333 for columns and rows
  rdpq_text_printf(&textParams, nextFont, 12, 191, "FPS");
  rdpq_text_printf(&(rdpq_textparms_t){
    .width = 22,
    .height = 20,
    .align = ALIGN_RIGHT,
    .disable_aa_fix = true,
    .style_id = fpsCheck,
  }, nextFont, 32, 191, "%.1f", display_get_fps());
  
  if (text_debug){
    posY = 12;
    rdpq_set_prim_color(T_BLACK);
    rdp_draw_textured_rectangle_scaled(TILE5, 10, 10, 80, 180, 1,1, MIRROR_XY);
    // Player
    rdpq_text_printf(&textParams, nextFont, posX, posY, "X %.2f", player[0]->pos.v[0]);posY+=10;
    rdpq_text_printf(&textParams, nextFont, posX, posY, "Y %.2f", player[0]->pos.v[1]);posY+=10;
    rdpq_text_printf(&textParams, nextFont, posX, posY, "Z %.2f", player[0]->pos.v[2]);posY+=10;
    rdpq_text_printf(&textParams, nextFont, posX, posY, "State %s", playerStateStrings[playerState[0]]);posY+=10;
    rdpq_text_printf(&textParams, nextFont, posX, posY, "Grounded %d", player[0]->isGrounded);posY+=20;

    // Surfaces
    Surface dWall = find_closest_surface(player[0]->hitbox.center, testLevelWall, testLevelWallCount);
    Surface dFloor = find_closest_surface(player[0]->hitbox.center, testLevelFloor, testLevelFloorCount);
    Surface dSlope = find_closest_surface(player[0]->hitbox.center, testLevelSlope, testLevelSlopeCount);
    rdpq_text_printf(&textParams, nextFont, posX, posY, "Wall %d", check_sphere_surface_collision(player[0]->hitbox, dWall));posY+=10;
    rdpq_text_printf(&textParams, nextFont, posX, posY, "Floor %d", check_sphere_surface_collision(player[0]->hitbox, dFloor));posY+=10;
    rdpq_text_printf(&textParams, nextFont, posX, posY, "Slope %d", check_sphere_surface_collision(player[0]->hitbox, dSlope));posY+=20;

    // Actors
    int dBall = find_closest(player[0]->hitbox.center, balls, numBalls);
    float dDistBall = t3d_vec3_distance(&player[0]->hitbox.center, &balls[dBall]->hitbox.shape.sphere.center);
    bool dHitBall = check_sphere_collision(player[0]->hitbox, balls[dBall]->hitbox.shape.sphere);
    int dCrate = find_closest(player[0]->hitbox.center, crates, numCrates);
    float dDistCrate = t3d_vec3_distance(&player[0]->hitbox.center, &crates[dCrate]->hitbox.shape.aabb.min);
    bool dHitCrate = check_sphere_box_collision(player[0]->hitbox, crates[dCrate]->hitbox.shape.aabb);
    rdpq_text_printf(&textParams, nextFont, posX, posY, "Ball %d", dHitBall);posY+=10;
    rdpq_text_printf(&textParams, nextFont, posX+5, posY, "Dist %.2f", dDistBall);posY+=20;

    rdpq_text_printf(&textParams, nextFont, posX, posY, "Box %d", dHitCrate);posY+=10;
    rdpq_text_printf(&textParams, nextFont, posX+5, posY, "Dist %.2f", dDistCrate);posY+=20;

    /*
    rdpq_text_printf(NULL, nextFont, posX, posY, "Mat Count %u", matCount);posY+=10;
    if(matCount >= 8 && timeMS == 0){
      uint64_t nowMS = get_ticks_ms();
      timeMS = nowMS;
    }
    rdpq_text_printf(NULL, nextFont, posX, posY, "Stack FULL at %llu", timeMS);posY+=10;
    print_stack_memory_uint32(???, 8 * sizeof(T3DMat4FP));
    */
  }

}