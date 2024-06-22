#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3ddebug.h>
#include "../include/config.h"
#include "../include/types.h"
#include "actors.h"
#include "camera.h"
#include "collision.h"
#include "debug.h"
#include "input.h"
#include "map.h"
#include "player.h"
#include "sound.h"
#include "utils.h"

// HAPPY LITTLE FROG GAME

int main()
{
  debug_init_isviewer();
  debug_init_usblog();
  asset_init_compression(2);

  dfs_init(DFS_DEFAULT_LOCATION);

  display_init(RESOLUTION_320x240, DEPTH_16_BPP, 3, GAMMA_NONE, FILTERS_RESAMPLE_ANTIALIAS);
  surface_t depthBuffer = surface_alloc(FMT_RGBA16, display_get_width(), display_get_height());

  rdpq_init();
  joypad_init();

  t3d_init((T3DInitParams){});
  t3d_debug_print_init();
  

  T3DVec3 lightDirVec = {{1.0f, 1.0f, 1.0f}};
  t3d_vec3_norm(&lightDirVec);

  uint8_t colorAmbient[4] = {0xAA, 0xAA, 0xAA, 0xFF};
  uint8_t colorDir[4]     = {0xFF, 0xAA, 0xAA, 0xFF};

  debug_models_init();
  actors_init();
  player_init();
  cam_init();
  sound_init();
  map_init();

  lastTime = get_last_time();
  rspq_syncpoint_t syncPoint = 0;

  for(;;)
  {
    // ======== Update ======== //

    input_update();

    get_delta_time();
    //float frameRate = display_get_fps();
    //if (frameRate >= 30.0f) {
    //  limit_FPS(30.0f);
    //}

    if (!btnheld.start){
      sound_update_buffer();
  
      // CAMERA_LOGIC
      cam_update();
  
      //Player_logic
      player_update();
  
      //fly logic
      fly_update();

      //Spring logic
      spring_update();
    }


    for (int i = 0; i < NUM_FLYS; ++i) {
      t3d_mat4fp_from_srt_euler(flyMatFP[i],
        (float[3]){0.025f, 0.025f, 0.025f},
        (float[3]){flyPitch[i], -flyYaw[i], 0},
        flyPos[i].v
      );
      t3d_mat4fp_from_srt_euler(sphereFlyMatFP[i],
        (float[3]){0.025f, 0.025f, 0.025f},
        (float[3]){0, 0, 0}, 
        flyBox[i].center.v
      );
    }

    // Update player matrix
    t3d_mat4fp_from_srt_euler(modelMatFP,
      (float[3]){0.125f, 0.125f, 0.125f},
      (float[3]){0.0f, -rotY, 0},
      playerPos.v
    );

    t3d_mat4fp_from_srt_euler(tongueMatFP,
      (float[3]){0.125f, 0.125f, 0.125f},
      (float[3]){0.0f, -rotY, 0},
      tongue.pos.v
    );

    t3d_mat4fp_from_srt_euler(shadowMatFP,
      (float[3]){0.125f, 0.125f, 0.125f},
      (float[3]){0.0f, 0.0f, 0.0f},
      shadowPos.v
    );

    t3d_mat4fp_from_srt_euler(sphereMatFP,
      (float[3]){0.125f, 0.125f, 0.125f},
      (float[3]){0.0f, 0.0f, 0.0f},
      playerBox.center.v
    );

    t3d_mat4fp_from_srt_euler(sphere2MatFP,
      (float[3]){0.025f, 0.025f, 0.025f},
      (float[3]){0.0f, 0.0f, 0.0f},
      tongue.hitbox.center.v
    );
  
    // We now blend the walk animation with the idle/attack one
    t3d_skeleton_blend(&skel, &skel, &skelBlend, animBlend);
    for (int i = 0; i < NUM_SPRINGS; ++i) {
      t3d_skeleton_blend(&springSkels[i], &springSkels[i], &springSkelBlends[i], animBlend);
    }
    for (int i = 0; i < NUM_FLYS; ++i) {
      t3d_skeleton_blend(&flySkels[i], &flySkels[i], &flySkelBlends[i], animBlend);
    }

    if(syncPoint)rspq_syncpoint_wait(syncPoint); // wait for the RSP to process the previous frame

    // Now recalc. the matrices, this will cause any model referencing them to use the new pose
    t3d_skeleton_update(&skel);
    for (int i = 0; i < NUM_SPRINGS; ++i) {
      t3d_skeleton_update(&springSkels[i]);
    }
    for (int i = 0; i < NUM_FLYS; ++i) {
      t3d_skeleton_update(&flySkels[i]);
    }
    

    // ======== Draw (3D) ======== //
    rdpq_attach(display_get(), &depthBuffer);
    t3d_frame_start();
    t3d_viewport_attach(&viewport);

    t3d_screen_clear_color(RGBA32(155, 242, 238, 0xFF));
    t3d_screen_clear_depth();

    t3d_light_set_ambient(colorAmbient);
    t3d_light_set_directional(0, colorDir, &lightDirVec);
    t3d_light_set_count(1);

    rspq_block_run(dplMap);
    rspq_block_run(dplShadow);
    rspq_block_run(dplFrog);

    for (int i = 0; i < NUM_FLYS; ++i) {
      if(flyActive[i] == true) {
        if(flyHide[i] == 0) {
          rspq_block_run(dplFly[i]);
        }
        if(col_debug){
          rspq_block_run(dplDebugSphereFly[i]);
        }
      }
    }
    if(tongue.isActive == true) {
      rspq_block_run(dplTongue);
    }

    // Run gfx calls
    for (int i = 0; i < NUM_LILYPADS; ++i) {
        rspq_block_run(dplLilypad[i]);
        if(col_debug){
          rspq_block_run(dplDebugBox[i]);
        }
    }
    for (int i = 0; i < NUM_SPRINGS; ++i) {
        rspq_block_run(dplSpring[i]);
        if(col_debug){
          rspq_block_run(dplDebugBox2[i]);
        }
    }
    if(col_debug){
      rspq_block_run(dplDebugSphere);
      rspq_block_run(dplDebugSphere2);
    }

    syncPoint = rspq_syncpoint_new();

    // ======== Draw (UI) ======== //
    draw_debug_ui();

    rdpq_detach_show();
  }

  t3d_skeleton_destroy(&skel);
  t3d_skeleton_destroy(&skelBlend);

  t3d_anim_destroy(&animIdle);
  t3d_anim_destroy(&animWalk);
  t3d_anim_destroy(&animJump);
  t3d_anim_destroy(&animAttack);
  t3d_anim_destroy(&animRetract);

  
  t3d_model_free(model);
  t3d_model_free(modelMap);
  t3d_model_free(modelLilyPad);
  t3d_model_free(modelShadow);
  t3d_model_free(modelTongue);
  t3d_model_free(modelDebugBox);
  t3d_model_free(modelDebugSphere);

  // Clean up
  free(modelMatFP);
  free(shadowMatFP);
  free(tongueMatFP);
  free(mapMatFP);
  free(sphereMatFP);
  free(sphere2MatFP);
  for (int i = 0; i < NUM_LILYPADS; ++i) {
    free(lilypadMatFP[i]);
    rspq_block_free(dplLilypad[i]);
    rspq_block_free(dplDebugBox[i]);
  }
  for (int i = 0; i < NUM_SPRINGS; ++i) {
    t3d_skeleton_destroy(&springSkels[i]);
    t3d_skeleton_destroy(&springSkelBlends[i]);
    t3d_anim_destroy(&animsSpring[i]);
    t3d_model_free(modelSprings[i]);
    free(springMatFP[i]);
    rspq_block_free(dplSpring[i]);
    rspq_block_free(dplDebugBox2[i]);
  }
  for (int i = 0; i < NUM_SPRINGS + NUM_LILYPADS; ++i) {
    free(boxMatFP[i]);
  }
  for (int i = 0; i < NUM_FLYS; ++i) {
    t3d_skeleton_destroy(&flySkels[i]);
    t3d_skeleton_destroy(&flySkelBlends[i]);
    t3d_anim_destroy(&animsFlying[i]);
    t3d_anim_destroy(&animsDeath[i]);
    t3d_model_free(modelFlys[i]);
    free(flyMatFP[i]);
    free(sphereFlyMatFP[i]);
    rspq_block_free(dplFly[i]);
    rspq_block_free(dplDebugSphereFly[i]);
  }

  rspq_block_free(dplDebugSphere);
  rspq_block_free(dplDebugSphere2);
  rspq_block_free(dplFrog);
  rspq_block_free(dplTongue);
  rspq_block_free(dplShadow);
  rspq_block_free(dplMap);


  t3d_destroy();
  return 0;
}

