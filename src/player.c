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
float playerScaleY[MAX_PLAYERS];


// Check for PvP interaction, delcared first because used in init function
void check_player_collisions(PlayerParams *players[], int numPlayers) {
  for (int i = 0; i < numPlayers; i++) {
    for (int j = i + 1; j < numPlayers; j++) {
      if (check_sphere_collision(player[i]->projectile.hitbox, player[j]->hitbox)) {
        resolve_sphere_collision_offset(player[i]->projectile.hitbox, &player[j]->pos,0.2f);
        resolve_sphere_collision_offset(player[j]->hitbox, &player[i]->projectile.pos,.1f);
        player[j]->pos.v[0] += player[i]->forward.v[0] * 5;
        player[j]->pos.v[2] += player[i]->forward.v[2] * 5;
      }
      if (check_sphere_collision(player[i]->hitbox, player[j]->hitbox)) {
        resolve_sphere_collision_offset(player[i]->hitbox, &player[j]->pos,1.4f);
        resolve_sphere_collision_offset(player[j]->hitbox, &player[i]->pos,1.4f);
        // Adjust both players' positions based on their current speed and direction
        players[j]->pos.v[0] += players[i]->forward.v[0] * players[i]->currSpeed;
        players[j]->pos.v[2] += players[i]->forward.v[2] * players[i]->currSpeed;
        players[i]->pos.v[0] += players[j]->forward.v[0];
        players[i]->pos.v[2] += players[j]->forward.v[2];
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
    projectileMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    playerhitboxMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));
    projectilehitboxMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));

    
    // Create skeleton and anims for each player
    playerSkel[i] = t3d_skeleton_create(modelPlayer);
    playerSkelBlend[i] = t3d_skeleton_clone(&playerSkel[i], false);
    animIdle[i] = t3d_anim_create(modelPlayer, "idle");
    t3d_anim_attach(&animIdle[i], &playerSkel[i]);

    animWalk[i] = t3d_anim_create(modelPlayer, "walk");
    t3d_anim_attach(&animWalk[i], &playerSkelBlend[i]);

    animJump[i] = t3d_anim_create(modelPlayer, "jump");
    t3d_anim_set_speed(&animAttack[i], 2.5f);
    t3d_anim_set_looping(&animJump[i], false);
    t3d_anim_set_playing(&animJump[i], false);
    t3d_anim_attach(&animJump[i], &playerSkel[i]);

    animAttack[i] = t3d_anim_create(modelPlayer, "attack");
    t3d_anim_set_speed(&animAttack[i], 3.5f);
    t3d_anim_set_looping(&animAttack[i], false);
    t3d_anim_set_playing(&animAttack[i], false);
    t3d_anim_attach(&animAttack[i], &playerSkel[i]);

    animFall[i] = t3d_anim_create(modelPlayer, "fall");
    t3d_anim_attach(&animFall[i], &playerSkelBlend[i]);


    // Create player's RSPQ blocks
    rspq_block_begin();
      t3d_matrix_push_pos(1);
      matCount++;
      t3d_matrix_set(playerMatFP[i], true);
      rdpq_set_prim_color(GREEN);
      t3d_matrix_set(playerMatFP[i], true);
      t3d_model_draw_skinned(modelPlayer, &playerSkel[i]);
      t3d_matrix_pop(1);
    dplPlayer[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_push_pos(1);
      matCount++;
      t3d_matrix_set(playerhitboxMatFP[i], true);
      rdpq_set_prim_color(RED);
      t3d_matrix_set(playerhitboxMatFP[i], true);
      t3d_model_draw(modelDebugSphere);
      t3d_matrix_pop(1);
    dplPlayerHitBox[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_push_pos(1);
      matCount++;
      t3d_matrix_set(projectileMatFP[i], true);
      rdpq_set_prim_color(WHITE);
      t3d_matrix_set(projectileMatFP[i], true);
      t3d_model_draw(modelProjectile);
      t3d_matrix_pop(1);
    dplProjectile[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_push_pos(1);
      matCount++;
      t3d_matrix_set(projectilehitboxMatFP[i], true);
      rdpq_set_prim_color(ORANGE);
      t3d_matrix_set(projectilehitboxMatFP[i], true);
      t3d_model_draw(modelDebugSphere);
      t3d_matrix_pop(1);
    dplProjectileHitBox[i] = rspq_block_end();

    rspq_block_begin();
      t3d_matrix_push_pos(1);
      matCount++;
      t3d_matrix_set(shadowMatFP[i], true);
      rdpq_set_prim_color(TRANSPARENT);
      t3d_matrix_set(shadowMatFP[i], true);
      t3d_model_draw(modelShadow);
      t3d_matrix_pop(1);
    dplShadow[i] = rspq_block_end();

    // Init player params
    player[i] = malloc(sizeof(PlayerParams));
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

    player[i]->vel.v[0] = 0.0f;
    player[i]->vel.v[1] = 0.0f;
    player[i]->vel.v[2] = 0.0f;
    if(numPlayers > 2){
      player[i]->jumpForce = 14.0f * JUMP_MODIFIER;
    } else {
      player[i]->jumpForce = 10.0f * JUMP_MODIFIER;
    }

    player[i]->score = 0;
    playerScaleY[i] = 1.0f;

  }

  // If more than 1 player, place the players randomly and check for collisions
  if(numPlayers > 1){
    for (int p = 0; p < numPlayers; ++p){
      player[p]->pos = (T3DVec3){{random_float(-320.0f, 320.0f),groundLevel,random_float(-320.0f, 320.0f)}};
      player[p]->hitbox.center = player[p]->pos;
      check_player_collisions(player, numPlayers);

      if (check_sphere_box_collision(player[p]->hitbox, FloorBox)) {
        resolve_box_collision_offset(FloorBox, &player[p]->pos, 0.01f);
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

        // If the actor is movable ie. bouncy, player pushes actor
        if(currActor->IsBouncy == true){
          resolve_sphere_collision_offset(player[playerCount]->hitbox, &currActor->pos, 2.0f);
          currActor->pos.v[0] += player[playerCount]->forward.v[0] * player[playerCount]->currSpeed;
          currActor->pos.v[2] += player[playerCount]->forward.v[2] * player[playerCount]->currSpeed;
        }

        // Move model and hitbox separately to blend later
        resolve_box_collision_offset_xz(currActor->hitbox.shape.aabb, &player[playerCount]->hitbox.center, player[playerCount]->hitbox.radius);
        resolve_box_collision_offset_xz(currActor->hitbox.shape.aabb, &player[playerCount]->pos, 0.02f);
      }
    }

    // Handles if actor has a Sphere hitbox
    if(currActor->hitbox.shape.type == SHAPE_SPHERE){
      if (check_sphere_collision(player[playerCount]->hitbox, currActor->hitbox.shape.sphere)) {

        // If the actor is movable ie. bouncy, player pushes actor
        if(currActor->IsBouncy == true){
          resolve_sphere_collision_offset(player[playerCount]->hitbox, &currActor->hitbox.shape.sphere.center, 1.4f);
        }

        // Actor pushes player
        resolve_sphere_collision_xz(currActor->hitbox.shape.sphere, &player[playerCount]->pos);


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

        // If the actor is movable ie. bouncy, player pushes actor
        if(currActor->IsBouncy == true){
          resolve_sphere_collision_offset_xz(player[playerCount]->projectile.hitbox, &currActor->pos, 2.0f);
          currActor->pos.v[0] += player[playerCount]->forward.v[0] * 2;
          currActor->pos.v[2] += player[playerCount]->forward.v[2] * 2;
        }

        resolve_box_collision_offset_xz(currActor->hitbox.shape.aabb, &player[playerCount]->projectile.pos, 0.02f);

        player[playerCount]->score++;

      }
    }

    // Handles if actor has a Sphere hitbox
    if(currActor->hitbox.shape.type == SHAPE_SPHERE){
      if (check_sphere_collision(player[playerCount]->hitbox, currActor->hitbox.shape.sphere)) {

        // If the actor is movable ie. bouncy, projectile pushes actor
        if(currActor->IsBouncy == true){
          resolve_sphere_collision_offset(player[playerCount]->projectile.hitbox, &currActor->hitbox.shape.sphere.center, 2.0f);
        }

        // Actor pushes projectile
        resolve_sphere_collision(currActor->hitbox.shape.sphere, &player[playerCount]->projectile.pos);

        player[playerCount]->score++;

      }
    }

    // More to be added

  }
}


// Example interaction: bounce player, not working in multiplayer??
void player_bounced(PlayerParams *player[], int playerCount) {
  float bounceMultiplier = 1.5f;

  playerState[playerCount] = PLAYER_JUMP_START;

  player[playerCount]->vel.v[1] += (player[playerCount]->jumpForce * bounceMultiplier) + GRAVITY * deltaTime;

  player[playerCount]->pos.v[1] += player[playerCount]->vel.v[1] * deltaTime;

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
        resolve_box_collision_offset(currActor->hitbox.shape.aabb, &player[playerCount]->hitbox.center, player[playerCount]->hitbox.radius);
        resolve_box_collision_offset(currActor->hitbox.shape.aabb, &player[playerCount]->pos, 0.01f);

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
            } else {
              // Resolve collision if not at the right height
              resolve_box_collision_offset(currActor->hitbox.shape.aabb, &player[playerCount]->pos, 0.1f);
            }

          } else {
            // Resolve collision if not at the right height
            resolve_box_collision_offset(currActor->hitbox.shape.aabb, &player[playerCount]->pos, 0.1f);
          }
        } else {
          // Resolve collision if not within bounds
          resolve_box_collision_offset(currActor->hitbox.shape.aabb, &player[playerCount]->pos, 0.1f);
        }
      }
    }

    // More to come
  }

}


