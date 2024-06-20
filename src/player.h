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

extern T3DMat4FP* modelMatFP;
extern T3DMat4FP* shadowMatFP;
extern T3DMat4FP* tongueMatFP;
extern T3DMat4FP* sphereMatFP;
extern T3DMat4FP* sphere2MatFP;
extern T3DModel *model;
extern T3DModel *modelTongue;
extern T3DModel *modelShadow;
extern T3DSkeleton skel;
extern T3DSkeleton skelBlend;
extern T3DAnim animIdle;
extern T3DAnim animWalk;
extern T3DAnim animJump;
extern T3DAnim animAttack;
extern T3DAnim animRetract;
extern rspq_block_t *dplDebugSphere;
extern rspq_block_t *dplDebugSphere2;
extern rspq_block_t *dplFrog;
extern rspq_block_t *dplTongue;
extern rspq_block_t *dplShadow;

extern T3DVec3 moveDir;
extern T3DVec3 playerPos;
extern T3DVec3 shadowPos;
extern T3DVec3 playerForward;
extern Sphere playerBox;
extern TongueParams tongue;
extern float rotY;
extern float currSpeed;
extern float animBlend;
extern bool isAttack;
extern bool isJumpStart;
extern bool isJumping;
extern bool isGrounded;
extern bool isFalling;
extern bool isWalking;
extern float playerVelocityY;
extern float gravity;
extern float jumpForce;
extern int score;
extern int tongueRetract;

void player_init(void);
void check_lilypad_collisions(AABB *lilypadBox, int lilypadCount);
void check_bouncepad_collisions(AABB *bouncepadBox, int bouncepadCount);
void player_update(void);

#endif // PLAYER_H