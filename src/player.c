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
#include "player.h"
#include "sound.h"
#include "utils.h"


T3DMat4FP* modelMatFP;
T3DMat4FP* shadowMatFP;
T3DMat4FP* tongueMatFP;
T3DMat4FP* sphereMatFP;
T3DMat4FP* sphere2MatFP;
T3DModel *model;
T3DModel *modelTongue;
T3DModel *modelShadow;
T3DSkeleton skel;
T3DSkeleton skelBlend;
T3DAnim animIdle;
T3DAnim animWalk;
T3DAnim animJump;
T3DAnim animAttack;
T3DAnim animRetract;
rspq_block_t *dplDebugSphere;
rspq_block_t *dplDebugSphere2;
rspq_block_t *dplFrog;
rspq_block_t *dplTongue;
rspq_block_t *dplShadow;

T3DVec3 moveDir;
T3DVec3 playerPos;
T3DVec3 shadowPos;
T3DVec3 playerForward;
Sphere playerBox;
TongueParams tongue;
float rotY;
float currSpeed;
float animBlend;
bool isAttack;
bool isJumpStart;
bool isJumping;
bool isGrounded;
bool isFalling;
bool isWalking;
float playerVelocityY;
float gravity;
float jumpForce;
int score;
int tongueRetract;
bool activateSpring[NUM_SPRINGS] = {false};

void player_init(void){
  modelMatFP = malloc_uncached(sizeof(T3DMat4FP));
  shadowMatFP = malloc_uncached(sizeof(T3DMat4FP));
  tongueMatFP = malloc_uncached(sizeof(T3DMat4FP));

  sphereMatFP = malloc_uncached(sizeof(T3DMat4FP));
  sphere2MatFP = malloc_uncached(sizeof(T3DMat4FP));
  model = t3d_model_load("rom:/frog.t3dm");
  modelTongue = t3d_model_load("rom:/tongue.t3dm");
  modelShadow = t3d_model_load("rom:/shadow.t3dm");
  skel = t3d_skeleton_create(model);
  skelBlend = t3d_skeleton_clone(&skel, false);
  animIdle = t3d_anim_create(model, "idle");
  t3d_anim_set_speed(&animIdle, 2.0f);
  t3d_anim_attach(&animIdle, &skel);

  animWalk = t3d_anim_create(model, "fall");
  t3d_anim_set_speed(&animWalk, 2.0f);
  t3d_anim_attach(&animWalk, &skelBlend);

  animJump = t3d_anim_create(model, "jump");
  t3d_anim_set_speed(&animJump, 3.5f);
  t3d_anim_set_looping(&animJump, false);
  t3d_anim_set_playing(&animJump, false);
  t3d_anim_attach(&animJump, &skel);

  animAttack = t3d_anim_create(model, "attack");
  t3d_anim_set_speed(&animAttack, 3.5f);
  t3d_anim_set_looping(&animAttack, false);
  t3d_anim_set_playing(&animAttack, false);
  t3d_anim_attach(&animAttack, &skel);

  animRetract = t3d_anim_create(model, "leg_retract");
  t3d_anim_set_speed(&animRetract, 3.5f);
  t3d_anim_set_looping(&animRetract, false);
  t3d_anim_set_playing(&animRetract, false);
  t3d_anim_attach(&animRetract, &skel);


  rspq_block_begin();
    t3d_matrix_push(sphereMatFP);
    rdpq_set_prim_color(RGBA32(255, 0, 0, 120));
    t3d_model_draw(modelDebugSphere);
    t3d_matrix_pop(1);
  dplDebugSphere = rspq_block_end();

  rspq_block_begin();
    t3d_matrix_push(sphere2MatFP);
    rdpq_set_prim_color(RGBA32(255, 0, 0, 120));
    t3d_model_draw(modelDebugSphere);
    t3d_matrix_pop(1);
  dplDebugSphere2 = rspq_block_end();

  rspq_block_begin();
    t3d_matrix_push(modelMatFP);
    rdpq_set_prim_color(RGBA32(255, 255, 255, 255));
    t3d_model_draw_skinned(model, &skel);
    t3d_matrix_pop(1);
  dplFrog = rspq_block_end();

  rspq_block_begin();
    t3d_matrix_push(tongueMatFP);
    rdpq_set_prim_color(RGBA32(255, 255, 255, 255));
    t3d_model_draw(modelTongue);
    t3d_matrix_pop(1);
  dplTongue = rspq_block_end();

  rspq_block_begin();
    t3d_matrix_push(shadowMatFP);
    rdpq_set_prim_color(RGBA32(0, 0, 0, 120));
    t3d_model_draw(modelShadow);
    t3d_matrix_pop(1);
  dplShadow = rspq_block_end();

  moveDir = (T3DVec3){{0,0,0}};
  playerPos = (T3DVec3){{0,0.15f,0}};
  shadowPos = (T3DVec3){{0,0.15f,0}};
  playerForward = (T3DVec3){{0,0,1}};
  playerBox = (Sphere){{{-0.3f, 0.0f, -0.3f}},0.3f}; // Player's Sphere
  tongue.pos = playerBox.center;
  tongue.dir = playerForward;
  tongue.hitbox = (Sphere){{{0.0f, 0.0f, 0.0f}},6.0f};
  tongue.speed = 0.0f;
  tongue.isActive = false;
  tongue.length = 10.0f;
  rotY = 0.0f;
  currSpeed = 0.0f;
  animBlend = 0.0f;
  isAttack = false;
  isJumpStart = false;
  isJumping = false;
  isGrounded = true;
  isFalling = false;
  isWalking = false;
  playerVelocityY = 0.0f;
  gravity = -80.0f;
  jumpForce = 100.0f;
  score = 0;
  tongueRetract = 0;
}

