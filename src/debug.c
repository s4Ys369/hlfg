#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include <malloc.h>
#include "../include/config.h"
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "camera.h"
#include "collision.h"
#include "debug.h"
#include "input.h"
#include "levels.h"
#include "map.h"
#include "player.h"
#include "ui.h"
#include "utils.h"

T3DModel *modelDebugBox;
T3DModel *modelDebugSphere;
T3DVertPacked* triVerts;
T3DMat4FP* triangleMatFP;
rspq_block_t *dplFloorTri;
rspq_block_t *dplSlopeTri;
rspq_block_t *dplWallTri;
rspq_block_t *dplDebugText;
int col_debug;
int text_debug;
int debug_mode = DEBUG_RENDER_ALL;
int col_floor = 0;
int col_slope = 0;
int col_wall = 0;
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

const char* debugModeStrings[NUM_DEBUG_MODES] = {
    "Render All",
    "Hide Level",
    "Hide Objects",
    "Hide All"
};

void debug_models_init(void){
  text_debug = 0;
  col_debug = 0;
  modelDebugBox = t3d_model_load("rom:/models/box.t3dm");
  modelDebugSphere = t3d_model_load("rom:/models/debugsphere.t3dm");

  dplDebugText = NULL;
  dplFloorTri = NULL;
  dplSlopeTri = NULL;
  dplWallTri = NULL;

  triVerts = malloc_uncached(sizeof(T3DVertPacked) * 6);
  
  uint16_t norm = t3d_vert_pack_normal(&(T3DVec3){{ 0, 0, 1}});
  triVerts[0] = (T3DVertPacked){
    .posA = {0,0,0}, .rgbaA = 0xFF0000'7F, .normA = norm,
    .posB = {32,0,32}, .rgbaB = 0x00FF00'7F, .normB = norm,
  };
  triVerts[1] = (T3DVertPacked){
    .posA = {64,0,64}, .rgbaA = 0x0000FF'99, .normA = norm,
    .posB = {0,0,0}, .rgbaB = 0xFF00FF'99, .normB = norm,
  };
  triVerts[2] = (T3DVertPacked){
    .posA = {0,0,0}, .rgbaA = 0xFF0000'7F, .normA = norm,
    .posB = {32,0,32}, .rgbaB = 0x00FF00'7F, .normB = norm,
  };
  triVerts[3] = (T3DVertPacked){
    .posA = {64,0,64}, .rgbaA = 0x0000FF'99, .normA = norm,
    .posB = {0,0,0}, .rgbaB = 0xFF00FF'99, .normB = norm,
  };
  triVerts[4] = (T3DVertPacked){
    .posA = {0,0,0}, .rgbaA = 0xFF0000'7F, .normA = norm,
    .posB = {32,0,32}, .rgbaB = 0x00FF00'7F, .normB = norm,
  };
  triVerts[5] = (T3DVertPacked){
    .posA = {64,0,64}, .rgbaA = 0x0000FF'99, .normA = norm,
    .posB = {0,0,0}, .rgbaB = 0xFF00FF'99, .normB = norm,
  };
  
  triangleMatFP = malloc_uncached(sizeof(T3DMat4FP));
  t3d_mat4fp_from_srt_euler(triangleMatFP, (float[3]){1.0f, 1.0f, 1.0f}, (float[3]){0, 0, 0}, (float[3]){0, 0, 0});

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
    .height = 200,
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

    rdpq_mode_begin();
      rdpq_sync_pipe();
      rdpq_sync_tile();
      rdpq_set_mode_standard();
      rdpq_mode_combiner(RDPQ_COMBINER1((0,0,0,PRIM), (PRIM,0,TEX0,0)));
      rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
    rdpq_mode_end();
    
    rdpq_set_prim_color(T_BLACK);
    rdpq_sprite_upload(TILE1, spriteTextWindow, &textWindowParams);
    
    // unhardcode?
    rdpq_texture_rectangle(TILE1, 10, 10, 80, 190, 0, 0);

    dplDebugText = rspq_block_end();

  }

  if(text_debug){
    posY=12;
    rspq_block_run(dplDebugText);

    // Fazana's Puppyprint RAM used
    //struct mallinfo mem_info = mallinfo();
    //int ramUsed = mem_info.uordblks - (size_t) (((display_get_width() * display_get_height()) * 2) - ((unsigned int) HEAP_START_ADDR - 0x80000000) - 0x10000);
    //rdpq_text_printf(NULL, nextFont, posX+ 100, posY + 20, "RAM %dKB/%dKB", (ramUsed / 1024), get_memory_size() / 1024);

    if(!isPaused){
      if(btn[0].d_left){
        if(debug_mode > DEBUG_RENDER_ALL){
            debug_mode--;
        }
      }
      if(btn[0].d_right){
        if(debug_mode < DEBUG_HIDE_ALL){
          debug_mode++;
        }
      }
    }

    // Player
    rdpq_text_printf(
      &textParams, 
      nextFont,
      posX, posY, 
      "X %.2f\n"
      "Y %.2f\n"
      "Z %.2f\n"
      "State %s\n"
      "Grounded %d\n"
      "Speed %.2f\n"
      "%s\n"
      "Rumble\n"
      "Detected %d\n"
      "Active %d", 
      player[0]->pos.v[0],
      player[0]->pos.v[1],
      player[0]->pos.v[2],
      playerStateStrings[playerState[0]],
      player[0]->isGrounded,
      player[0]->currSpeed,
      debugModeStrings[debug_mode],
      rumble_supported[0],
      rumble_active[0]
    );
    


    /* Surfaces
    Surface dWall = find_closest_surface(player[0]->hitbox.center, levels[currLevel].walls, levels[currLevel].wallCount);
    Surface dFloor = find_closest_surface(player[0]->hitbox.center, levels[currLevel].floors, levels[currLevel].floorCount);
    Surface dSlope = find_closest_surface(player[0]->hitbox.center, levels[currLevel].slopes, levels[currLevel].slopeCount);
    T3DVec3 dSlopeNormal = calc_surface_norm(dSlope);
    T3DVec3 dFloorNormal = calc_surface_norm(dFloor);
    T3DVec3 dWallNormal = calc_surface_norm(dWall);
    t3d_vec3_norm(&dSlopeNormal);
    t3d_vec3_norm(&dFloorNormal);
    t3d_vec3_norm(&dWallNormal);

    T3DVec3 forward = player[0]->forward;
    //float dotNorth = t3d_vec3_dot(&forward, &nearer);
    //float dotSouth = t3d_vec3_dot(&forward, &farther);
    //float dotEast = t3d_vec3_dot(&forward, &right);
    //float dotWest = t3d_vec3_dot(&forward, &left);
    rdpq_text_printf(
      &textParams, 
      nextFont,
      posX, posY, 
      "X %.2f\n"
      "Z %.2f\n"
      "Pitch %.2f\n"
      "Yaw %.2f\n"
      "Roll %.2f\n"
      "SP %.2f\n"
      "SR %.2f\n"
      "Forward\n" 
      " %.2f,\n %.2f,\n %.2f\n"
      "Slope Normal\n"
      " %.2f,\n %.2f,\n %.2f",
      player[0]->pos.v[0], player[0]->pos.v[2],
      player[0]->rot.v[0], player[0]->rot.v[1], player[0]->rot.v[2],
      player[0]->shadowRot.v[0], player[0]->shadowRot.v[2],
      forward.v[0], forward.v[1], forward.v[2],
      dSlopeNormal.v[0], dSlopeNormal.v[1], dSlopeNormal.v[2]
    );
    */

    /* Actors
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
    
    //rdpq_text_printf(&textParams, nextFont, posX, posY, "Mats %u", matCount);
    
    
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

  if(btnheld[0].l && numPlayers == 1){
    col_debug = 1;
    Surface cFloor = find_closest_surface(player[0]->hitbox.center, levels[currLevel].floors, levels[currLevel].floorCount);
    Surface cWall = find_closest_surface(player[0]->hitbox.center, levels[currLevel].walls, levels[currLevel].wallCount);
    Surface cSlope = find_closest_surface(player[0]->hitbox.center, levels[currLevel].slopes, levels[currLevel].slopeCount);
    if(check_sphere_surface_collision(player[0]->hitbox, cFloor)){
      col_floor = 1;
      triVerts[0].posA[0] = (int16_t)(cFloor.posA.v[0]);
      triVerts[0].posA[1] = (int16_t)(cFloor.posA.v[1]);
      triVerts[0].posA[2] = (int16_t)(cFloor.posA.v[2]);

      triVerts[0].posB[0] = (int16_t)(cFloor.posB.v[0]);
      triVerts[0].posB[1] = (int16_t)(cFloor.posB.v[1]);
      triVerts[0].posB[2] = (int16_t)(cFloor.posB.v[2]);

      triVerts[1].posA[0] = (int16_t)(cFloor.posC.v[0]);
      triVerts[1].posA[1] = (int16_t)(cFloor.posC.v[1]);
      triVerts[1].posA[2] = (int16_t)(cFloor.posC.v[2]);

      if(!dplFloorTri) {
        rspq_block_begin();
          rdpq_mode_begin();
            rdpq_sync_pipe();
            rdpq_set_mode_standard();
            rdpq_mode_combiner(RDPQ_COMBINER_SHADE);
            t3d_state_set_drawflags(T3D_FLAG_SHADED | T3D_FLAG_DEPTH);
            rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
          rdpq_mode_end();

          t3d_matrix_push(triangleMatFP);
          t3d_vert_load(triVerts, 0, 12);
          t3d_matrix_pop(1);
          t3d_tri_draw(0, 1, 2);
          t3d_tri_sync();
        dplFloorTri = rspq_block_end();
      }
    } else {
      col_floor = 0;
    }
    if(check_sphere_surface_collision(player[0]->hitbox, cSlope)){
      col_slope = 1;
      triVerts[2].posA[0] = (int16_t)(cSlope.posA.v[0]);
      triVerts[2].posA[1] = (int16_t)(cSlope.posA.v[1]);
      triVerts[2].posA[2] = (int16_t)(cSlope.posA.v[2]);

      triVerts[2].posB[0] = (int16_t)(cSlope.posB.v[0]);
      triVerts[2].posB[1] = (int16_t)(cSlope.posB.v[1]);
      triVerts[2].posB[2] = (int16_t)(cSlope.posB.v[2]);

      triVerts[3].posA[0] = (int16_t)(cSlope.posC.v[0]);
      triVerts[3].posA[1] = (int16_t)(cSlope.posC.v[1]);
      triVerts[3].posA[2] = (int16_t)(cSlope.posC.v[2]);

      if(!dplSlopeTri) {
        rspq_block_begin();
          rdpq_mode_begin();
            rdpq_sync_pipe();
            rdpq_set_mode_standard();
            rdpq_mode_combiner(RDPQ_COMBINER_SHADE);
            t3d_state_set_drawflags(T3D_FLAG_SHADED | T3D_FLAG_DEPTH);
            rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
          rdpq_mode_end();

          t3d_matrix_push(triangleMatFP);
          t3d_vert_load(triVerts, 0, 12);
          t3d_matrix_pop(1);
          t3d_tri_draw(4, 5, 6);

          t3d_tri_sync();
        dplSlopeTri = rspq_block_end();
      }
    } else {
      col_slope = 0;
    }
    if(check_sphere_surface_collision(player[0]->hitbox, cWall)){
      col_wall = 1;

      triVerts[4].posA[0] = (int16_t)(cWall.posA.v[0]);
      triVerts[4].posA[1] = (int16_t)(cWall.posA.v[1]);
      triVerts[4].posA[2] = (int16_t)(cWall.posA.v[2]);

      triVerts[4].posB[0] = (int16_t)(cWall.posB.v[0]);
      triVerts[4].posB[1] = (int16_t)(cWall.posB.v[1]);
      triVerts[4].posB[2] = (int16_t)(cWall.posB.v[2]);

      triVerts[5].posA[0] = (int16_t)(cWall.posC.v[0]);
      triVerts[5].posA[1] = (int16_t)(cWall.posC.v[1]);
      triVerts[5].posA[2] = (int16_t)(cWall.posC.v[2]);

      if(!dplWallTri) {
        rspq_block_begin();
          rdpq_mode_begin();
            rdpq_sync_pipe();
            rdpq_set_mode_standard();
            rdpq_mode_combiner(RDPQ_COMBINER_SHADE);
            t3d_state_set_drawflags(T3D_FLAG_SHADED | T3D_FLAG_DEPTH);
            rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
          rdpq_mode_end();

          t3d_matrix_push(triangleMatFP);
          t3d_vert_load(triVerts, 0, 12);
          t3d_matrix_pop(1);
          t3d_tri_draw(8, 9, 10);

          t3d_tri_sync();
        dplWallTri = rspq_block_end();
      }
    } else {
      col_wall = 0;
    }
  } else {
    col_debug = 0;
    col_floor = 0;
    col_slope = 0;
    col_wall = 0;
  }

}