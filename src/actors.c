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


#if NUM_HILLS > 0
T3DMat4FP* hillMatFP[NUM_HILLS];
T3DVec3 hillPos[NUM_HILLS];
AABB hillBox[NUM_HILLS];
rspq_block_t *dplHill[NUM_HILLS];
T3DModel *modelHill;
#endif

#if NUM_LILYPADS > 0
T3DMat4FP* lilypadMatFP[NUM_LILYPADS];
T3DMat4FP* boxLPMatFP[NUM_LILYPADS];
T3DVec3 lilypadPos[NUM_LILYPADS];
AABB lilypadBox[NUM_LILYPADS];
rspq_block_t *dplLilypad[NUM_LILYPADS];
rspq_block_t *dplDebugBox[NUM_LILYPADS];
T3DModel *modelLilyPad;
#endif

#if NUM_SPRINGS > 0
T3DMat4FP* springMatFP[NUM_SPRINGS];
T3DMat4FP* boxSMatFP[NUM_SPRINGS];
T3DVec3 springPos[NUM_SPRINGS];
AABB springBox[NUM_SPRINGS];
rspq_block_t *dplSpring[NUM_SPRINGS];
rspq_block_t *dplDebugBox2[NUM_SPRINGS];
T3DModel  *modelSpring;
T3DSkeleton springSkels[NUM_SPRINGS];
T3DSkeleton springSkelBlends[NUM_SPRINGS];
T3DAnim animsSpring[NUM_SPRINGS];
bool springActive[NUM_SPRINGS];
float springForce;
#endif

#if NUM_FLYS > 0
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
T3DModel *modelFly;
T3DSkeleton flySkels[NUM_FLYS];
T3DSkeleton flySkelBlends[NUM_FLYS];
T3DAnim animsFlying[NUM_FLYS];
T3DAnim animsDeath[NUM_FLYS];
int flyHide[NUM_FLYS];
#endif

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

int cIndex = -1;

void check_actor_collisions(T3DVec3 *posA, T3DVec3 *posB, AABB *boxA, AABB *boxB, int targetCount){
  for (int i = 0; i < targetCount; ++i) {
    AABB *currActor;
    cIndex = find_closest_actor(*posA, posB, targetCount);
    if (cIndex != -1){
      currActor = &boxB[cIndex];
      if(check_box_collision(boxA[i], *currActor)){
        resolve_box_collision_xz(*currActor, &posA[i], 0.01f);
      }
    }
  }
}

void actors_init(void){
  shuffle_array(xValues, 10);
  shuffle_array(zValues, 10); 
#if NUM_HILLS > 0
  modelHill = t3d_model_load("rom:/hill.t3dm");
#endif
#if NUM_LILYPADS > 0
  modelLilyPad = t3d_model_load("rom:/lily_pad.t3dm");
#endif
#if NUM_SPRINGS > 0
  modelSpring = t3d_model_load("rom:/spring.t3dm");
#endif
#if NUM_FLYS > 0
  modelFly = t3d_model_load("rom:/fly.t3dm");
#endif
#if NUM_HILLS > 0
  hills_init();
#endif
#if NUM_LILYPADS > 0
  lilypads_init();
#endif
#if NUM_SPRINGS > 0
  springs_init();
#endif
#if NUM_FLYS > 0
  flys_init();
#endif
}