void check_lilypad_collisions(AABB *lilypadBox, int lilypadCount) {
  AABB *currentLilypad;

  for (int i = 0; i < lilypadCount; i++) {
    currentLilypad = &lilypadBox[i];
    if (check_sphere_box_collision(playerBox, *currentLilypad)) {
        resolve_box_collision(*currentLilypad, &playerPos);

      if (playerPos.v[1] >= currentLilypad->max.v[1]) {
        if (playerBox.center.v[0] <= currentLilypad->max.v[0] &&
            playerBox.center.v[0] >= currentLilypad->min.v[0] &&
            playerBox.center.v[2] <= currentLilypad->max.v[2] &&
            playerBox.center.v[2] >= currentLilypad->min.v[2]) {

          isGrounded = true;
          isJumping = false;
          isFalling = false;
          break; // Exit loop if grounded on a lilypad
        } else {
          isGrounded = false;
          isJumping = false;
          isFalling = true;
          break;
        }
      }
    }
  }
}

void check_bouncepad_collisions(AABB *bouncepadBox, int bouncepadCount) {
  bool playerBounced = false;
  AABB *currentBouncepad;
  
  for (int i = 0; i < bouncepadCount; i++) {
    currentBouncepad = &bouncepadBox[i];
    
    if (check_sphere_box_collision(playerBox, *currentBouncepad)) { 
      resolve_box_collision(*currentBouncepad, &playerPos);
      if(playerPos.v[1] >= currentBouncepad->max.v[1]){
        if (playerBox.center.v[0] <= currentBouncepad->max.v[0] &&
            playerBox.center.v[0] >= currentBouncepad->min.v[0] &&
            playerBox.center.v[2] <= currentBouncepad->max.v[2] &&
            playerBox.center.v[2] >= currentBouncepad->min.v[2]) {
          isFalling = false;
          playerBounced = true;
          activateSpring[i] = true;
          t3d_anim_set_playing(&animsSpring[i], true);
          wav64_play(&sfx_bounce, 0);
          wav64_play(&sfx_boing, 1);
          mixer_try_play();
          break;
        }   
      }
    }
  }

  if (playerBounced) {
    // Player bounce
    isGrounded = true;
    isJumping = true;
    isFalling = false;
    springForce += gravity * deltaTime;
    playerPos.v[1] += springForce * deltaTime;
    playerBox.center.v[0] += playerPos.v[0] * deltaTime;
    playerBox.center.v[1] += playerPos.v[1] + 0.15f;
    playerBox.center.v[2] += playerPos.v[2] * deltaTime;
    tongue.pos.v[1] += playerBox.center.v[1] * deltaTime;
    playerPos.v[1] += playerBox.center.v[1] * deltaTime;
  }
}

