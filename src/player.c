#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3danim.h>
#include <t3d/t3dskeleton.h>
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
#include "utils.h"


T3DMat4FP* playerMatFP[MAX_PLAYERS];
T3DMat4FP* shadowMatFP[MAX_PLAYERS];
T3DMat4FP* projectileMatFP[MAX_PLAYERS];
T3DMat4FP* playerhitboxMatFP[MAX_PLAYERS];
T3DMat4FP* projectilehitboxMatFP[MAX_PLAYERS];
T3DModel *modelPlayer;
T3DModel *modelProjectile;
T3DModel *modelShadow;
T3DSkeleton playerSkel[MAX_PLAYERS];
T3DSkeleton playerSkelBlend[MAX_PLAYERS];
T3DAnim animIdle[MAX_PLAYERS];
T3DAnim animWalk[MAX_PLAYERS];
T3DAnim animJump[MAX_PLAYERS];
T3DAnim animAttack[MAX_PLAYERS];
T3DAnim animFall[MAX_PLAYERS];
rspq_block_t *dplPlayerHitBox[MAX_PLAYERS];
rspq_block_t *dplProjectileHitBox[MAX_PLAYERS];
rspq_block_t *dplPlayer[MAX_PLAYERS];
rspq_block_t *dplProjectile[MAX_PLAYERS];
rspq_block_t *dplShadow[MAX_PLAYERS];
PlayerParams *player[MAX_PLAYERS];
int playerState[MAX_PLAYERS];


// Check for PvP interaction, delcared first because used in init function
void check_player_collisions(PlayerParams *players[], int numPlayers) {
  for (int i = 0; i < numPlayers; i++) {
    for (int j = i + 1; j < numPlayers; j++) {
      if (check_sphere_collision(player[i]->hitbox, player[j]->hitbox)) {
        resolve_sphere_collision(player[i]->hitbox, &player[j]->pos);
        resolve_sphere_collision(player[j]->hitbox, &player[i]->pos);
      }
    }
  } 
}


