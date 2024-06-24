#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3danim.h>
#include <t3d/t3dmodel.h>
#include <t3d/t3dskeleton.h>
#include "../include/config.h"
#include "../include/types.h"
#include "actors.h"
#include "collision.h"
#include "debug.h"
#include "map.h"
#include "player.h"
#include "utils.h"

T3DMat4FP* lilypadMatFP[NUM_LILYPADS];
T3DMat4FP* boxMatFP[NUM_LILYPADS];
T3DVec3 lilypadPos[NUM_LILYPADS];
AABB lilypadBox[NUM_LILYPADS];
rspq_block_t *dplLilypad[NUM_LILYPADS];
rspq_block_t *dplDebugBox[NUM_LILYPADS];
T3DModel *modelLilyPad;

T3DMat4FP* springMatFP[NUM_SPRINGS];
T3DVec3 springPos[NUM_SPRINGS];
AABB springBox[NUM_SPRINGS];
rspq_block_t *dplSpring[NUM_SPRINGS];
rspq_block_t *dplDebugBox2[NUM_SPRINGS];
T3DModel* modelSprings[NUM_SPRINGS];
T3DSkeleton springSkels[NUM_SPRINGS];
T3DSkeleton springSkelBlends[NUM_SPRINGS];
T3DAnim animsSpring[NUM_SPRINGS];
bool springActive[NUM_SPRINGS];
float springForce;

T3DMat4FP* flyMatFP[NUM_FLYS];
T3DMat4FP* sphereFlyMatFP[NUM_FLYS];
T3DVec3 flyPos[NUM_FLYS];
T3DVec3 flyDir[NUM_FLYS];
float flyYaw[NUM_FLYS];
float flyPitch[NUM_FLYS];
Sphere flyBox[NUM_FLYS];
float flySpeed[NUM_FLYS];
bool flyActive[NUM_FLYS];
int flyPointV[NUM_FLYS];
FlyParams fly[NUM_FLYS];
rspq_block_t *dplFly[NUM_FLYS];
rspq_block_t *dplDebugSphereFly[NUM_FLYS];
T3DModel* modelFlys[NUM_FLYS];
T3DSkeleton flySkels[NUM_FLYS];
T3DSkeleton flySkelBlends[NUM_FLYS];
T3DAnim animsFlying[NUM_FLYS];
T3DAnim animsDeath[NUM_FLYS];
int flyHide[NUM_FLYS];

float xValues[] = {
  150.0f,
  120.0f,
  90.0f,
  60.0f,
  30.0f,
  -30.0f,
  -60.0f,
  -90.0f,
  -120.0f,
  -150.0f
};
float zValues[] = {
  -175.0f,
  -150.0f,
  -125.0f,
  -100.0f,
  -50.0f,
  50.0f,
  100.0f,
  125.0f,
  150.0f,
  175.0f
};


void actors_init(void){
  shuffle_array(xValues, 10);
  shuffle_array(zValues, 10); 
  modelLilyPad = t3d_model_load("rom:/lily_pad.t3dm");
  lilypads_init();
  springs_init();
  flys_init();
}