#if NUM_HILLS > 0
// Initialize hills
void hills_init(void){
  for (int i = 0; i < NUM_HILLS; ++i) {
    hillMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    float translation[3] = {random_float(-450.0f, 450.0f), random_float(0.0f, 25.0f), random_float(-450.0f, 450.0f)};
    t3d_mat4fp_from_srt_euler(hillMatFP[i], (float[3]){1.0f, 1.0f, 1.0f}, (float[3]){0, 0, 0}, translation);

    hillPos[i] = (T3DVec3){{translation[0],translation[1],translation[2]}};
    hillBox[i] = (AABB){{{hillPos[i].v[0] - 64.0f, -1.0f, hillPos[i].v[2] - 64.0f }},
                    {{hillPos[i].v[0] + 64.0f, hillPos[i].v[1] + 16.5f, hillPos[i].v[2] + 64.0f}}}; // Hill's AABB

    // Create gfx call to draw hill
    rspq_block_begin();
      t3d_matrix_set(hillMatFP[i], true);
      rdpq_set_prim_color(RGBA16(255, 255, 255, 255));
      t3d_model_draw(modelHill);
    dplHill[i] = rspq_block_end();

#if NUM_LILYPADS > 0
    check_actor_collisions(&hillPos[i], lilypadPos, &hillBox[i], lilypadBox, NUM_LILYPADS);
    hillBox[i] = (AABB){{{hillPos[i].v[0] - 64.0f, -1.0f, hillPos[i].v[2] - 64.0f }},
                    {{hillPos[i].v[0] + 64.0f, hillPos[i].v[1] + 16.5f, hillPos[i].v[2] + 64.0f}}};
#endif

#if NUM_SPRINGS > 0
    check_actor_collisions(&hillPos[i], springPos, &hillBox[i], springBox, NUM_SPRINGS);
    hillBox[i] = (AABB){{{hillPos[i].v[0] - 64.0f, -1.0f, hillPos[i].v[2] - 64.0f }},
                    {{hillPos[i].v[0] + 64.0f, hillPos[i].v[1] + 16.5f, hillPos[i].v[2] + 64.0f}}};
#endif
  }
}
#endif

#if NUM_LILYPADS > 0
// Initialize lily pads
void lilypads_init(void){
  for (int i = 0; i < NUM_LILYPADS; ++i) {
	  float x = xValues[i];
    float z = zValues[i];
    lilypadMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    boxLPMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));

    lilypadPos[i] = (T3DVec3){{x, 20.0f, z}};
    lilypadBox[i] = (AABB){{{x - 20.0f, -1.0f, z - 20.0f}}, {{x + 20.0f, 28.0f, z + 20.0f}}};

    // Create gfx call to draw lily pad
    rspq_block_begin();
      t3d_matrix_set(lilypadMatFP[i], true);
      rdpq_set_prim_color(RGBA16(255, 255, 255, 255));
      t3d_model_draw(modelLilyPad);
    dplLilypad[i] = rspq_block_end();

    // Check and resolve collisions for each actor, then reset hitbox
#if NUM_HILLS > 0
    check_actor_collisions(&lilypadPos[i], hillPos, &lilypadBox[i], hillBox, NUM_HILLS);
    lilypadBox[i] = (AABB){{{lilypadPos[i].v[0] - 20.0f, -1.0f, lilypadPos[i].v[2] - 20.0f}},
                    {{lilypadPos[i].v[0] + 20.0f, 28.0f, lilypadPos[i].v[2] + 20.0f}}};
#endif

#if NUM_SPRINGS > 0
    check_actor_collisions(&lilypadPos[i], springPos, &lilypadBox[i], springBox, NUM_SPRINGS);
    lilypadBox[i] = (AABB){{{lilypadPos[i].v[0] - 20.0f, -1.0f, lilypadPos[i].v[2] - 20.0f}},
                    {{lilypadPos[i].v[0] + 20.0f, 28.0f, lilypadPos[i].v[2] + 20.0f}}};
#endif

    t3d_mat4fp_from_srt_euler(lilypadMatFP[i], (float[3]){0.25f, 0.25f, 0.25f}, (float[3]){0, 0, 0}, lilypadPos[i].v);
    t3d_mat4fp_from_srt_euler(boxLPMatFP[i], (float[3]){0.25f, 0.25f, 0.25f}, (float[3]){0, 0, 0}, lilypadPos[i].v);
    rspq_block_begin();
      t3d_matrix_set(boxLPMatFP[i], true);
      rdpq_set_prim_color(RGBA32(255, 0, 0, 120));
      t3d_model_draw(modelDebugBox);
    dplDebugBox[i] = rspq_block_end();
  }
}
#endif

