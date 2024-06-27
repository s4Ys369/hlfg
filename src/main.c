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
  debug_models_init();
  actors_init();
  player_init();
  cam_init();
  sound_init();
  map_init();

  rspq_syncpoint_t syncPoint = 0;

  for(;;)
  {
    // ======== Update ======== //

    get_jump_time();
    input_update();


    if (!btnheld[0].start){
      if(NUM_PLAYERS < 3){
        sound_update_buffer();
      }
  
      // CAMERA_LOGIC
      cam_update();
  
      //Player_logic
      player_update();
  
      //actor logic
#if NUM_SPRINGS > 0
      spring_update();
#endif
#if NUM_FLYS > 0
      fly_update();
#endif

    }

#if NUM_FLYS > 0
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
#endif

    for (int i = 0; i < NUM_PLAYERS; ++i) {
    // Update players matrix
    t3d_mat4fp_from_srt_euler(modelMatFP[i],
      (float[3]){0.125f, 0.125f, 0.125f},
      (float[3]){0.0f, -player[i].rotY, 0},
      player[i].playerPos.v
    );

    t3d_mat4fp_from_srt_euler(tongueMatFP[i],
      (float[3]){0.125f, 0.125f, 0.125f},
      (float[3]){0.0f, -player[i].rotY, 0},
      player[i].tongue[i].pos.v
    );

    t3d_mat4fp_from_srt_euler(shadowMatFP[i],
      (float[3]){0.125f, 0.125f, 0.125f},
      (float[3]){0.0f, 0.0f, 0.0f},
      player[i].shadowPos.v
    );

    t3d_mat4fp_from_srt_euler(sphereMatFP[i],
      (float[3]){0.125f, 0.125f, 0.125f},
      (float[3]){0.0f, 0.0f, 0.0f},
      player[i].playerBox.center.v
    );

    t3d_mat4fp_from_srt_euler(sphere2MatFP[i],
      (float[3]){0.0025f*player[i].tongue[i].hitbox.radius, 0.0025f*player[i].tongue[i].hitbox.radius, 0.0025f*player[i].tongue[i].hitbox.radius},
      (float[3]){0.0f, 0.0f, 0.0f},
      player[i].tongue[i].hitbox.center.v
    );
  
    // We now blend the walk animation with the idle/attack one
    t3d_skeleton_blend(&skel[i], &skel[i], &skelBlend[i], player[i].animBlend);
    }

#if NUM_SPRINGS > 0
    for (int i = 0; i < NUM_SPRINGS; ++i) {
      t3d_mat4fp_from_srt_euler(springMatFP[i], 
      (float[3]){0.25f, 0.25f, 0.25f}, 
      (float[3]){0, 0, 0}, 
      springPos[i].v
      );
      t3d_skeleton_blend(&springSkels[i], &springSkels[i], &springSkelBlends[i], 1);
    }
#endif

#if NUM_FLYS > 0
    for (int i = 0; i < NUM_FLYS; ++i) {
      t3d_skeleton_blend(&flySkels[i], &flySkels[i], &flySkelBlends[i], 1);
    }
#endif

    if(syncPoint)rspq_syncpoint_wait(syncPoint); // wait for the RSP to process the previous frame

    // Now recalc. the matrices, this will cause any model referencing them to use the new pose
    for (int i = 0; i < NUM_PLAYERS; ++i) {
      t3d_skeleton_update(&skel[i]);
    }

#if NUM_SPRINGS > 0
    for (int i = 0; i < NUM_SPRINGS; ++i) {
      t3d_skeleton_update(&springSkels[i]);
    }
#endif

#if NUM_FLYS > 0
    for (int i = 0; i < NUM_FLYS; ++i) {
      t3d_skeleton_update(&flySkels[i]);
    }
#endif

    

    // ======== Draw (3D) ======== //
    rdpq_attach(display_get(), &depthBuffer);
    t3d_frame_start();

    color_t fogColor = (color_t){0xC2, 0xB7, 0x7A, 0xFF};
    rdpq_set_prim_color((color_t){0xC2, 0xB7, 0x7A, 0xFF});
    rdpq_mode_fog(RDPQ_FOG_STANDARD);
    rdpq_set_fog_color(fogColor);

    t3d_screen_clear_color(fogColor);
    t3d_screen_clear_depth();

    t3d_fog_set_range(80.0f, 100.0f);
    t3d_fog_set_enabled(true);
    
    t3d_light_set_ambient(colorAmbient);
    t3d_light_set_count(1);

    // Run gfx calls
    float fov = T3D_DEG_TO_RAD(75.0f);
    float fov2p = T3D_DEG_TO_RAD(50.0f);
    for (int i = 0; i < NUM_PLAYERS; ++i) {
      T3DViewport *vp = &viewport[i];
      T3DVec3 CP = camPos[i];
      T3DVec3 CT = camTarget[i];

      if (NUM_PLAYERS == 2){
        t3d_viewport_set_projection(vp, fov2p, 10.0f, 150.0f);
      }else if (NUM_PLAYERS == 3){
        t3d_viewport_set_projection(&viewport[0], fov2p, 10.0f, 150.0f);
        t3d_viewport_set_projection(&viewport[1], fov, 10.0f, 150.0f);
        t3d_viewport_set_projection(&viewport[2], fov, 10.0f, 150.0f);
      } else {
        t3d_viewport_set_projection(vp, fov, 10.0f, 150.0f);
      }
      t3d_viewport_look_at(vp, &CP, &CT, &(T3DVec3){{0,1,0}});
      t3d_viewport_attach(vp);
      t3d_light_set_directional(0, colorDir, &lightDirVec);

      for (int i = 0; i < NUM_PLAYERS; ++i) {
        rspq_block_run(dplFrog[i]);
      }

#if NUM_SPRINGS > 0
      for (int i = 0; i < NUM_SPRINGS; ++i) {
        rspq_block_run(dplSpring[i]);
          if(col_debug){
            rspq_block_run(dplDebugBox2[i]);
          }
      }
#endif

      t3d_matrix_push_pos(1);
      rspq_block_run(dplMap);
      t3d_matrix_pop(1);

#if NUM_FLYS > 0
      t3d_matrix_push_pos(1);
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
      t3d_matrix_pop(1);
#endif

      t3d_matrix_push_pos(1);
      for (int i = 0; i < NUM_PLAYERS; ++i) {
        rspq_block_run(dplShadow[i]);
        if(player[i].tongue[i].isActive == true) {
          rspq_block_run(dplTongue[i]);
        }
        if(col_debug){
          rspq_block_run(dplDebugSphere[i]);
          rspq_block_run(dplDebugSphere2[i]);
        }
      }
      t3d_matrix_pop(1);

#if NUM_HILLS > 0
      t3d_matrix_push_pos(1);
      for (int i = 0; i < NUM_HILLS; ++i) {
        rspq_block_run(dplHill[i]);
      }
      t3d_matrix_pop(1);
#endif

#if NUM_LILYPADS > 0
      t3d_matrix_push_pos(1);
      for (int i = 0; i < NUM_LILYPADS; ++i) {
        rspq_block_run(dplLilypad[i]);
          if(col_debug){
            rspq_block_run(dplDebugBox[i]);
          }
      }
      t3d_matrix_pop(1);
#endif
    }

    syncPoint = rspq_syncpoint_new();

    // ======== Draw (UI) ======== //

    int sizeX = display_get_width();
    int sizeY = display_get_height();
    rdpq_sync_pipe();
    rdpq_set_scissor(0, 0, sizeX, sizeY);
    rdpq_set_mode_standard();
    rdpq_set_mode_fill(RGBA32(0, 0, 0, 0xFF));

    // draw thick lines between the screens
    switch (NUM_PLAYERS){
      case 1:
        break;
      case 2:
        rdpq_fill_rectangle(0, sizeY/2-1, sizeX, sizeY/2+1);
        break;
      case 3:
        rdpq_fill_rectangle(0, sizeY/2-1, sizeX, sizeY/2+1);
        rdpq_fill_rectangle(sizeX/2-1, sizeY/2, sizeX/2+1, sizeY);
        break;
      case 4:
        rdpq_fill_rectangle(0, sizeY/2-1, sizeX, sizeY/2+1);
        rdpq_fill_rectangle(sizeX/2-1, 0, sizeX/2+1, sizeY);
        break;
    }
    draw_debug_ui();
    rdpq_detach_show();
  }


  // Clean up
  t3d_model_free(modelMap);
  free_uncached(mapMatFP);
  rspq_block_free(dplMap);
  
  t3d_model_free(modelDebugBox);
  t3d_model_free(modelDebugSphere);

  for (int i = 0; i < NUM_PLAYERS; ++i) {
    t3d_skeleton_destroy(&skel[i]);
    t3d_skeleton_destroy(&skelBlend[i]);

    t3d_anim_destroy(&animIdle[i]);
    t3d_anim_destroy(&animWalk[i]);
    t3d_anim_destroy(&animJump[i]);
    t3d_anim_destroy(&animAttack[i]);
    t3d_anim_destroy(&animRetract[i]);

    t3d_model_free(model[i]);
    t3d_model_free(modelShadow[i]);
    t3d_model_free(modelTongue[i]);
  
    free_uncached(modelMatFP[i]);
    free_uncached(shadowMatFP[i]);
    free_uncached(tongueMatFP[i]);
    free_uncached(sphereMatFP[i]);
    free_uncached(sphere2MatFP[i]);
  
    rspq_block_free(dplDebugSphere[i]);
    rspq_block_free(dplDebugSphere2[i]);
    rspq_block_free(dplFrog[i]);
    rspq_block_free(dplTongue[i]);
    rspq_block_free(dplShadow[i]);
  }