void player_to_mesh(int playerCount){
// mesh collisions?
  T3DQuad currQuad = get_closest_quad(player[playerCount]->pos, modelMesh, 1);
  T3DVec3 currQuadNorm = get_quad_normal(currQuad);
  T3DVec3 currQuadCenter = compute_quad_center(currQuad);
  if (check_sphere_quad_collision(player[playerCount]->hitbox, currQuad)){
    //player[i]->vel = reflect_velocity(player[i]->vel, currQuadNorm);
    resolve_slope_collision(player[playerCount]->hitbox.center, player[playerCount]->vel, currQuad);
    float planeD = calculate_plane_d(currQuadNorm, currQuadCenter);
    resolve_sphere_quad_collision(&player[playerCount]->hitbox.center, player[playerCount]->hitbox.radius, currQuadNorm, planeD);
  }
}

void player_to_wall(int playerCount){
// wall collisions?
  Surface currWall = find_closest_surface(player[playerCount]->hitbox.center, Wall, wallCount);
  if (check_sphere_surface_collision(player[playerCount]->hitbox, currWall)){
    resolve_sphere_surface_collision(&player[playerCount]->hitbox, &currWall);
  }
}

void player_to_slope(int playerCount){
// slope collisions?
  Surface currSlope = find_closest_surface(player[playerCount]->hitbox.center, Slope, slopeCount);
  if (check_sphere_surface_collision(player[playerCount]->hitbox, currSlope)){
    resolve_sphere_surface_collision(&player[playerCount]->hitbox, &currSlope);
  }
}