#if NUM_SPRINGS > 0
// Initialize springs
void springs_init(void){
  for (int i = 0; i < NUM_SPRINGS; ++i) {
	  float x = xValues[i+5];
    float y = 20.0f;
    float z = zValues[i+5];
    springMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    boxSMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    
    springSkels[i] = t3d_skeleton_create(modelSpring);
    springSkelBlends[i] = t3d_skeleton_clone(&springSkels[i], false);
    animsSpring[i] = t3d_anim_create(modelSpring, "spring");
    t3d_anim_set_speed(&animsSpring[i], 50.0f);
    t3d_anim_attach(&animsSpring[i], &springSkels[i]);

    springActive[i] = true;
    springForce = 120.0f;

    springPos[i] = (T3DVec3){{x, y, z}};
    springBox[i] = (AABB){{{x - 20.0f, -1.0f, z - 20.0f}}, {{x + 20.0f, 30.0f, z + 20.0f}}};

    // Create gfx call to draw spring
    rspq_block_begin();
      t3d_matrix_push(springMatFP[i]);
      rdpq_set_prim_color(RGBA16(255, 255, 255, 255));
      t3d_model_draw_skinned(modelSpring, &springSkels[i]);
      t3d_matrix_pop(1);
    dplSpring[i] = rspq_block_end();

    // Check and resolve collisions for each actor, then reset hitbox
#if NUM_HILLS > 0
    check_actor_collisions(&springPos[i], hillPos, &springBox[i], hillBox, NUM_HILLS);
    springBox[i] = (AABB){{{springPos[i].v[0] - 20.0f, -1.0f, springPos[i].v[2] - 20.0f}},
                    {{springPos[i].v[0] + 20.0f, 30.0f, springPos[i].v[2] + 20.0f}}};
#endif

#if NUM_LILYPADS > 0
    check_actor_collisions(&springPos[i], lilypadPos, &springBox[i], lilypadBox, NUM_LILYPADS);
    springBox[i] = (AABB){{{springPos[i].v[0] - 20.0f, -1.0f, springPos[i].v[2] - 20.0f}},
                    {{springPos[i].v[0] + 20.0f, 30.0f, springPos[i].v[2] + 20.0f}}};
#endif

    t3d_mat4fp_from_srt_euler(boxSMatFP[i], (float[3]){0.25f, 0.25f, 0.25f}, (float[3]){0, 0, 0}, springPos[i].v);
    rspq_block_begin();
      t3d_matrix_push(boxSMatFP[i]);
      rdpq_set_prim_color(RGBA32(255, 0, 0, 120));
      t3d_model_draw(modelDebugBox);
      t3d_matrix_pop(1);
    dplDebugBox2[i] = rspq_block_end();
  }
}

void spring_update(void){
  for (int i = 0; i < NUM_SPRINGS; ++i) {

    if(springActive[i]) {
      t3d_anim_set_playing(&animsSpring[i], true);
      t3d_anim_update(&animsSpring[i], deltaTime);
    }
  }
}
#endif

// Initialize flys
#if NUM_FLYS > 0
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

    flySkels[i] = t3d_skeleton_create(modelFly);
    flySkelBlends[i] = t3d_skeleton_clone(&flySkels[i], true);

    animsFlying[i] = t3d_anim_create(modelFly, "flying");
    t3d_anim_set_speed(&animsFlying[i], 10.0f);
    t3d_anim_attach(&animsFlying[i], &flySkels[i]);

    animsDeath[i] = t3d_anim_create(modelFly, "death");
    t3d_anim_set_looping(&animsDeath[i], false);
    t3d_anim_set_playing(&animsDeath[i], false);
    t3d_anim_attach(&animsDeath[i], &flySkels[i]);

    flyPos[i] = (T3DVec3){{random_float(-170.0f, 170.0f), random_float(5.0f, 50.0f), random_float(-170.0f, 170.0f)}};
    flyYaw[i] = 0.0f;
    flyPitch[i] = 0.0f;
    flyBox[i] = (Sphere){flyPos[i], 10.0f};
    flyActive[i] = true;
    flyHide[i] = 0;

    // Create gfx call to draw flys
    rspq_block_begin();
      t3d_matrix_set(flyMatFP[i], true);
      rdpq_set_prim_color(RGBA16(255, 255, 255, 255));
      t3d_model_draw_skinned(modelFly, &flySkels[i]);
    dplFly[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_set(sphereFlyMatFP[i], true);
      rdpq_set_prim_color(RGBA32(255, 0, 0, 120));
      t3d_model_draw(modelDebugSphere);
    dplDebugSphereFly[i] = rspq_block_end();
  }
}

