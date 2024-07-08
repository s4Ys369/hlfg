#include <libdragon.h>
#include <t3d/t3d.h>
#include "../include/config.h"
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "actors.h"
#include "camera.h"
#include "collision.h"
#include "debug.h"
#include "input.h"
#include "map.h"
#include "player.h"
#include "sound.h"
#include "ui.h"
#include "utils.h"
#include "test_level.h"

// IBE : Itty Bitty Engine, a 3D Game Engine for Tiny3D

int main()
{
  debug_init_isviewer();
  debug_init_usblog();

  dfs_init(DFS_DEFAULT_LOCATION);

  display_init(RESOLUTION_320x240, DEPTH_32_BPP, 3, GAMMA_NONE, FILTERS_RESAMPLE);
  surface_t depthBuffer = surface_alloc(FMT_RGBA16, display_get_width(), display_get_height());

  rdpq_init();
  input_init();

  // Default stack size is 8, but lower or raiser the size produces undesired results
  //t3d_init((T3DInitParams){.matrixStackSize = 8});
  t3d_init((T3DInitParams){});

  debug_models_init();

  map_init();
  actors_init();
  player_init();
  cam_init();
  sound_init();
  ui_init();

  syncPoint = 0;

  rspq_syncpoint_t syncPoint1 = 10;
  rspq_syncpoint_t syncPoint2 = 20;
  rspq_syncpoint_t syncPoint3 = 30;

  for(;;)
  {
    // ======== Update ======== //

    get_jump_time();
    input_update();

    // Simple Pause State
    if (!isPaused){

      //Don't worry about sound when dealing multiplayer
      if(numPlayers < 2){
        sound_update_buffer();
      }


      actors_update();
      player_update();
      cam_update();
    }

    if(syncPoint == syncPoint1)rspq_syncpoint_wait(syncPoint);

    // Update actor matrices
    for (int c = 0; c < numCrates; ++c) {
      t3d_mat4fp_from_srt_euler(crateMatFP[c],
        (float[3]){2.0f, 2.0f, 2.0f},
        (float[3]){0, 0, 0},
        crates[c]->pos.v
      );
    }

    for (int b = 0; b < numBalls; ++b) {
      t3d_mat4fp_from_srt_euler(ballMatFP[b],
        (float[3]){1.0f, 1.0f, 1.0f},
        balls[b]->rot.v,
        balls[b]->pos.v
      );
    }

    if(syncPoint == syncPoint2)rspq_syncpoint_wait(syncPoint);

    // Update player's extra matrices separately
    for (int p = 0; p < numPlayers; ++p) {

      t3d_mat4fp_from_srt_euler(projectileMatFP[p],
        (float[3]){0.5f, 0.5f, 0.5f},
        (float[3]){player[p]->rot.v[0], -player[p]->rot.v[1], player[p]->rot.v[2]},
        player[p]->projectile.pos.v
      );

      t3d_mat4fp_from_srt_euler(shadowMatFP[p],
        (float[3]){0.25f, 0.25f, 0.25f},
        (float[3]){player[p]->shadowRot.v[0], 0.0f, player[p]->shadowRot.v[2]},
        player[p]->shadowPos.v
      );

      t3d_mat4fp_from_srt_euler(playerhitboxMatFP[p],
        player[p]->scale.v,
        (float[3]){0.0f, 0.0f, 0.0f},
        player[p]->hitbox.center.v
      );

      t3d_mat4fp_from_srt_euler(projectilehitboxMatFP[p],
        (float[3]){(0.0625f * player[p]->projectile.hitbox.radius),
                    (0.0625f * player[p]->projectile.hitbox.radius), 
                    (0.0625f * player[p]->projectile.hitbox.radius)},
        (float[3]){0.0f, 0.0f, 0.0f},
        player[p]->projectile.hitbox.center.v
      );

    }

    if(syncPoint == syncPoint3)rspq_syncpoint_wait(syncPoint);
    
    for (int np = 0; np < numPlayers; ++np) {
      // Update players matrices
      t3d_mat4fp_from_srt_euler(playerMatFP[np],
          player[np]->scale.v,
          (float[3]){player[np]->rot.v[0], -player[np]->rot.v[1], player[np]->rot.v[2]},
          player[np]->pos.v
        );
    }

    for (int i = 0; i < numPlayers; ++i) {
      // We now blend the walk animation with the idle/attack one
      t3d_skeleton_blend(&playerSkel[i], &playerSkel[i], &playerSkelBlend[i], player[i]->animBlend);
    }
      
    t3d_mat4fp_from_srt_euler(testLevelMatFP, (float[3]){1.0f, 1.0f, 1.0f}, (float[3]){0, 0, 0}, (float[3]){0, 0, 0});

    if(syncPoint)rspq_syncpoint_wait(syncPoint);

    // Now recalc. the matrices, this will cause any model referencing them to use the new pose
    for (int i = 0; i < numPlayers; ++i) {
      t3d_skeleton_update(&playerSkel[i]);
    }


    // ======== Draw (3D) ======== //
    rdpq_attach(display_get(), &depthBuffer);
    t3d_frame_start();

    color_t fogColor = WHITE;
    rdpq_set_prim_color(WHITE);
    //rdpq_mode_fog(RDPQ_FOG_STANDARD);
    //rdpq_set_fog_color(fogColor);

    t3d_screen_clear_color(fogColor);
    t3d_screen_clear_depth();

    //t3d_fog_set_range(20.0f, 150.0f);
    //t3d_fog_set_enabled(true);
    
    t3d_light_set_ambient(colorAmbient);
    t3d_light_set_count(1);

    // Draw viewports
    float fov = T3D_DEG_TO_RAD(75.0f);
    float fov2p = T3D_DEG_TO_RAD(50.0f);
    float fov4p = T3D_DEG_TO_RAD(85.0f);
    for (int i = 0; i < numPlayers; ++i) {
      T3DViewport *vp = &player[i]->cam.viewport;
      T3DVec3 CP = player[i]->cam.camPos;
      T3DVec3 CT = player[i]->cam.camTarget;

      // FOV looks off at different window sizes, so adjust
      if (numPlayers == 2){
        t3d_viewport_set_projection(vp, fov2p, 20.0f, 750.0f);
      }else if (numPlayers == 3){
        t3d_viewport_set_projection(&player[0]->cam.viewport, fov2p, 20.0f, 750.0f);
        t3d_viewport_set_projection(&player[1]->cam.viewport, fov4p, 20.0f, 500.0f);
        t3d_viewport_set_projection(&player[2]->cam.viewport, fov4p, 20.0f, 500.0f);
      } else if (numPlayers == 4){
        t3d_viewport_set_projection(vp, fov4p, 20.0f, 500.0f);
      } else {
        t3d_viewport_set_projection(vp, fov, 20.0f, 1000.0f);
      }

      t3d_viewport_look_at(vp, &CP, &CT, &(T3DVec3){{0,1,0}});
      t3d_viewport_attach(vp);
      t3d_light_set_directional(0, colorDir, &lightDirVec);
      
      // Run levels block
      for (int l = 0; l < numLevels; ++l) {
        //t3d_segment_set(SEGMENT_LEVELS, &testLevelMatFP);
        rspq_block_run(dplTestLevel);
      }
      
      // then actors
      for (int c = 0; c < numCrates; ++c) {
        rspq_block_run(dplCrate[c]);
      }

      for (int b = 0; b < numBalls; ++b) {
        rspq_block_run(dplBall[b]);
      }

      // then the player blocks
      for (int p = 0; p < numPlayers; ++p) {
        rspq_block_run(dplPlayer[p]);

        // Lose shadows after 2 players for performance
        if(numPlayers <= 2){
          rspq_block_run(dplShadow[p]);
        }
      }

      // then the player's extra blocks
      for (int d = 0; d < numPlayers; ++d) {
        if(player[d]->projectile.isActive == true) {
          rspq_block_run(dplProjectile[d]);
        }
        if(col_debug){
          rspq_block_run(dplMap);
          rspq_block_run(dplPlayerHitBox[d]);
          rspq_block_run(dplProjectileHitBox[d]);
          //rspq_block_run(dplMesh);
          //rspq_block_run(dplMesh2);
          //rspq_block_run(dplTri);
        }
      }

    }

    syncPoint = rspq_syncpoint_new();

    // ======== Draw (UI) ======== //

    int sizeX = display_get_width();
    int sizeY = display_get_height();
    rdpq_sync_pipe();
    rdpq_set_scissor(0, 0, sizeX, sizeY);
    rdpq_set_mode_standard();
    rdpq_set_mode_fill(BLACK);

    // draw thick lines between the screens
    switch (numPlayers){
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

    ui_update();
    
    rdpq_detach_show();
  }


  // Clean up
  t3d_model_free(modelMap);
  free_uncached(mapMatFP);
  rspq_block_free(dplMap);
  t3d_model_free(modelMesh);
  free_uncached(meshMatFP);
  rspq_block_free(dplMesh);
  
  t3d_model_free(modelDebugBox);
  t3d_model_free(modelDebugSphere);

  for (int i = 0; i < numPlayers; ++i) {
    t3d_skeleton_destroy(&playerSkel[i]);
    t3d_skeleton_destroy(&playerSkelBlend[i]);

    t3d_anim_destroy(&animIdle[i]);
    t3d_anim_destroy(&animWalk[i]);
    t3d_anim_destroy(&animJump[i]);
    t3d_anim_destroy(&animAttack[i]);
    t3d_anim_destroy(&animFall[i]);

    t3d_model_free(modelPlayer);
    t3d_model_free(modelShadow);
    t3d_model_free(modelProjectile);
  
    free_uncached(playerMatFP[i]);
    free_uncached(shadowMatFP[i]);
    free(player[i]);
    free_uncached(projectileMatFP[i]);
    free_uncached(playerhitboxMatFP[i]);
    free_uncached(projectilehitboxMatFP[i]);
  
    rspq_block_free(dplPlayerHitBox[i]);
    rspq_block_free(dplProjectileHitBox[i]);
    rspq_block_free(dplShadow[i]);
    rspq_block_free(dplProjectile[i]);
    rspq_block_free(dplPlayer[i]);
  }


  for (int i = 0; i < numCrates; ++i) {
    t3d_model_free(modelCrate);
    free_uncached(crateMatFP[i]);
    free(crates[i]);
    rspq_block_free(dplCrate[i]);
  }

  for (int i = 0; i < numBalls; ++i) {
    t3d_model_free(modelBall);
    free_uncached(ballMatFP[i]);
    free(balls[i]);
    rspq_block_free(dplBall[i]);
  }

  t3d_destroy();
  return 0;
}