void player_update(void){
  deltaTime = get_delta_time();
  jumpTime = get_jump_time();

  // Transform input direction to camera's coordinate system
  T3DVec3 newDir = {{
    (float)joypad.stick_x * 0.05f * camResults.right.v[0] + -(float)joypad.stick_y * 0.05f * camResults.forward.v[0],
    0, // :.[
    (float)joypad.stick_x * 0.05f * camResults.right.v[2] + -(float)joypad.stick_y * 0.05f * camResults.forward.v[2]
  }};
  float speed = sqrtf(t3d_vec3_len2(&newDir));

  // Player Jump Input
  if((btn.a) && !animJump.isPlaying && !animAttack.isPlaying) {
    if (isGrounded)
    {
      wav64_play(&sfx_jump, 0);
      mixer_try_play();
      t3d_anim_set_playing(&animJump, true);
      t3d_anim_set_time(&animJump, 0.0f);
      isJumpStart = true;
    }
  }

  // Player Attack Input
  if((btn.b) && !animJump.isPlaying && !animAttack.isPlaying) {
    if (isGrounded)
    {
      wav64_play(&sfx_jump, 0);
      mixer_try_play();
      t3d_anim_set_playing(&animAttack, true);
      t3d_anim_set_time(&animAttack, 0.0f);
      isAttack = true;
    }
  }

  // Player movement
  if(speed > 0.1f && !isJumpStart && !isJumping && !isAttack) {
    newDir.v[0] /= speed;
    newDir.v[2] /= speed;
    moveDir = newDir;

    float newAngle = atan2f(moveDir.v[0], moveDir.v[2]);
    rotY = t3d_lerp_angle(rotY, newAngle, 0.5f);
    currSpeed = t3d_lerp(currSpeed, speed * 0.1f, 0.1f);
  } else if (isJumping && !isGrounded){
    float newAngle = atan2f((moveDir.v[0]), (moveDir.v[2]));
    rotY = t3d_lerp_angle(rotY, newAngle, 0.1f);
    currSpeed = t3d_lerp(currSpeed, speed * 0.6f, 0.6f);
  } else {
    currSpeed *= 0.8f;
  }

  // use blend based on speed for smooth transitions
  animBlend = currSpeed / 0.51f;
  if(animBlend > 1.0f)animBlend = 1.0f;
  if(animBlend >= 0.8f)animBlend = 1.0f;

  // move player...
  playerPos.v[0] += moveDir.v[0] * currSpeed;
  playerPos.v[2] += moveDir.v[2] * currSpeed;
  // ...and limit position inside the box
  if(playerPos.v[0] < MapBox.min.v[0])playerPos.v[0] = MapBox.min.v[0];
  if(playerPos.v[0] >  MapBox.max.v[0])playerPos.v[0] =  MapBox.max.v[0];
  if(playerPos.v[2] < MapBox.min.v[2])playerPos.v[2] = MapBox.min.v[2];
  if(playerPos.v[2] >  MapBox.max.v[2])playerPos.v[2] =  MapBox.max.v[2];

  // Update the animation and modify the skeleton, this will however NOT recalculate the matrices
  if (!isJumpStart && !isJumping && !isAttack){
    t3d_anim_update(&animIdle, deltaTime);
    t3d_anim_set_speed(&animWalk, animBlend + 0.15f);
    t3d_anim_update(&animWalk, deltaTime);
  }


  // Update player bounding box
  playerBox.center.v[0] = playerPos.v[0];
  playerBox.center.v[1] = playerPos.v[1] + 0.15f;
  playerBox.center.v[2] = playerPos.v[2];

  // Check for collision with lilypad then ground, order highest to lowest apparently
  for(int i = 0; i < NUM_SPRINGS; ++i){
    check_bouncepad_collisions(springBox, NUM_SPRINGS);
  }
  for(int i = 0; i < NUM_LILYPADS; ++i){
    check_lilypad_collisions(lilypadBox, NUM_LILYPADS);
  }
  if (check_sphere_box_collision(playerBox, MapBox)) {
    resolve_box_collision(MapBox, &playerPos);
  }

  // check walking
  if (currSpeed > 0.1f) {
    if(isGrounded) {
      isWalking = true;
    } else {
      isWalking = false;
    }
  } else {
    isWalking = false;
  }

  // do fall
  if(isFalling) {
    if (playerPos.v[1] > groundLevel) {
      playerVelocityY += gravity * jumpTime;
      playerPos.v[1] += playerVelocityY * jumpTime;
      isGrounded = false;
    } else {
      playerPos.v[1] = groundLevel;
      isFalling = false;
      isGrounded = true;
      jumpForce = 100.0f;
    }
  }

  //do attack
  if(isAttack){
    t3d_anim_update(&animAttack, deltaTime);
    tongue.speed = 120.0f;
    tongue.isActive = true;
    tongue.pos.v[0] += tongue.dir.v[0] * tongue.speed * deltaTime;
    tongue.pos.v[1] += tongue.dir.v[1] * tongue.speed * deltaTime;
    tongue.pos.v[2] += tongue.dir.v[2] * tongue.speed * deltaTime;

    // Calculate the distance traveled by the tongue from its origin
    float distanceTraveled = sqrtf(
      (tongue.pos.v[0] - playerBox.center.v[0]) * (tongue.pos.v[0] - playerBox.center.v[0]) +
      (tongue.pos.v[1] - playerBox.center.v[1]) * (tongue.pos.v[1] - playerBox.center.v[1]) +
      (tongue.pos.v[2] - playerBox.center.v[2]) * (tongue.pos.v[2] - playerBox.center.v[2])
    );

    // Define the maximum distance the tongue can travel
    float EndPosMax = 18.0f;

    // Reverse direction if the maximum distance is reached
    if (distanceTraveled >= EndPosMax) {
      tongue.speed = 100.0f;
      tongue.dir.v[0] = -tongue.dir.v[0] * tongue.speed * deltaTime;
      tongue.dir.v[2] = -tongue.dir.v[2] * tongue.speed * deltaTime;
      tongueRetract = 1;
    }

    // Calculate the end position based on the tongue's direction and length
    T3DVec3 tongueEndPos;
    tongueEndPos.v[0] = tongue.pos.v[0] + tongue.dir.v[0] * tongue.length;
    tongueEndPos.v[1] = tongue.pos.v[1] + 6.0f;
    tongueEndPos.v[2] = tongue.pos.v[2] + tongue.dir.v[2] * tongue.length;


    // Set the hitbox center to the end position
    if(tongueRetract == 0){
      if (distanceTraveled <= EndPosMax) {
        tongue.hitbox.center = tongueEndPos;
      }
    } else {
      tongue.hitbox.center = playerBox.center;
    }

    Sphere *currentFlyBox;
    for(int i = 0; i < NUM_FLYS; ++i){
      currentFlyBox = &flyBox[i];
      if(check_sphere_collision(*currentFlyBox, tongue.hitbox)){
        t3d_anim_set_playing(&animsDeath[i], true);
        t3d_anim_update(&animsDeath[i], deltaTime);
        flySpeed[i] = 0;
        flyActive[i] = false;
        currentFlyBox->center.v[1] = -100.0f;
        tongue.hitbox.center = playerBox.center;
        tongue.speed = 100.0f;
        tongue.dir.v[0] = -tongue.dir.v[0] * tongue.speed * deltaTime;
        tongue.dir.v[2] = -tongue.dir.v[2] * tongue.speed * deltaTime;
        animAttack.isPlaying = 0;
        score++;
        break;
      }
    }

    if(!animAttack.isPlaying){
      t3d_anim_set_time(&animAttack, 0.0f);
      isAttack = false;
      tongue.hitbox.center = playerBox.center;
      tongue.speed = 0.0f;
      tongue.isActive = false;
    }
  }

  //do jump
  if(isJumpStart) {
    t3d_anim_update(&animJump, deltaTime);
    t3d_anim_update(&animRetract, deltaTime);
    t3d_anim_set_time(&animRetract, 0.0f);
    if(isGrounded){
      if(!animJump.isPlaying){
        isJumpStart = false;
        isJumping = true;
      }
    }
  }

  if(isJumping){
    if (isGrounded) {
      // Initiate jump
      t3d_anim_set_playing(&animRetract, true);
      t3d_anim_set_time(&animRetract, 0.0f);
      playerVelocityY = jumpForce;
      isGrounded = false;
    }
    t3d_anim_update(&animRetract, deltaTime);
    if (!animRetract.isPlaying){
      isJumping = false;
      isFalling = true;
    }

    // Apply gravity
    playerVelocityY += gravity * jumpTime;

    // Update player position
    playerPos.v[1] += playerVelocityY * jumpTime;

    // Update player bounding box
    playerBox.center.v[0] = playerPos.v[0];
    playerBox.center.v[1] = playerPos.v[1] + 0.15f;
    playerBox.center.v[2] = playerPos.v[2];

    // Check for collision with lilypad then ground, order highest to lowest apparently
    for(int i = 0; i < NUM_SPRINGS; ++i){
      check_bouncepad_collisions(springBox, NUM_SPRINGS);
    }
    for(int i = 0; i < NUM_LILYPADS; ++i){
      check_lilypad_collisions(lilypadBox, NUM_LILYPADS);
    }
    if (check_sphere_box_collision(playerBox, MapBox)) {
      resolve_box_collision(MapBox, &playerPos);
    }
  }

  // do grounded
  if(isGrounded) {
    if (playerPos.v[1] < groundLevel) {
        playerPos.v[1] = groundLevel;
      if (check_sphere_box_collision(playerBox, MapBox)) {
        resolve_box_collision(MapBox, &playerPos);
      }
    }
  }

  // update shadow
  shadowPos.v[0] = playerPos.v[0];
  shadowPos.v[1] = groundLevel;
  shadowPos.v[2] = playerPos.v[2];

  //reset tongue
  if(tongue.speed == 0.0f){
    update_player_forward(&playerForward, rotY);
    tongue.pos = playerBox.center;
    tongue.dir = playerForward;
    tongue.hitbox.center =  tongue.pos;
    tongueRetract = 0;
  }

}