// Initialize lily pads
void lilypads_init(void){
  for (int i = 0; i < NUM_LILYPADS; ++i) {
	  float x = xValues[i];
    float z = zValues[i];
    lilypadMatFP[i] = malloc(sizeof(T3DMat4FP));
    boxMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    float translation[3] = {x, 20.0f, z}; // Example positions
    t3d_mat4fp_from_srt_euler(lilypadMatFP[i], (float[3]){0.25f, 0.25f, 0.25f}, (float[3]){0, 0, 0}, translation);
    t3d_mat4fp_from_srt_euler(boxMatFP[i], (float[3]){0.25f, 0.25f, 0.25f}, (float[3]){0, 0, 0}, translation);

    lilypadPos[i] = (T3DVec3){{x, 20.0f, z}};
    lilypadBox[i] = (AABB){{{x - 20.0f, -1.0f, z - 20.0f}}, {{x + 20.0f, 38.0f, z + 20.0f}}};

    // Create gfx call to draw lily pad
    rspq_block_begin();
      t3d_matrix_push(lilypadMatFP[i]);
      rdpq_set_prim_color(RGBA16(255, 255, 255, 255));
      t3d_model_draw(modelLilyPad);
      t3d_matrix_pop(1);
    dplLilypad[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_push(boxMatFP[i]);
      rdpq_set_prim_color(RGBA32(255, 0, 0, 120));
      t3d_model_draw(modelDebugBox);
      t3d_matrix_pop(1);
    dplDebugBox[i] = rspq_block_end();
  }
}

// Initialize springs
void springs_init(void){
  for (int i = 0; i < NUM_SPRINGS; ++i) {
	  float x = xValues[i+5];
    float y = 20.0f;
    float z = zValues[i+5];
    springMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    boxMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    float translation[3] = {x, y, z}; // Example positions
    t3d_mat4fp_from_srt_euler(boxMatFP[i], (float[3]){0.25f, 0.25f, 0.25f}, (float[3]){0, 0, 0}, translation);
    
    modelSprings[i] = t3d_model_load("rom:/spring.t3dm");
    springSkels[i] = t3d_skeleton_create(modelSprings[i]);
    springSkelBlends[i] = t3d_skeleton_clone(&springSkels[i], false);
    animsSpring[i] = t3d_anim_create(modelSprings[i], "spring");
    t3d_anim_set_looping(&animsSpring[i], false);
    t3d_anim_set_playing(&animsSpring[i], false);
    t3d_anim_set_time(&animsSpring[i], 0.0f);
    t3d_anim_set_speed(&animsSpring[i], 2.5f);
    t3d_anim_attach(&animsSpring[i], &springSkels[i]);

    springActive[i] = false;
    springForce = 120.0f;

    springPos[i] = (T3DVec3){{x, y, z}};
    springBox[i] = (AABB){{{x - 20.0f, -1.0f, z - 20.0f}}, {{x + 20.0f, 38.0f, z + 20.0f}}};

    // Create gfx call to draw spring
    rspq_block_begin();
      t3d_matrix_push(springMatFP[i]);
      rdpq_set_prim_color(RGBA16(255, 255, 255, 255));
      t3d_model_draw_skinned(modelSprings[i], &springSkels[i]);
      t3d_matrix_pop(1);
    dplSpring[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_push(boxMatFP[i]);
      rdpq_set_prim_color(RGBA32(255, 0, 0, 120));
      t3d_model_draw(modelDebugBox);
      t3d_matrix_pop(1);
    dplDebugBox2[i] = rspq_block_end();
  }
}

void spring_update(void){
  for (int i = 0; i < NUM_SPRINGS; ++i) {
    t3d_mat4fp_from_srt_euler(springMatFP[i], (float[3]){0.25f, 0.25f, 0.25f}, (float[3]){0, 0, 0}, springPos[i].v);
    if(player->activateSpring[i]){
      springActive[i] = true;
      player->activateSpring[i] = false;
    }

    if(springActive[i]) {
      t3d_anim_set_playing(&animsSpring[i], true);
      t3d_anim_update(&animsSpring[i], deltaTime);
    }

    if(!animsSpring[i].isPlaying) {
      t3d_anim_set_time(&animsSpring[i], 0.0f);
      springActive[i] = false;
    }

  }
}

// Initialize flys
void flys_init(void){
  for (int i = 0; i < NUM_FLYS; ++i) {
    fly->pos = flyPos[i];
    fly->yaw = flyYaw[i];
    fly->pitch= flyPitch[i];
    fly->hitbox = flyBox[i];
    fly->dir = flyDir[i];
    fly->speed = flySpeed[i];
    fly->isActive = flyActive[i];
    fly->pointValue = flyPointV[i];
    flyMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    sphereFlyMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    modelFlys[i] = t3d_model_load("rom:/fly.t3dm");

    flySkels[i] = t3d_skeleton_create(modelFlys[i]);
    flySkelBlends[i] = t3d_skeleton_clone(&flySkels[i], false);

    animsFlying[i] = t3d_anim_create(modelFlys[i], "flying");
    t3d_anim_set_speed(&animsFlying[i], 10.0f);
    t3d_anim_attach(&animsFlying[i], &flySkels[i]);

    animsDeath[i] = t3d_anim_create(modelFlys[i], "death");
    t3d_anim_set_looping(&animsDeath[i], false);
    t3d_anim_set_playing(&animsDeath[i], false);
    t3d_anim_attach(&animsDeath[i], &flySkels[i]);

    flyPos[i] = (T3DVec3){{random_float(-170.0f, 170.0f), 6.0f, random_float(-170.0f, 170.0f)}};
    flyYaw[i] = 0.0f;
    flyPitch[i] = 0.0f;
    flyBox[i] = (Sphere){flyPos[i], 3.0f};
    flyActive[i] = true;
    flyHide[i] = 0;

    // Create gfx call to draw flys
    rspq_block_begin();
      t3d_matrix_push(flyMatFP[i]);
      rdpq_set_prim_color(RGBA16(255, 255, 255, 255));
      t3d_model_draw_skinned(modelFlys[i], &flySkels[i]);
      t3d_matrix_pop(1);
    dplFly[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_push(sphereFlyMatFP[i]);
      rdpq_set_prim_color(RGBA32(255, 0, 0, 120));
      t3d_model_draw(modelDebugSphere);
      t3d_matrix_pop(1);
    dplDebugSphereFly[i] = rspq_block_end();
  }
}

void fly_update(void){
  for (int i = 0; i < NUM_FLYS; ++i) {
    if(flyActive[i]){
      t3d_anim_update(&animsFlying[i], deltaTime);
      flyDir[i] = (T3DVec3){{random_float(-100.0f, 100.0f), 0.0f, random_float(-100.0f, 100.0f)}};
      flySpeed[i] = random_float(-4.0f, 4.0f);
      flyPointV[i] = 1;

      // Normalize the direction vector
      float length = sqrtf(
        flyDir[i].v[0] * flyDir[i].v[0] +
        flyDir[i].v[1] * flyDir[i].v[1] +
        flyDir[i].v[2] * flyDir[i].v[2]
      );

      if (length == 0) {
        break; // Avoid division by zero
      }

      T3DVec3 normalizedDir = {{
        flyDir[i].v[0] / length,
        flyDir[i].v[1] / length,
        flyDir[i].v[2] / length
      }};

      t3d_vec3_norm(&normalizedDir);

      // Calculate yaw (rotation around y-axis)
      flyYaw[i] = atan2f(normalizedDir.v[0], normalizedDir.v[2]);
      t3d_lerp_angle((normalizedDir.v[0] * flyYaw[i]), (normalizedDir.v[2] * flyYaw[i]), deltaTime/0.1f);

      // Calculate pitch (rotation around x-axis)
      flyPitch[i] = asinf((normalizedDir.v[1] * deltaTime));

      flyPos[i].v[0] += flyDir[i].v[0] * flySpeed[i] * deltaTime;
      flyPos[i].v[2] += flyDir[i].v[2] * flySpeed[i] * deltaTime;

      if(flyPos[i].v[0] < MapBox.min.v[0])flyPos[i].v[0] = 0;
      if(flyPos[i].v[0] >  MapBox.max.v[0])flyPos[i].v[0] =  0;
      if(flyPos[i].v[1] < 5)flyPos[i].v[1] = 5;
      if(flyPos[i].v[1] >  5)flyPos[i].v[1] =  5;
      if(flyPos[i].v[2] < MapBox.min.v[2])flyPos[i].v[2] = 0;
      if(flyPos[i].v[2] >  MapBox.max.v[2])flyPos[i].v[2] =  0;

      flyBox[i].center.v[0] = flyPos[i].v[0];
      flyBox[i].center.v[1] = flyPos[i].v[1];
      flyBox[i].center.v[2] = flyPos[i].v[2];
    }

    float dx = player->playerPos.v[0] - flyPos[i].v[0];
    float dy = player->playerPos.v[1] - flyPos[i].v[1];
    float dz = player->playerPos.v[2] - flyPos[i].v[2];
    float distanceFromPlayer = sqrtf(dx * dx + dy * dy + dz * dz);
    if(distanceFromPlayer > FLY_DRAW_DIST){
      flyHide[i] = 1;
    } else {
      flyHide[i] = 0;
    }
  }
}