int closestPlayer = -1;
int closestHill = -1;
int closestLP = -1;
int closestSpring = -1;
void fly_update(void){
  for (int i = 0; i < NUM_FLYS; ++i) {
    if(flyActive[i]){
      t3d_anim_update(&animsFlying[i], deltaTime);
      flyDir[i] = (T3DVec3){{random_float(-10.0f, 10.0f), random_float(-10.0f, 10.0f), random_float(-10.0f, 10.0f)}};
      flySpeed[i] = random_float(10.0f, 50.0f);
      flyPointV[i] = 1;

      // Normalize the direction vector
      T3DVec3 normalizedDir = flyDir[i];

      t3d_vec3_norm(&normalizedDir);

      // Calculate yaw (rotation around y-axis)
      float newYaw = atan2f(normalizedDir.v[0], normalizedDir.v[2]);
      flyYaw[i] = t3d_lerp_angle(flyYaw[i], newYaw, 0.5f);

      // Calculate pitch (rotation around x-axis)
      float newPitch = asinf((normalizedDir.v[1]));
      flyPitch[i] = t3d_lerp_angle(flyPitch[i], newPitch, 0.5f);

      flyPos[i].v[0] += flyDir[i].v[0] * flySpeed[i] * deltaTime;
      flyPos[i].v[1] += flyDir[i].v[1] * flySpeed[i] * deltaTime;
      flyPos[i].v[2] += flyDir[i].v[2] * flySpeed[i] * deltaTime;

      if(flyPos[i].v[0] < FloorBox.min.v[0])flyPos[i].v[0] = 0;
      if(flyPos[i].v[0] >  FloorBox.max.v[0])flyPos[i].v[0] =  0;
      if(flyPos[i].v[1] < 50)flyPos[i].v[1] = 50;
      if(flyPos[i].v[1] >  5)flyPos[i].v[1] =  5;
      if(flyPos[i].v[2] < FloorBox.min.v[2])flyPos[i].v[2] = 0;
      if(flyPos[i].v[2] >  FloorBox.max.v[2])flyPos[i].v[2] =  0;

      flyBox[i].center = flyPos[i];

      Sphere *currPlayerBox;
      closestPlayer = find_closest_actor(flyPos[i], &player->playerPos, NUM_PLAYERS);
#if NUM_HILLS > 0
      AABB *currHill;
      closestHill = find_closest_actor(flyPos[i], hillPos, NUM_HILLS);
#endif

#if NUM_LILYPADS > 0
      AABB *currLP;
      closestLP = find_closest_actor(flyPos[i], lilypadPos, NUM_LILYPADS);
#endif

#if NUM_SPRINGS > 0
      AABB *currSpring;
      closestSpring = find_closest_actor(flyPos[i], springPos, NUM_SPRINGS);
#endif

      if (closestPlayer != -1){
        currPlayerBox = &player[closestPlayer].playerBox;
        if (check_sphere_collision(flyBox[i], *currPlayerBox)) {
          resolve_sphere_collision(*currPlayerBox, &flyPos[i]);
        }
      }

#if NUM_HILLS > 0
      if (closestHill != -1){
        currHill = &hillBox[closestHill];
        if (check_sphere_box_collision(flyBox[i], *currHill)) {
          resolve_box_collision(*currHill, &flyPos[i], flyBox[i].radius);
        }
      }
#endif

#if NUM_LILYPADS > 0
      if (closestLP != -1){
        currLP = &lilypadBox[closestLP];
        if (check_sphere_box_collision(flyBox[i], *currLP)) {
          resolve_box_collision(*currLP, &flyPos[i], flyBox[i].radius);
        }
      }
#endif

#if NUM_SPRINGS > 0
      if (closestSpring != -1){
        currSpring = &springBox[closestSpring];
        if (check_sphere_box_collision(flyBox[i], *currSpring)) {
          resolve_box_collision(*currSpring, &flyPos[i], flyBox[i].radius);
        }
      }
#endif
    }

    float distanceFromPlayer = t3d_vec3_distance(&player->playerPos, &flyPos[i]);
    if(distanceFromPlayer > FLY_DRAW_DIST){
      flyHide[i] = 1;
    } else {
      flyHide[i] = 0;
    }
  }
}
#endif

