#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>
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
#include "player.h"
#include "sound.h"
#include "utils.h"


T3DMat4FP* modelMatFP[NUM_PLAYERS];
T3DMat4FP* shadowMatFP[NUM_PLAYERS];
T3DMat4FP* tongueMatFP[NUM_PLAYERS];
T3DMat4FP* sphereMatFP[NUM_PLAYERS];
T3DMat4FP* sphere2MatFP[NUM_PLAYERS];
T3DModel *model[NUM_PLAYERS];
T3DModel *modelP1;
T3DModel *modelP2;
T3DModel *modelP3;
T3DModel *modelP4;
T3DModel *modelTongue[NUM_PLAYERS];
T3DModel *modelShadow[NUM_PLAYERS];
T3DSkeleton skel[NUM_PLAYERS];
T3DSkeleton skelBlend[NUM_PLAYERS];
T3DAnim animIdle[NUM_PLAYERS];
T3DAnim animWalk[NUM_PLAYERS];
T3DAnim animJump[NUM_PLAYERS];
T3DAnim animAttack[NUM_PLAYERS];
T3DAnim animRetract[NUM_PLAYERS];
rspq_block_t *dplDebugSphere[NUM_PLAYERS];
rspq_block_t *dplDebugSphere2[NUM_PLAYERS];
rspq_block_t *dplFrog[NUM_PLAYERS];
rspq_block_t *dplTongue[NUM_PLAYERS];
rspq_block_t *dplShadow[NUM_PLAYERS];
PlayerParams player[NUM_PLAYERS];