void player_update(void){
  float speedMultiplayer;
  for (int i = 0; i < numPlayers; ++i) {

    if(numPlayers > 2){
      speedMultiplayer = SPEED_MODIFIER * SPEED_MODIFIER;
    } else {
       speedMultiplayer = SPEED_MODIFIER;
    }
  
  // Transform input direction to camera's coordinate system
  T3DVec3 newDir = {{
    (float)joypad[i].stick_x * 0.05f * player[i]->cam.camResults.right.v[0] + -(float)joypad[i].stick_y * 0.05f * player[i]->cam.camResults.forward.v[0],
    0, // :.[
    (float)joypad[i].stick_x * 0.05f * player[i]->cam.camResults.right.v[2] + -(float)joypad[i].stick_y * 0.05f * player[i]->cam.camResults.forward.v[2]
  }};
  float speed = sqrtf(t3d_vec3_len2(&newDir));

  // Player Jump Input
  if(btn[i].a) {
    if (playerState[i] == PLAYER_IDLE || playerState[i] == PLAYER_WALK)
    {
      sound_jump();
      playerState[i] = PLAYER_JUMP_START;
    }
  }

  // Player Attack Input
  if(btn[i].b) {
    sound_jump();
    playerState[i] = PLAYER_ATTACK_START;

  }

  // Player movement
  if(speed > 0.1f && playerState[i] != PLAYER_JUMP_START 
              && playerState[i] != PLAYER_JUMP 
              && playerState[i] != PLAYER_ATTACK_START 
              && playerState[i] != PLAYER_ATTACK) {
    newDir.v[0] /= speed;
    newDir.v[2] /= speed;
    player[i]->moveDir = newDir;

    float newAngle = atan2f(player[i]->moveDir.v[0], player[i]->moveDir.v[2]);
    player[i]->yaw = t3d_lerp_angle(player[i]->yaw, newAngle, 0.5f);
    player[i]->currSpeed = t3d_lerp(player[i]->currSpeed, speed * 0.2f, 0.2f);
    player[i]->currSpeed *= speedMultiplayer;

  } else if (speed > 0.1f && playerState[i] == PLAYER_JUMP) {
    newDir.v[0] /= speed;
    newDir.v[2] /= speed;
    player[i]->moveDir = newDir;

    float newAngle = atan2f((player[i]->moveDir.v[0]), (player[i]->moveDir.v[2]));
    player[i]->yaw = t3d_lerp_angle(player[i]->yaw, newAngle, 0.7f);
    player[i]->currSpeed = t3d_lerp(player[i]->currSpeed, speed * 0.6f, 0.6f);
    player[i]->currSpeed *= speedMultiplayer;

  } else {
    player[i]->currSpeed *= 0.8f * speedMultiplayer;
  }

  // use blend based on speed for smooth transitions
  player[i]->animBlend = player[i]->currSpeed / 0.51f;
  if(player[i]->animBlend > 1.0f)player[i]->animBlend = 1.0f;

  // move player...
  player[i]->pos.v[0] += player[i]->moveDir.v[0] * player[i]->currSpeed;
  player[i]->pos.v[2] += player[i]->moveDir.v[2] * player[i]->currSpeed;

  // Update player bounding box
  player[i]->hitbox.center.v[0] = player[i]->pos.v[0];
  player[i]->hitbox.center.v[1] = player[i]->pos.v[1] + player[i]->hitbox.radius;
  player[i]->hitbox.center.v[2] = player[i]->pos.v[2];

  // Limit position inside of bounds
  if(player[i]->pos.v[0] < FloorBox.min.v[0]) player[i]->pos.v[0] = FloorBox.min.v[0];
  if(player[i]->pos.v[0] >  FloorBox.max.v[0])player[i]->pos.v[0] = FloorBox.max.v[0];
  if(player[i]->pos.v[2] < FloorBox.min.v[2]) player[i]->pos.v[2] = FloorBox.min.v[2];
  if(player[i]->pos.v[2] >  FloorBox.max.v[2])player[i]->pos.v[2] = FloorBox.max.v[2];

  // Update the animation and modify the skeleton, this will however NOT recalculate the matrices
  t3d_anim_update(&animIdle[i], deltaTime);
  if (playerState[i] == PLAYER_IDLE || playerState[i] == PLAYER_WALK){
    t3d_anim_set_speed(&animWalk[i], player[i]->animBlend);
    t3d_anim_update(&animWalk[i], deltaTime);
  }
  
  // do walk
  if(player[i]->isGrounded && player[i]->currSpeed > 0.1f){
    if(playerState[i] != PLAYER_JUMP_START 
      && playerState[i] != PLAYER_JUMP 
      && playerState[i] != PLAYER_FALL 
      && playerState[i] != PLAYER_ATTACK_START 
      && playerState[i] != PLAYER_ATTACK) {

      playerState[i] = PLAYER_WALK;
    }
  }

  // Check for collision with players then actors at ground level
  if(player[i]->pos.v[1] == groundLevel){
    if(numPlayers > 1){
      check_player_collisions(player, numPlayers);
    }
    check_actor_collisions(crates, numCrates, i);
    check_actor_collisions(balls, numBalls, i);
    player_to_slope(i);
    player_to_wall(i);
  }

  // Check for collision with players then actors if grounded above ground level
  if(player[i]->pos.v[1] != groundLevel && (playerState[i] == PLAYER_IDLE || playerState[i] == PLAYER_WALK)){
    if(numPlayers > 1){
      check_player_collisions(player, numPlayers);
    }
    
    check_midair_actor_collisions(crates, numCrates, i);
    check_actor_collisions(balls, numBalls, i);
    player_to_slope(i);
    player_to_wall(i);

  }

  // do fall
  if(playerState[i] == PLAYER_FALL) {
    t3d_anim_update(&animFall[i], deltaTime);

    if(numPlayers > 1){
      check_player_collisions(player, numPlayers);
    }
    
    check_midair_actor_collisions(crates, numCrates, i);
    check_actor_collisions(balls, numBalls, i);
    player_to_slope(i);
    player_to_wall(i);

    if(!player[i]->isGrounded){
      if (player[i]->pos.v[1] > groundLevel) {
        player[i]->vel.v[1] += GRAVITY * jumpTime;
        player[i]->pos.v[1] += player[i]->vel.v[1] * jumpTime;
        playerScaleY[i] -= 0.02f;
        if(playerScaleY[i] < 0.3f){
          playerScaleY[i] = 0.3f;
        }
      } else if (player[i]->pos.v[1] <= groundLevel) {
        playerState[i] = PLAYER_LAND;
        player[i]->vel.v[1] = 0.0f;
        playerScaleY[i] = 1.0f;
        if(numPlayers > 2){
          player[i]->jumpForce = 14.0f * JUMP_MODIFIER;
        } else {
          player[i]->jumpForce = 10.0f * JUMP_MODIFIER;
        }
      }
    }
  }

  // do land
  if(playerState[i] == PLAYER_LAND){
    playerState[i] = PLAYER_IDLE;
  }

  //do attack
  if(playerState[i] == PLAYER_ATTACK_START){
    t3d_anim_set_playing(&animAttack[i], true);
    t3d_anim_set_time(&animAttack[i], 0.0f);
    player[i]->currSpeed *= 0.5f;
    player[i]->projectile.pos = player[i]->hitbox.center;
    player[i]->projectile.speed = 80.0f;
    player[i]->projectile.isActive = true;
    playerState[i] = PLAYER_ATTACK;
  }

  if(playerState[i] == PLAYER_ATTACK){
  
    t3d_anim_update(&animAttack[i], deltaTime);
    player[i]->currSpeed = 0;
    player[i]->projectile.pos.v[0] += player[i]->projectile.dir.v[0] * player[i]->projectile.speed * deltaTime;
    player[i]->projectile.pos.v[1] += player[i]->projectile.dir.v[1] * player[i]->projectile.speed * deltaTime;
    player[i]->projectile.pos.v[2] += player[i]->projectile.dir.v[2] * player[i]->projectile.speed * deltaTime;

    // Calculate the distance traveled by the projectile from its origin
    float distanceTraveled = t3d_vec3_distance(&player[i]->projectile.pos, &player[i]->hitbox.center);

    // Define the maximum distance the projectile can travel
    float EndPosMax = player[i]->projectile.length;

    // Reverse direction if the maximum distance is reached
    if (distanceTraveled >= EndPosMax) {
      player[i]->projectile.speed = 120.0f;
      player[i]->projectile.dir.v[0] = -player[i]->projectile.dir.v[0];
      player[i]->projectile.dir.v[1] = -player[i]->projectile.dir.v[1];
      player[i]->projectile.dir.v[2] = -player[i]->projectile.dir.v[2];
    }

    // Calculate the end position based on the projectiles's direction and length
    T3DVec3 EndPos;
    EndPos.v[0] = player[i]->projectile.pos.v[0] + player[i]->projectile.dir.v[0] * player[i]->projectile.length;
    EndPos.v[1] = player[i]->projectile.pos.v[1] + player[i]->projectile.dir.v[1] * player[i]->projectile.length;
    EndPos.v[2] = player[i]->projectile.pos.v[2] + player[i]->projectile.dir.v[2] * player[i]->projectile.length;
    t3d_vec3_norm(&EndPos);
    


    // Scale hitbox up and down according to position
    if (distanceTraveled <= EndPosMax) { 
      player[i]->projectile.hitbox.center = player[i]->projectile.pos;
      if(numPlayers > 3){
        player[i]->projectile.hitbox.radius += 2.5f;
      } else {
        player[i]->projectile.hitbox.radius += 1.5f;
      }

      if(player[i]->projectile.hitbox.radius > 20.0f){
        player[i]->projectile.hitbox.radius = 20.0f;
      }
    }

    if(numPlayers > 1){
      check_player_collisions(player, numPlayers);
    }
    check_attack_collisions(crates, numCrates, i);
    check_attack_collisions(balls, numBalls, i);
    player_to_slope(i);
    player_to_wall(i);

    if(!animAttack[i].isPlaying){
      player[i]->projectile.hitbox.center = player[i]->hitbox.center;
      player[i]->projectile.speed = 0.0f;
      player[i]->projectile.isActive = false;
      if (player[i]->isGrounded == true) {
        playerState[i] = PLAYER_IDLE;
      } else {
        playerState[i] = PLAYER_FALL;
      }
    }
  }

  //do jump
  if(playerState[i] == PLAYER_JUMP_START) {

    t3d_anim_set_time(&animJump[i], 0.0f);
    t3d_anim_set_playing(&animJump[i], true);

    if(numPlayers > 1){
      check_player_collisions(player, numPlayers);
    }
    
    check_actor_collisions(crates, numCrates, i);
    check_actor_collisions(balls, numBalls, i);
    player_to_slope(i);
    player_to_wall(i);

    // Apply jump force modifier
    player[i]->vel.v[1] = player[i]->jumpForce;

    playerState[i] = PLAYER_JUMP;
  }

  if(playerState[i] == PLAYER_JUMP){

    t3d_anim_update(&animJump[i], deltaTime);
    playerScaleY[i] += 0.02f;
    if(playerScaleY[i] > 1.4f){
      playerScaleY[i] = 1.4f;
    }

    if (!animJump[i].isPlaying){
      playerState[i] = PLAYER_FALL;
      t3d_anim_set_time(&animFall[i], player[i]->animBlend);
    }

    // Apply gravity
    player[i]->vel.v[1] += GRAVITY * jumpTime;

    // Update player position
    player[i]->pos.v[1] += player[i]->vel.v[1] * jumpTime;

    // Update player bounding box
    player[i]->hitbox.center.v[0] = player[i]->pos.v[0];
    player[i]->hitbox.center.v[1] = player[i]->pos.v[1];
    player[i]->hitbox.center.v[2] = player[i]->pos.v[2];

    // Check for collision with players then actors then floor
    if(numPlayers > 1){
      check_player_collisions(player, numPlayers);
      playerState[i] = PLAYER_FALL;
    }
    
    check_midair_actor_collisions(crates, numCrates, i);
    check_actor_collisions(balls, numBalls, i);
    player_to_slope(i);
    player_to_wall(i);
  }

  // do grounded
  switch(playerState[i]){
    case PLAYER_IDLE:
      player[i]->isGrounded = true;
      break;
    case PLAYER_WALK:
      player[i]->isGrounded = true;
      break;
    case PLAYER_JUMP_START:
      player[i]->isGrounded = false;
      break;
    case PLAYER_JUMP:
      player[i]->isGrounded = false;
      break;
    case PLAYER_FALL:
      player[i]->isGrounded = false;
      break;
    case PLAYER_LAND:
      player[i]->isGrounded = true;
      break;
  }

  if(player[i]->isGrounded) {
    if (player[i]->pos.v[1] < groundLevel) {
      player[i]->pos.v[1] = groundLevel;
    }
    
    if(player[i]->pos.v[1] > groundLevel){
      for (int c = 0; c < numCrates; ++c) {
        int closestCrate = find_closest(player[i]->pos, crates, numCrates);
        if(!check_sphere_box_collision(player[i]->hitbox, crates[closestCrate]->hitbox.shape.aabb)){
          // Check if the player is outside bounds in the x and z directions
          if (player[i]->hitbox.center.v[0] > crates[closestCrate]->hitbox.shape.aabb.max.v[0] ||
              player[i]->hitbox.center.v[0] < crates[closestCrate]->hitbox.shape.aabb.min.v[0] ||
              player[i]->hitbox.center.v[2] > crates[closestCrate]->hitbox.shape.aabb.max.v[2] ||
              player[i]->hitbox.center.v[2] < crates[closestCrate]->hitbox.shape.aabb.min.v[2]) {
            playerState[i] = PLAYER_FALL;
          }
        } else {
          if (player[i]->pos.v[1] < crates[closestCrate]->hitbox.shape.aabb.max.v[1]) {
            playerState[i] = PLAYER_FALL;
          }
        }
      }
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
    player[i]->projectile.hitbox.radius = 8.0f;
  }

  }

}