void player_init(void){

  // Load T3D Models
  modelPlayer = t3d_model_load("rom:/player.t3dm");
  modelProjectile = t3d_model_load("rom:/projectile.t3dm");
  modelShadow = t3d_model_load("rom:/shadow.t3dm");

  for (int i = 0; i < numPlayers; ++i) {

    // Allocate player matrices
    playerMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    shadowMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    projectileMatFP[i] = malloc(sizeof(T3DMat4FP));
    playerhitboxMatFP[i] = malloc(sizeof(T3DMat4FP));
    projectilehitboxMatFP[i] = malloc(sizeof(T3DMat4FP));

    
    // Create skeleton and anims for each player
    playerSkel[i] = t3d_skeleton_create(modelPlayer);
    playerSkelBlend[i] = t3d_skeleton_clone(&playerSkel[i], false);
    animIdle[i] = t3d_anim_create(modelPlayer, "idle");
    t3d_anim_set_speed(&animIdle[i], 2.0f);
    t3d_anim_attach(&animIdle[i], &playerSkel[i]);

    animWalk[i] = t3d_anim_create(modelPlayer, "walk");
    t3d_anim_set_speed(&animWalk[i], 2.0f);
    t3d_anim_attach(&animWalk[i], &playerSkelBlend[i]);

    animJump[i] = t3d_anim_create(modelPlayer, "jump");
    t3d_anim_set_speed(&animJump[i], 3.5f);
    t3d_anim_set_looping(&animJump[i], false);
    t3d_anim_set_playing(&animJump[i], false);
    t3d_anim_attach(&animJump[i], &playerSkel[i]);

    animAttack[i] = t3d_anim_create(modelPlayer, "attack");
    t3d_anim_set_speed(&animAttack[i], 3.5f);
    t3d_anim_set_looping(&animAttack[i], false);
    t3d_anim_set_playing(&animAttack[i], false);
    t3d_anim_attach(&animAttack[i], &playerSkel[i]);

    animFall[i] = t3d_anim_create(modelPlayer, "fall");
    t3d_anim_set_speed(&animFall[i], 3.5f);
    t3d_anim_set_playing(&animAttack[i], false);
    t3d_anim_attach(&animFall[i], &playerSkelBlend[i]);


    // Create player's RSPQ blocks
    rspq_block_begin();
      t3d_matrix_push(playerMatFP[i]);
      rdpq_set_prim_color(BLUE);
      t3d_model_draw_skinned(modelPlayer, &playerSkel[i]);
      t3d_matrix_pop(1);
    dplPlayer[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_set(playerhitboxMatFP[i], true);
      rdpq_set_prim_color(RED);
      t3d_model_draw(modelDebugSphere);
    dplPlayerHitBox[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_set(projectileMatFP[i], true);
      rdpq_set_prim_color(INDIGO);
      t3d_model_draw(modelProjectile);
    dplProjectile[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_set(projectileMatFP[i], true);
      rdpq_set_prim_color(ORANGE);
      t3d_model_draw(modelDebugSphere);
    dplProjectileHitBox[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_set(shadowMatFP[i], true);
      rdpq_set_prim_color(TRANSPARENT);
      t3d_model_draw(modelShadow);
    dplShadow[i] = rspq_block_end();

    // Init player params
    player[i] = malloc_uncached(sizeof(PlayerParams));
    player[i]->moveDir = (T3DVec3){{0,0,0}};
    player[i]->pos = (T3DVec3){{0,groundLevel,0}};
    player[i]->shadowPos = player[i]->pos;
    player[i]->forward = (T3DVec3){{0,0,1}};
    player[i]->hitbox = (Sphere){{{0.0f, 16.0f, 0.0f}}, 16.0f};

    player[i]->projectile.pos = player[i]->hitbox.center;
    player[i]->projectile.dir = player[i]->forward;
    player[i]->projectile.hitbox = (Sphere){player[i]->hitbox.center,8.0f};
    player[i]->projectile.speed = 0.0f;
    player[i]->projectile.isActive = false;
    player[i]->projectile.length = 16.0f;

    player[i]->yaw = 0.0f;

    player[i]->currSpeed = 0.0f;

    player[i]->animBlend = 0.0f;

    player[i]->isIdle = false;
    player[i]->isAttack = false;
    player[i]->isJumpStart = false;
    player[i]->isJumping = false;
    player[i]->isGrounded = false;
    player[i]->isFalling = false;
    player[i]->isWalking = false;

    player[i]->velY = 0.0f;
    player[i]->jumpForce = 100.0f;

    player[i]->score = 0;

  }

  // If more than 1 player, place the players randomly and check for collisions
  if(numPlayers > 1){
    for (int p = 0; p < numPlayers; ++p){
      player[p]->pos = (T3DVec3){{random_float(-50.0f, 50.0f),groundLevel,random_float(-50.0f, 50.0f)}};
      check_player_collisions(player, numPlayers);

      if (check_sphere_box_collision(player[p]->hitbox, FloorBox)) {
        resolve_box_collision(FloorBox, &player[p]->pos, 0.01f);
      }
    }
  }
}

// General actor interaction
void check_actor_collisions(Actor **actor, int actorCount, int playerCount) {

  // Set the closet actor to current actor 
  Actor *currActor;
  int closestActor = find_closest(player[playerCount]->pos, actor, actorCount);

  if (closestActor != -1){
    currActor = actor[closestActor];

    // Handles if actor has a AABB hitbox
    if(currActor->hitbox.shape.type == SHAPE_BOX){
      if (check_sphere_box_collision(player[playerCount]->hitbox, currActor->hitbox.shape.aabb)) {

        // Move model and hitbox separately to blend later
        resolve_box_collision_xz(currActor->hitbox.shape.aabb, &player[playerCount]->hitbox.center, player[playerCount]->hitbox.radius);
        resolve_box_collision_xz(currActor->hitbox.shape.aabb, &player[playerCount]->pos, 0.02f);

        // If the actor is movable ie. bouncy, player pushes actor
        if(currActor->IsBouncy == true){
          resolve_sphere_collision(player[playerCount]->hitbox, &currActor->pos);
        }
      }
    }

    // Handles if actor has a Sphere hitbox
    if(currActor->hitbox.shape.type == SHAPE_SPHERE){
      if (check_sphere_collision(player[playerCount]->hitbox, currActor->hitbox.shape.sphere)) {

        // Move model and hitbox separately to blend later
        resolve_sphere_collision(currActor->hitbox.shape.sphere, &player[playerCount]->hitbox.center);
        resolve_sphere_collision(currActor->hitbox.shape.sphere, &player[playerCount]->pos);

      }
    }

    // More to be added

  }
}

// General attack interaction
void check_attack_collisions(Actor **actor, int actorCount, int playerCount) {

  // Set the closet actor to current actor 
  Actor *currActor;
  int closestActor = find_closest(player[playerCount]->projectile.hitbox.center, actor , actorCount);

  if (closestActor != -1){
    currActor = actor[closestActor];

    // Handles if actor has a AABB hitbox
    if(currActor->hitbox.shape.type == SHAPE_BOX){
      if (check_sphere_box_collision(player[playerCount]->projectile.hitbox, currActor->hitbox.shape.aabb)) {

        // Move model and hitbox separately to blend later
        resolve_box_collision_xz(currActor->hitbox.shape.aabb, &player[playerCount]->projectile.hitbox.center, player[playerCount]->projectile.hitbox.radius);
        resolve_box_collision_xz(currActor->hitbox.shape.aabb, &player[playerCount]->projectile.pos, 0.02f);

        // If the actor is movable ie. bouncy, player pushes actor
        if(currActor->IsBouncy == true){
          resolve_sphere_collision(player[playerCount]->projectile.hitbox, &currActor->pos);
        }
      }
    }

    // Handles if actor has a Sphere hitbox
    if(currActor->hitbox.shape.type == SHAPE_SPHERE){
      if (check_sphere_collision(player[playerCount]->hitbox, currActor->hitbox.shape.sphere)) {

        // Move model and hitbox separately to blend later
        resolve_sphere_collision(currActor->hitbox.shape.sphere, &player[playerCount]->projectile.hitbox.center);
        resolve_sphere_collision(currActor->hitbox.shape.sphere, &player[playerCount]->projectile.pos);

        // If the actor is movable ie. bouncy, player pushes actor
        if(currActor->IsBouncy == true){
          resolve_sphere_collision(player[playerCount]->projectile.hitbox, &currActor->pos);
        }
      }
    }

    // More to be added

  }
}


// Example interaction: bounce player
void player_bounced(PlayerParams *player[], int playerCount) {
  float bounceMultiplier = 1.5f;

  playerState[playerCount] = PLAYER_JUMP_START;

  player[playerCount]->velY += (player[playerCount]->jumpForce * bounceMultiplier) + GRAVITY * deltaTime;

  player[playerCount]->pos.v[1] += player[playerCount]->velY * deltaTime;

  player[playerCount]->hitbox.center.v[1] = player[playerCount]->pos.v[1];

  player[playerCount]->projectile.pos.v[1] = player[playerCount]->hitbox.center.v[1];
}


// General airbourne actor interaction
void check_midair_actor_collisions(Actor **actor, int actorCount, int playerCount) {
 
  // Set the closet actor to current actor 
  Actor *currActor;
  int closestActor = find_closest(player[playerCount]->pos, actor , actorCount);

  if (closestActor != -1){
    currActor = actor[closestActor];

    // Handles if actor has a AABB hitbox
    if(currActor->hitbox.shape.type == SHAPE_BOX){
      if (check_sphere_box_collision(player[playerCount]->hitbox, currActor->hitbox.shape.aabb)) {

        // Move model and hitbox separately to blend later
        resolve_box_collision(currActor->hitbox.shape.aabb, &player[playerCount]->hitbox.center, player[playerCount]->hitbox.radius);
        resolve_box_collision(currActor->hitbox.shape.aabb, &player[playerCount]->pos, 0.02f);

        // Check if the player is above or within bounds in the x and z directions
        if (player[playerCount]->hitbox.center.v[0] <= currActor->hitbox.shape.aabb.max.v[0] &&
            player[playerCount]->hitbox.center.v[0] >= currActor->hitbox.shape.aabb.min.v[0] &&
            player[playerCount]->hitbox.center.v[2] <= currActor->hitbox.shape.aabb.max.v[2] &&
            player[playerCount]->hitbox.center.v[2] >= currActor->hitbox.shape.aabb.min.v[2]) {

          // Check if the player is above the top surface
          if (player[playerCount]->hitbox.center.v[1] >= currActor->hitbox.shape.aabb.max.v[1]) {

            // Check if not playing an override animations
            if(!animJump[playerCount].isPlaying && !animAttack[playerCount].isPlaying){

              // Check if the actor is marked as safe...
              if(currActor->isSafe == true){

                //... if so landed
                playerState[playerCount] = PLAYER_LAND;

              } else {

                //... if not do something  ie. bounce the player
                player_bounced(player, playerCount);

                // Always push the mixer ASAP or there is a delay in the sound
                sound_bounce();
              }
            }

          } else {
            // Fall if not at the right height
            playerState[playerCount] = PLAYER_FALL;
          }
        } else {
          // Just keep falling if not within bounds
          playerState[playerCount] = PLAYER_FALL;
        }
      }
    }

    // More to come
  }

}


void player_update(void){

  for (int i = 0; i < numPlayers; ++i) {


  // Transform input direction to camera's coordinate system
  T3DVec3 newDir = {{
    (float)joypad[i].stick_x * 0.05f * player[i]->cam.camResults.right.v[0] + -(float)joypad[i].stick_y * 0.05f * player[i]->cam.camResults.forward.v[0],
    0, // :.[
    (float)joypad[i].stick_x * 0.05f * player[i]->cam.camResults.right.v[2] + -(float)joypad[i].stick_y * 0.05f * player[i]->cam.camResults.forward.v[2]
  }};
  float speed = sqrtf(t3d_vec3_len2(&newDir));

  // Player Jump Input
  if((btn[i].a) && !animJump[i].isPlaying && !animAttack[i].isPlaying) {
    if (player[i]->isGrounded)
    {
      sound_jump();
      playerState[i] = PLAYER_JUMP_START;
    }
  }

  // Player Attack Input
  if((btn[i].b) && !animJump[i].isPlaying && !animAttack[i].isPlaying) {
      sound_jump();
      t3d_anim_set_playing(&animAttack[i], true);
      t3d_anim_set_time(&animAttack[i], 0.0f);
      playerState[i] = PLAYER_ATTACK;
  }

  // Player movement
  if(speed > 0.1f && !player[i]->isJumpStart && !player[i]->isJumping && !player[i]->isAttack) {
    newDir.v[0] /= speed;
    newDir.v[2] /= speed;
    player[i]->moveDir = newDir;

    float newAngle = atan2f(player[i]->moveDir.v[0], player[i]->moveDir.v[2]);
    player[i]->yaw = t3d_lerp_angle(player[i]->yaw, newAngle, 0.5f);
    player[i]->currSpeed = t3d_lerp(player[i]->currSpeed, speed * 0.2f, 0.2f);
  } else if (!player[i]->isGrounded) {
    float newAngle = atan2f((player[i]->moveDir.v[0]), (player[i]->moveDir.v[2]));
    player[i]->yaw = t3d_lerp_angle(player[i]->yaw, newAngle, 0.1f);
    player[i]->currSpeed = t3d_lerp(player[i]->currSpeed, speed * 0.6f, 0.6f);
  } else {
    player[i]->currSpeed *= 0.8f;
  }

  // use blend based on speed for smooth transitions
  player[i]->animBlend = player[i]->currSpeed / 0.51f;
  if(player[i]->animBlend > 1.0f)player[i]->animBlend = 1.0f;

  // move player...
  player[i]->pos.v[0] += player[i]->moveDir.v[0] * player[i]->currSpeed;
  player[i]->pos.v[2] += player[i]->moveDir.v[2] * player[i]->currSpeed;
  // ...and limit position inside the box
  if(player[i]->pos.v[0] < FloorBox.min.v[0]) player[i]->pos.v[0] = FloorBox.min.v[0];
  if(player[i]->pos.v[0] >  FloorBox.max.v[0])player[i]->pos.v[0] = FloorBox.max.v[0];
  if(player[i]->pos.v[2] < FloorBox.min.v[2]) player[i]->pos.v[2] = FloorBox.min.v[2];
  if(player[i]->pos.v[2] >  FloorBox.max.v[2])player[i]->pos.v[2] = FloorBox.max.v[2];

  // Update the animation and modify the skeleton, this will however NOT recalculate the matrices
  if (playerState[i] == PLAYER_IDLE || PLAYER_WALK){
    t3d_anim_update(&animIdle[i], deltaTime);
    t3d_anim_set_speed(&animWalk[i], player[i]->animBlend);
    t3d_anim_update(&animWalk[i], deltaTime);
  }


  // Update player bounding box
  player[i]->hitbox.center.v[0] = player[i]->pos.v[0];
  player[i]->hitbox.center.v[1] = player[i]->pos.v[1] + 16.0f;
  player[i]->hitbox.center.v[2] = player[i]->pos.v[2];

  // Check for collision with lilypad then ground, order highest to lowest apparently
  if(player[i]->pos.v[1] == groundLevel){
    if(numPlayers > 1){
      check_player_collisions(player, numPlayers);
    }
    check_actor_collisions(crates, numCrates, i);
    check_actor_collisions(balls, numBalls, i);
  }

  if(player[i]->pos.v[1] != groundLevel && player[i]->isGrounded){
    if(numPlayers > 1){
      check_player_collisions(player, numPlayers);
    }

    check_midair_actor_collisions(crates, numCrates, i);
    check_actor_collisions(balls, numBalls, i);

  }

  // check walking
  if (player[i]->currSpeed > 0.1f) {
    if(player[i]->isGrounded) {
      playerState[i] = PLAYER_WALK;
    }
  } else {
    if(player[i]->isGrounded) {
      playerState[i] = PLAYER_IDLE;
    }
  }

  // do fall
  if(player[i]->isFalling) {

    t3d_anim_set_speed(&animFall[i], player[i]->animBlend);
    t3d_anim_update(&animFall[i], deltaTime);

    if(numPlayers > 1){
      check_player_collisions(player, numPlayers);
    }

    check_midair_actor_collisions(crates, numCrates, i);
    check_actor_collisions(balls, numBalls, i);

    if (player[i]->pos.v[1] > groundLevel) {
      player[i]->velY += GRAVITY * deltaTime;
      player[i]->pos.v[1] += player[i]->velY * deltaTime;
    } else {
      player[i]->pos.v[1] = groundLevel;
      playerState[i] = PLAYER_LAND;
      t3d_anim_set_playing(&animFall[i], false);
      player[i]->jumpForce = 100.0f;
    }
  }

  //do attack
  int retract[MAX_PLAYERS];

  if(player[i]->isAttack){

    retract[i] = 0;
    t3d_anim_update(&animAttack[i], deltaTime);

    player[i]->projectile.speed = 120.0f;
    player[i]->projectile.isActive = true;
    player[i]->projectile.pos.v[0] += player[i]->projectile.dir.v[0] * player[i]->projectile.speed * deltaTime;
    player[i]->projectile.pos.v[1] += player[i]->projectile.dir.v[1] * player[i]->projectile.speed * deltaTime;
    player[i]->projectile.pos.v[2] += player[i]->projectile.dir.v[2] * player[i]->projectile.speed * deltaTime;

    // Calculate the distance traveled by the tongue from its origin
    float distanceTraveled = t3d_vec3_distance(&player[i]->projectile.pos, &player[i]->hitbox.center);

    // Define the maximum distance the tongue can travel
    float EndPosMax = 18.0f;

    // Reverse direction if the maximum distance is reached
    if (distanceTraveled >= EndPosMax) {
      player[i]->projectile.speed = 40.0f;
      player[i]->projectile.dir.v[0] = -player[i]->projectile.dir.v[0];
      player[i]->projectile.dir.v[1] = -player[i]->projectile.dir.v[1];
      player[i]->projectile.dir.v[2] = -player[i]->projectile.dir.v[2];
      retract[i] = 1;
    }

    /* Calculate the end position based on the projectiles's direction and length
    T3DVec3 EndPos;
    EndPos.v[0] = player[i]->projectile.pos.v[0] + player[i]->projectile.dir.v[0] * player[i]->projectile.length;
    EndPos.v[1] = player[i]->hitbox.center.v[1] + 1;
    EndPos.v[2] = player[i]->projectile.pos.v[2] + player[i]->projectile.dir.v[2] * player[i]->projectile.length;
    */


    // Scale hitbox up and down according to position
    if(retract[i] == 0){
      if (distanceTraveled <= EndPosMax) {
        player[i]->projectile.hitbox.center = player[i]->projectile.pos;
        player[i]->projectile.hitbox.radius += 5.0f; 
      }
    } else {
      player[i]->projectile.hitbox.center = player[i]->projectile.pos;
      player[i]->projectile.hitbox.radius -= 0.5f; 
    }

    player[i]->projectile.hitbox.center.v[1] = player[i]->projectile.pos.v[1] + 5;

    check_actor_collisions(crates, numCrates, i);
    check_actor_collisions(balls, numBalls, i);

    if(!animAttack[i].isPlaying){
      player[i]->projectile.hitbox.center = player[i]->hitbox.center;
      player[i]->projectile.speed = 0.0f;
      player[i]->projectile.isActive = false;
      playerState[i] = PLAYER_IDLE;
    }
  }

  //do jump
  if(player[i]->isJumpStart) {

    t3d_anim_set_time(&animJump[i], 0.0f);
    t3d_anim_set_playing(&animJump[i], true);

    if(numPlayers > 1){
      check_player_collisions(player, numPlayers);
    }

    check_actor_collisions(crates, numCrates, i);
    check_actor_collisions(balls, numBalls, i);

    playerState[i] = PLAYER_JUMP;
  }

  if(player[i]->isJumping){

    t3d_anim_update(&animJump[i], deltaTime);

    if (!animJump[i].isPlaying){
      playerState[i] = PLAYER_FALL;
      t3d_anim_set_playing(&animFall[i], true);
    }

    // Apply jump force modifier
    player[i]->velY = player[i]->jumpForce;

    // Apply gravity
    player[i]->velY += GRAVITY * jumpTime;

    // Update player position
    player[i]->pos.v[1] += player[i]->velY * jumpTime;

    // Update player bounding box
    player[i]->hitbox.center.v[0] = player[i]->pos.v[0];
    player[i]->hitbox.center.v[1] = player[i]->pos.v[1];
    player[i]->hitbox.center.v[2] = player[i]->pos.v[2];

    // Check for collision with players then actors then floor
    if(numPlayers > 1){
      check_player_collisions(player, numPlayers);
    }

    check_midair_actor_collisions(crates, numCrates, i);
    check_actor_collisions(balls, numBalls, i);

    if (check_sphere_box_collision(player[i]->hitbox, FloorBox)) {
      resolve_box_collision(FloorBox, &player[i]->pos, 0.01f);
      playerState[i] = PLAYER_LAND;
    }
  }

  // do grounded
  if(player[i]->isGrounded) {
    if (player[i]->pos.v[1] < groundLevel) {
        player[i]->pos.v[1] = groundLevel;
    }
  }

  // update shadow
  player[i]->shadowPos.v[0] = player[i]->pos.v[0];
  player[i]->shadowPos.v[1] = groundLevel;
  player[i]->shadowPos.v[2] = player[i]->pos.v[2];

  //reset projectile
  if(player[i]->projectile.speed == 0.0f){
    update_player_forward(&player[i]->forward, player[i]->yaw);
    player[i]->projectile.pos = player[i]->hitbox.center;
    player[i]->projectile.dir = player[i]->forward;
    player[i]->projectile.hitbox.center =  player[i]->projectile.pos;
    player[i]->projectile.hitbox.radius = 15.0f;
    retract[i] = 0;
  }

  switch(playerState[i]){
    case PLAYER_IDLE:
      player[i]->isIdle = true;
      player[i]->isGrounded = true;
      break;
    case PLAYER_WALK:
      player[i]->isIdle = true;
      player[i]->isGrounded = true;
      player[i]->isWalking = true;
      break;
    case PLAYER_JUMP_START:
      player[i]->isIdle = false;
      player[i]->isAttack = false;
      player[i]->isJumpStart = true;
      player[i]->isJumping = false;
      player[i]->isFalling = false;
      player[i]->isWalking = false;
      break;
    case PLAYER_JUMP:
      player[i]->isIdle = false;
      player[i]->isGrounded = false;
      player[i]->isAttack = false;
      player[i]->isJumpStart = false;
      player[i]->isJumping = true;
      player[i]->isFalling = false;
      player[i]->isWalking = false;
      break;
    case PLAYER_ATTACK:
      player[i]->isIdle = false;
      player[i]->isAttack = true;
      player[i]->isJumpStart = false;
      player[i]->isJumping = false;
      player[i]->isFalling = false;
      player[i]->isWalking = false;
      break;
    case PLAYER_FALL:
      player[i]->isIdle = true;
      player[i]->isGrounded = false;
      player[i]->isJumping = false;
      player[i]->isFalling = true;
      break;
    case PLAYER_LAND:
      player[i]->isFalling = false;
      player[i]->isGrounded = true;
      break;
    }

  }

}