void player_init(void){

  modelP1 = t3d_model_load("rom:/frog.t3dm");
  if(NUM_PLAYERS > 1){
    if(NUM_PLAYERS == 2){
      modelP2 = t3d_model_load("rom:/frog_p2.t3dm");
    }
    if(NUM_PLAYERS == 3){
      modelP2 = t3d_model_load("rom:/frog_p2.t3dm");
      modelP3 = t3d_model_load("rom:/frog_p3.t3dm");
    }
    if(NUM_PLAYERS == 4){
      modelP2 = t3d_model_load("rom:/frog_p2.t3dm");
      modelP3 = t3d_model_load("rom:/frog_p3.t3dm");
      modelP4 = t3d_model_load("rom:/frog_p4.t3dm");
    }
  }

  switch(NUM_PLAYERS){
    case 1:
      model[0] = modelP1;
      break;
    case 2:
      model[0] = modelP1;
      model[1] = modelP2;
      break;
    case 3:
      model[0] = modelP1;
      model[1] = modelP2;
      model[2] = modelP3;
      break;
    case 4:
      model[0] = modelP1;
      model[1] = modelP2;
      model[2] = modelP3;
      model[3] = modelP4;
      break;
  }

  for (int i = 0; i < NUM_PLAYERS; ++i) {
    modelMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    shadowMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    tongueMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));

    sphereMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    sphere2MatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    modelTongue[i] = t3d_model_load("rom:/tongue.t3dm");
    modelShadow[i] = t3d_model_load("rom:/shadow.t3dm");
    skel[i] = t3d_skeleton_create(model[i]);
    skelBlend[i] = t3d_skeleton_clone(&skel[i], false);
    animIdle[i] = t3d_anim_create(model[i], "idle");
    t3d_anim_set_speed(&animIdle[i], 2.0f);
    t3d_anim_attach(&animIdle[i], &skel[i]);

    animWalk[i] = t3d_anim_create(model[i], "fall");
    t3d_anim_set_speed(&animWalk[i], 2.0f);
    t3d_anim_attach(&animWalk[i], &skelBlend[i]);

    animJump[i] = t3d_anim_create(model[i], "jump");
    t3d_anim_set_speed(&animJump[i], 3.5f);
    t3d_anim_set_looping(&animJump[i], false);
    t3d_anim_set_playing(&animJump[i], false);
    t3d_anim_attach(&animJump[i], &skel[i]);

    animAttack[i] = t3d_anim_create(model[i], "attack");
    t3d_anim_set_speed(&animAttack[i], 3.5f);
    t3d_anim_set_looping(&animAttack[i], false);
    t3d_anim_set_playing(&animAttack[i], false);
    t3d_anim_attach(&animAttack[i], &skel[i]);

    animRetract[i] = t3d_anim_create(model[i], "leg_retract");
    t3d_anim_set_speed(&animRetract[i], 3.5f);
    t3d_anim_set_looping(&animRetract[i], false);
    t3d_anim_set_playing(&animRetract[i], false);
    t3d_anim_attach(&animRetract[i], &skel[i]);


    rspq_block_begin();
      t3d_matrix_set(sphereMatFP[i], true);
      rdpq_set_prim_color(RGBA32(255, 0, 0, 120));
      t3d_model_draw(modelDebugSphere);
    dplDebugSphere[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_set(sphere2MatFP[i], true);
      rdpq_set_prim_color(RGBA32(255, 0, 0, 120));
      t3d_model_draw(modelDebugSphere);
    dplDebugSphere2[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_push(modelMatFP[i]);
      rdpq_set_prim_color(RGBA32(255, 255, 255, 255));
      t3d_model_draw_skinned(model[i], &skel[i]);
      t3d_matrix_pop(1);
    dplFrog[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_set(tongueMatFP[i], true);
      rdpq_set_prim_color(RGBA32(255, 255, 255, 255));
      t3d_model_draw(modelTongue[i]);
    dplTongue[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_set(shadowMatFP[i], true);
      rdpq_set_prim_color(RGBA32(0, 0, 0, 120));
      t3d_model_draw(modelShadow[i]);
    dplShadow[i] = rspq_block_end();

    player[i].moveDir = (T3DVec3){{0,0,0}};
    player[i].playerPos = (T3DVec3){{0,0.15f,0}};
    player[i].shadowPos = (T3DVec3){{0,0.15f,0}};
    player[i].playerForward = (T3DVec3){{0,0,1}};
    player[i].playerBox = (Sphere){{{-0.3f, 0.0f, -0.3f}},0.3f}; // Player's Sphere
    player[i].tongue[i].pos = player[i].playerBox.center;
    player[i].tongue[i].dir = player[i].playerForward;
    player[i].tongue[i].hitbox = (Sphere){{{0.0f, 0.0f, 0.0f}},6.0f};
    player[i].tongue[i].speed = 0.0f;
    player[i].tongue[i].isActive = false;
    player[i].tongue[i].length = 10.0f;
    player[i].rotY = 0.0f;
    player[i].currSpeed = 0.0f;
    player[i].animBlend = 0.0f;
    player[i].isAttack = false;
    player[i].isJumpStart = false;
    player[i].isJumping = false;
    player[i].isGrounded = true;
    player[i].isFalling = false;
    player[i].isWalking = false;
    player[i].playerVelocityY = 0.0f;
    player[i].gravity = -80.0f;
    player[i].jumpForce = 100.0f;
    player[i].score = 0;
    player[i].tongueRetract = 0;
    for (int j; j < NUM_SPRINGS; ++j) {
      player[i].activateSpring[j] = false;
    }
    if(NUM_PLAYERS > 1){
      player[i].playerPos = (T3DVec3){{random_float(-170.0f, 170.0f),0.15f,random_float(-170.0f, 170.0f)}};
    }
  }
}

// Function to find the closest object
int closestIndex = -1;
int find_closest_actor(T3DVec3 origin, T3DVec3 actorPos[], int numActors) {
  float minDistance = FLT_MAX;
  for (int i = 0; i < numActors; i++) {
    float dist = t3d_vec3_distance(&origin, &actorPos[i]);
    if (dist < minDistance) {
      minDistance = dist;
      closestIndex = i;
    }
  }
  return closestIndex;
}

void check_hill_collisions(AABB *hillBox, int hillCount, int playerCount) {
  AABB *currentHill;
  closestIndex = find_closest_actor(player[playerCount].playerPos, hillPos, hillCount);

  if (closestIndex != -1){
    currentHill = &hillBox[closestIndex];
    if (check_sphere_box_collision(player[playerCount].playerBox, *currentHill)) {
        resolve_box_collision(*currentHill, &player[playerCount].playerPos);

      if (player[playerCount].playerPos.v[1] >= currentHill->max.v[1]) {
        if (player[playerCount].playerBox.center.v[0] <= currentHill->max.v[0] &&
            player[playerCount].playerBox.center.v[0] >= currentHill->min.v[0] &&
            player[playerCount].playerBox.center.v[2] <= currentHill->max.v[2] &&
            player[playerCount].playerBox.center.v[2] >= currentHill->min.v[2]) {

          player[playerCount].isGrounded = true;
          player[playerCount].isJumping = false;
          player[playerCount].isFalling = false;
        } else {
          player[playerCount].isGrounded = false;
          player[playerCount].isJumping = false;
          player[playerCount].isFalling = true;
        }
      }
    }
  }
}


void check_lilypad_collisions(AABB *lilypadBox, int lilypadCount, int playerCount) {
  AABB *currentLilypad;
  closestIndex = find_closest_actor(player[playerCount].playerPos, lilypadPos, lilypadCount);

  if (closestIndex != -1){
    currentLilypad = &lilypadBox[closestIndex];
    if (check_sphere_box_collision(player[playerCount].playerBox, *currentLilypad)) {
        resolve_box_collision(*currentLilypad, &player[playerCount].playerPos);

      if (player[playerCount].playerPos.v[1] >= currentLilypad->max.v[1]) {
        if (player[playerCount].playerBox.center.v[0] <= currentLilypad->max.v[0] &&
            player[playerCount].playerBox.center.v[0] >= currentLilypad->min.v[0] &&
            player[playerCount].playerBox.center.v[2] <= currentLilypad->max.v[2] &&
            player[playerCount].playerBox.center.v[2] >= currentLilypad->min.v[2]) {

          player[playerCount].isGrounded = true;
          player[playerCount].isJumping = false;
          player[playerCount].isFalling = false;
        } else {
          player[playerCount].isGrounded = false;
          player[playerCount].isJumping = false;
          player[playerCount].isFalling = true;
        }
      }
    }
  }
}

void check_bouncepad_collisions(AABB *bouncepadBox, int bouncepadCount, int playerCount) {
  bool playerBounced = false;
  AABB *currentBouncepad;
  closestIndex = find_closest_actor(player[playerCount].playerPos, springPos, bouncepadCount);

  if (closestIndex != -1){
    currentBouncepad = &bouncepadBox[closestIndex];
    
    if (check_sphere_box_collision(player[playerCount].playerBox, *currentBouncepad)) { 
      resolve_box_collision(*currentBouncepad, &player[playerCount].playerPos);
      if(player[playerCount].playerPos.v[1] >= currentBouncepad->max.v[1]){
        if (player[playerCount].playerBox.center.v[0] <= currentBouncepad->max.v[0] &&
            player[playerCount].playerBox.center.v[0] >= currentBouncepad->min.v[0] &&
            player[playerCount].playerBox.center.v[2] <= currentBouncepad->max.v[2] &&
            player[playerCount].playerBox.center.v[2] >= currentBouncepad->min.v[2]) {
          player[playerCount].isFalling = false;
          playerBounced = true;
          player[playerCount].activateSpring[closestIndex] = true;
          t3d_anim_set_playing(&animsSpring[closestIndex], true);
          wav64_play(&sfx_bounce, 0);
          wav64_play(&sfx_boing, 1);
          mixer_try_play();
        }   
      }
    }
  }

  if (playerBounced) {
    // Player bounce
    player[playerCount].isGrounded = true;
    player[playerCount].isJumping = true;
    player[playerCount].isFalling = false;
    springForce += player[playerCount].gravity * deltaTime;
    player[playerCount].playerPos.v[1] += springForce * deltaTime;
    player[playerCount].playerBox.center.v[0] += player[playerCount].playerPos.v[0] * deltaTime;
    player[playerCount].playerBox.center.v[1] += player[playerCount].playerPos.v[1] + 0.15f;
    player[playerCount].playerBox.center.v[2] += player[playerCount].playerPos.v[2] * deltaTime;
    player[playerCount].tongue[playerCount].pos.v[1] += player[playerCount].playerBox.center.v[1] * deltaTime;
    player[playerCount].playerPos.v[1] += player[playerCount].playerBox.center.v[1] * deltaTime;
  }
}

void player_update(void){

  for (int i = 0; i < NUM_PLAYERS; ++i) {

  // Transform input direction to camera's coordinate system
  T3DVec3 newDir = {{
    (float)joypad[i].stick_x * 0.05f * camResults[i].right.v[0] + -(float)joypad[i].stick_y * 0.05f * camResults[i].forward.v[0],
    0, // :.[
    (float)joypad[i].stick_x * 0.05f * camResults[i].right.v[2] + -(float)joypad[i].stick_y * 0.05f * camResults[i].forward.v[2]
  }};
  float speed = sqrtf(t3d_vec3_len2(&newDir));

  // Player Jump Input
  if((btn[i].a) && !animJump[i].isPlaying && !animAttack[i].isPlaying) {
    if (player[i].isGrounded)
    {
      wav64_play(&sfx_jump, 0);
      mixer_try_play();
      t3d_anim_set_playing(&animJump[i], true);
      t3d_anim_set_time(&animJump[i], 0.0f);
      player[i].isJumpStart = true;
    }
  }

  // Player Attack Input
  if((btn[i].b) && !animJump[i].isPlaying && !animAttack[i].isPlaying) {
    wav64_play(&sfx_jump, 0);
    mixer_try_play();
    t3d_anim_set_playing(&animAttack[i], true);
    t3d_anim_set_time(&animAttack[i], 0.0f);
    player[i].isAttack = true;
  }

  // Player movement
  if(speed > 0.1f && !player[i].isJumpStart && !player[i].isJumping && !player[i].isAttack) {
    newDir.v[0] /= speed;
    newDir.v[2] /= speed;
    player[i].moveDir = newDir;

    float newAngle = atan2f(player[i].moveDir.v[0], player[i].moveDir.v[2]);
    player[i].rotY = t3d_lerp_angle(player[i].rotY, newAngle, 0.5f);
    player[i].currSpeed = t3d_lerp(player[i].currSpeed, speed * 0.1f, 0.1f);
  } else if (player[i].isJumping && !player[i].isGrounded){
    float newAngle = atan2f((player[i].moveDir.v[0]), (player[i].moveDir.v[2]));
    player[i].rotY = t3d_lerp_angle(player[i].rotY, newAngle, 0.1f);
    player[i].currSpeed = t3d_lerp(player[i].currSpeed, speed * 0.6f, 0.6f);
  } else {
    player[i].currSpeed *= 0.8f;
  }

  // use blend based on speed for smooth transitions
  player[i].animBlend = player[i].currSpeed / 0.51f;
  if(player[i].animBlend > 1.0f)player[i].animBlend = 1.0f;
  if(player[i].animBlend >= 0.8f)player[i].animBlend = 1.0f;

  // move player...
  player[i].playerPos.v[0] += player[i].moveDir.v[0] * player[i].currSpeed;
  player[i].playerPos.v[2] += player[i].moveDir.v[2] * player[i].currSpeed;
  // ...and limit position inside the box
  if(player[i].playerPos.v[0] < FloorBox.min.v[0]) player[i].playerPos.v[0] = FloorBox.min.v[0];
  if(player[i].playerPos.v[0] >  FloorBox.max.v[0])player[i].playerPos.v[0] =  FloorBox.max.v[0];
  if(player[i].playerPos.v[2] < FloorBox.min.v[2]) player[i].playerPos.v[2] = FloorBox.min.v[2];
  if(player[i].playerPos.v[2] >  FloorBox.max.v[2])player[i].playerPos.v[2] =  FloorBox.max.v[2];

  // Update the animation and modify the skeleton, this will however NOT recalculate the matrices
  if (!player[i].isJumpStart && !player[i].isJumping && !player[i].isAttack){
    t3d_anim_update(&animIdle[i], deltaTime);
    t3d_anim_set_speed(&animWalk[i], player[i].animBlend + 0.15f);
    t3d_anim_update(&animWalk[i], deltaTime);
  }


  // Update player bounding box
  player[i].playerBox.center.v[0] = player[i].playerPos.v[0];
  player[i].playerBox.center.v[1] = player[i].playerPos.v[1] + 0.15f;
  player[i].playerBox.center.v[2] = player[i].playerPos.v[2];

  // Check for collision with lilypad then ground, order highest to lowest apparently
  check_hill_collisions(hillBox, NUM_HILLS, i);
  check_bouncepad_collisions(springBox, NUM_SPRINGS, i);
  check_lilypad_collisions(lilypadBox, NUM_LILYPADS, i);
  if (check_sphere_box_collision(player[i].playerBox, FloorBox)) {
    resolve_box_collision(FloorBox, &player[i].playerPos);
  }

  // check walking
  if (player[i].currSpeed > 0.1f) {
    if(player[i].isGrounded) {
      player[i].isWalking = true;
    } else {
      player[i].isWalking = false;
    }
  } else {
    player[i].isWalking = false;
  }

  // do fall
  if(player[i].isFalling) {
    if (player[i].playerPos.v[1] > groundLevel) {
      player[i].playerVelocityY += player[i].gravity * jumpTime;
      player[i].playerPos.v[1] += player[i].playerVelocityY * jumpTime;
      player[i].isGrounded = false;
    } else {
      player[i].playerPos.v[1] = groundLevel;
      player[i].isFalling = false;
      player[i].isGrounded = true;
      player[i].jumpForce = 100.0f;
    }
  }

  //do attack
  if(player[i].isAttack){
    t3d_anim_update(&animAttack[i], deltaTime);
    player[i].tongue[i].speed = 120.0f;
    player[i].tongue[i].isActive = true;
    player[i].tongue[i].pos.v[0] += player[i].tongue[i].dir.v[0] * player[i].tongue[i].speed * deltaTime;
    player[i].tongue[i].pos.v[1] += player[i].tongue[i].dir.v[1] * player[i].tongue[i].speed * deltaTime;
    player[i].tongue[i].pos.v[2] += player[i].tongue[i].dir.v[2] * player[i].tongue[i].speed * deltaTime;
    // Calculate the distance traveled by the tongue from its origin
    float distanceTraveled = t3d_vec3_distance(&player[i].tongue[i].pos, &player[i].playerBox.center);

    // Define the maximum distance the tongue can travel
    float EndPosMax = 18.0f;

    // Reverse direction if the maximum distance is reached
    if (distanceTraveled >= EndPosMax) {
      player[i].tongue[i].speed = 40.0f;
      player[i].tongue[i].dir.v[0] = -player[i].tongue[i].dir.v[0];
      player[i].tongue[i].dir.v[1] = -player[i].tongue[i].dir.v[1];
      player[i].tongue[i].dir.v[2] = -player[i].tongue[i].dir.v[2];
      player[i].tongueRetract = 1;
    }

    // Calculate the end position based on the tongue's direction and length
    T3DVec3 tongueEndPos;
    tongueEndPos.v[0] = player[i].tongue[i].pos.v[0] + player[i].tongue[i].dir.v[0] * player[i].tongue[i].length;
    tongueEndPos.v[1] = player[i].playerBox.center.v[1] + 1;
    tongueEndPos.v[2] = player[i].tongue[i].pos.v[2] + player[i].tongue[i].dir.v[2] * player[i].tongue[i].length;


    // Set the hitbox center to the end position
    if(player[i].tongueRetract == 0){
      if (distanceTraveled <= EndPosMax) {
        player[i].tongue[i].hitbox.center = tongueEndPos;
      }
    } else {
      player[i].tongue[i].hitbox.center = player[i].playerBox.center;
    }

    player[i].tongue[i].pos.v[1] = player[i].tongue[i].hitbox.center.v[1];

    Sphere *currentFlyBox;
    closestIndex = find_closest_actor(player[i].tongue[i].hitbox.center, flyPos, NUM_FLYS);
    if(closestIndex != -1) {
      currentFlyBox = &flyBox[closestIndex];
      if(check_sphere_collision(*currentFlyBox, player[i].tongue[i].hitbox)){
        t3d_anim_set_playing(&animsDeath[closestIndex], true);
        t3d_anim_update(&animsDeath[closestIndex], deltaTime);
        flySpeed[closestIndex] = 0;
        flyActive[closestIndex] = false;
        currentFlyBox->center.v[1] = -100.0f;
        player[i].tongue[i].hitbox.center = player[i].playerBox.center;
        animAttack[i].isPlaying = 0;
        player[i].score++;
      }
    }

    if(!animAttack[i].isPlaying){
      t3d_anim_set_time(&animAttack[i], 0.0f);
      player[i].isAttack = false;
      player[i].tongue[i].hitbox.center = player[i].playerBox.center;
      player[i].tongue[i].speed = 0.0f;
      player[i].tongue[i].isActive = false;
    }
  }

  //do jump
  if(player[i].isJumpStart) {
    t3d_anim_update(&animJump[i], deltaTime);
    t3d_anim_update(&animRetract[i], deltaTime);
    t3d_anim_set_time(&animRetract[i], 0.0f);
    if(player[i].isGrounded){
      if(!animJump[i].isPlaying){
        player[i].isJumpStart = false;
        player[i].isJumping = true;
      }
    }
  }

  if(player[i].isJumping){
    if (player[i].isGrounded) {
      // Initiate jump
      t3d_anim_set_playing(&animRetract[i], true);
      t3d_anim_set_time(&animRetract[i], 0.0f);
      player[i].playerVelocityY = player[i].jumpForce;
      player[i].isGrounded = false;
    }
    t3d_anim_update(&animRetract[i], deltaTime);
    if (!animRetract[i].isPlaying){
      player[i].isJumping = false;
      player[i].isFalling = true;
    }

    // Apply gravity
    player[i].playerVelocityY += player[i].gravity * jumpTime;

    // Update player position
    player[i].playerPos.v[1] += player[i].playerVelocityY * jumpTime;

    // Update player bounding box
    player[i].playerBox.center.v[0] = player[i].playerPos.v[0];
    player[i].playerBox.center.v[1] = player[i].playerPos.v[1] + 0.15f;
    player[i].playerBox.center.v[2] = player[i].playerPos.v[2];

    // Check for collision with lilypad then ground, order highest to lowest apparently
    check_hill_collisions(hillBox, NUM_HILLS, i);
    check_bouncepad_collisions(springBox, NUM_SPRINGS, i);
    check_lilypad_collisions(lilypadBox, NUM_LILYPADS, i);
    if (check_sphere_box_collision(player[i].playerBox, FloorBox)) {
      resolve_box_collision(FloorBox, &player[i].playerPos);
    }
  }

  // do grounded
  if(player[i].isGrounded) {
    if (player[i].playerPos.v[1] < groundLevel) {
        player[i].playerPos.v[1] = groundLevel;
      if (check_sphere_box_collision(player[i].playerBox, FloorBox)) {
        resolve_box_collision(FloorBox, &player[i].playerPos);
      }
    }
  }

  // update shadow
  player[i].shadowPos.v[0] = player[i].playerPos.v[0];
  player[i].shadowPos.v[1] = groundLevel;
  player[i].shadowPos.v[2] = player[i].playerPos.v[2];

  //reset tongue
  if(player[i].tongue[i].speed == 0.0f){
    update_player_forward(&player[i].playerForward, player[i].rotY);
    player[i].tongue[i].pos = player[i].playerBox.center;
    player[i].tongue[i].dir = player[i].playerForward;
    player[i].tongue[i].hitbox.center =  player[i].tongue[i].pos;
    player[i].tongueRetract = 0;
  }

  }

}