#if NUM_HILLS > 0
  for (int i = 0; i < NUM_HILLS; ++i) {
    t3d_model_free(modelHill);
    free_uncached(hillMatFP[i]);
    rspq_block_free(dplHill[i]);
  }
#endif

#if NUM_LILYPADS > 0
  for (int i = 0; i < NUM_LILYPADS; ++i) {
    t3d_model_free(modelLilyPad);
    free_uncached(lilypadMatFP[i]);
    free_uncached(boxLPMatFP[i]);
    rspq_block_free(dplLilypad[i]);
    rspq_block_free(dplDebugBox[i]);
  }
#endif

#if NUM_SPRINGS > 0
  for (int i = 0; i < NUM_SPRINGS; ++i) {
    t3d_skeleton_destroy(&springSkels[i]);
    t3d_skeleton_destroy(&springSkelBlends[i]);
    t3d_anim_destroy(&animsSpring[i]);
    t3d_model_free(modelSpring);
    free_uncached(springMatFP[i]);
    free_uncached(boxSMatFP[i]);
    rspq_block_free(dplSpring[i]);
    rspq_block_free(dplDebugBox2[i]);
  }
#endif

    
#if NUM_FLYS > 0
  for (int i = 0; i < NUM_FLYS; ++i) {
    t3d_skeleton_destroy(&flySkels[i]);
    t3d_skeleton_destroy(&flySkelBlends[i]);
    t3d_anim_destroy(&animsFlying[i]);
    t3d_anim_destroy(&animsDeath[i]);
    t3d_model_free(modelFly);
    free_uncached(flyMatFP[i]);
    free_uncached(sphereFlyMatFP[i]);
    rspq_block_free(dplFly[i]);
    rspq_block_free(dplDebugSphereFly[i]);
  }
#endif

  t3d_destroy();
  return 0;
}

