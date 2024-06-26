#ifndef PLAYER_H
#define PLAYER_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>
#include "../include/config.h"
#include "../include/types.h"
#include "actors.h"
#include "camera.h"
#include "collision.h"
#include "debug.h"
#include "input.h"
#include "map.h"
#include "sound.h"
#include "utils.h"

extern T3DMat4FP* modelMatFP[NUM_PLAYERS];
extern T3DMat4FP* shadowMatFP[NUM_PLAYERS];
extern T3DMat4FP* tongueMatFP[NUM_PLAYERS];
extern T3DMat4FP* sphereMatFP[NUM_PLAYERS];
extern T3DMat4FP* sphere2MatFP[NUM_PLAYERS];
extern T3DModel *model[NUM_PLAYERS];
extern T3DModel *modelP1;
extern T3DModel *modelP2;
extern T3DModel *modelP3;
extern T3DModel *modelP4;
extern T3DModel *modelTongue[NUM_PLAYERS];
extern T3DModel *modelShadow[NUM_PLAYERS];
extern T3DSkeleton skel[NUM_PLAYERS];
extern T3DSkeleton skelBlend[NUM_PLAYERS];
extern T3DAnim animIdle[NUM_PLAYERS];
extern T3DAnim animWalk[NUM_PLAYERS];
extern T3DAnim animJump[NUM_PLAYERS];
extern T3DAnim animAttack[NUM_PLAYERS];
extern T3DAnim animRetract[NUM_PLAYERS];
extern rspq_block_t *dplDebugSphere[NUM_PLAYERS];
extern rspq_block_t *dplDebugSphere2[NUM_PLAYERS];
extern rspq_block_t *dplFrog[NUM_PLAYERS];
extern rspq_block_t *dplTongue[NUM_PLAYERS];
extern rspq_block_t *dplShadow[NUM_PLAYERS];
extern PlayerParams player[NUM_PLAYERS];

void player_init(void);
int find_closest_actor(T3DVec3 origin, T3DVec3 actorPos[], int numActors);


void check_player_collisions(Sphere *a, Sphere *b, int numPlayers);


#if NUM_HILLS > 0
void check_hill_collisions(AABB *hillBox, int hillCount, int playerCount);
void check_midair_hill_collisions(AABB *hillBox, int hillCount, int playerCount);
#endif

#if NUM_LILYPADS > 0
void check_lilypad_collisions(AABB *lilypadBox, int lilypadCount, int playerCount);
void check_midair_lilypad_collisions(AABB *lilypadBox, int lilypadCount, int playerCount);
#endif

#if NUM_SPRINGS > 0
void check_bouncepad_collisions(AABB *bouncepadBox, int bouncepadCount, int playerCount);
#endif

void player_update(void);


#endif // PLAYER_H