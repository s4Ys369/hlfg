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
#include "test_level.h"


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
T3DVec3 playerStartPos = {{0,128,0}};
int airAttackCount = 0;
Surface lastSurface;
Surface lastFloor;
Surface lastSlope;


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
  modelPlayer = t3d_model_load("rom:/models/player.t3dm");
  modelProjectile = t3d_model_load("rom:/models/projectile.t3dm");
  modelShadow = t3d_model_load("rom:/models/shadow.t3dm");

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
      rdpq_sync_pipe();
      rdpq_set_mode_standard();
      rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
      t3d_matrix_push_pos(1);
      matCount++;
      t3d_matrix_set(playerhitboxMatFP[i], true);
      rdpq_set_prim_color(T_RED);
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
      rdpq_sync_pipe();
      rdpq_set_mode_standard();
      rdpq_mode_blender(RDPQ_BLENDER_MULTIPLY);
      t3d_matrix_push_pos(1);
      matCount++;
      t3d_matrix_set(projectilehitboxMatFP[i], true);
      rdpq_set_prim_color(T_BLUE);
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
    player[i]->rot = (T3DVec3){{0,0,0}};
    player[i]->scale = (T3DVec3){{1,1,1}};
    player[i]->pos = playerStartPos;
    player[i]->shadowPos = player[i]->pos;
    player[i]->shadowRot = player[i]->rot;
    player[i]->forward = (T3DVec3){{0,0,1}};
    player[i]->hitbox = (Sphere){player[i]->pos, 16.0f};

    player[i]->projectile.pos = player[i]->hitbox.center;
    player[i]->projectile.dir = player[i]->forward;
    player[i]->projectile.hitbox = (Sphere){player[i]->hitbox.center,8.0f};
    player[i]->projectile.speed = 0.0f;
    player[i]->projectile.isActive = false;
    player[i]->projectile.length = 16.0f;

    player[i]->currSpeed = 0.0f;

    player[i]->animBlend = 0.0f;

    player[i]->isGrounded = false;

    player[i]->vel = (T3DVec3){{0,0,0}};

    if(numPlayers > 2){
      player[i]->jumpForce = 650.0f;
    } else {
      player[i]->jumpForce = 600.0f;
    }

    player[i]->score = 0;

  }

  // If more than 1 player, place the players randomly and check for collisions
  if(numPlayers > 1){
    for (int p = 0; p < numPlayers; ++p){
      player[p]->pos = (T3DVec3){{random_float(-320.0f, 320.0f),groundLevel,random_float(-320.0f, 320.0f)}};
      player[p]->hitbox.center = player[p]->pos;
      check_player_collisions(player, numPlayers);

      if (check_sphere_box_collision(player[p]->hitbox, FloorBox)) {
        player[p]->pos = playerStartPos;
        if(!rumbleLong[p] && !rumbleShort[p] && !rumbleWave[p]){
          rumbleShort[p] = true;
        }
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
        resolve_box_collision_offset_xz(currActor->hitbox.shape.aabb, &player[playerCount]->pos, 0.2f);
        t3d_lerp(player[playerCount]->pos.v[0], player[playerCount]->hitbox.center.v[0], 0.2f);
        t3d_lerp(player[playerCount]->pos.v[2], player[playerCount]->hitbox.center.v[2], 0.2f);
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
  float bounceMultiplier = 1.8f;

  playerState[playerCount] = PLAYER_JUMP_START;

  if(!rumbleLong[playerCount] && !rumbleShort[playerCount] && !rumbleWave[playerCount]){
    rumbleLong[playerCount] = true;
  }

  player[playerCount]->vel.v[1] += (player[playerCount]->jumpForce * bounceMultiplier) + GRAVITY * jumpFixedTime;

  player[playerCount]->pos.v[1] += player[playerCount]->vel.v[1] * jumpFixedTime;

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


void player_to_quad(int playerCount){
// quad collisions?
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

// wall surface collisions
void player_to_wall(Surface currWall, int playerCount){
  resolve_sphere_surface_collision(&player[playerCount]->hitbox, &player[playerCount]->pos, &player[playerCount]->vel, &currWall); 
}

// slope surface collisions
void player_to_slope(Surface currSlope, int playerCount){
  resolve_sphere_surface_collision(&player[playerCount]->hitbox, &player[playerCount]->pos, &player[playerCount]->moveDir, &currSlope);
  playerState[playerCount] = PLAYER_SLIDE;
  airAttackCount = 0;
  lastSlope = currSlope;
  lastSurface = lastSlope;
}

// floor surface collisions
void player_to_floor(Surface currFloor, int playerCount){
    if(player[playerCount]->isGrounded == true && player[playerCount]->pos.v[1] <= currFloor.center.v[1]){
      player[playerCount]->pos.v[1] = currFloor.center.v[1];
      resolve_sphere_surface_collision(&player[playerCount]->hitbox, &player[playerCount]->pos, &player[playerCount]->vel, &currFloor);
    }
    if (!player[playerCount]->isGrounded){
      playerState[playerCount] = PLAYER_LAND;
    }
    lastFloor = currFloor;
    lastSurface = lastFloor;
    airAttackCount = 0;
}


 float searchDiameter = 0;

Surface closestFloors[8];
int closestFloorsCount;
Surface currFloor;
RaycastResult nextFloor;

Surface currSlope;

Surface currWall;
Surface closestWalls[4];
int closestWallsCount;

Surface closestSurfaces[3];
int closestCount;

void get_batched_surfaces(int playerCount){
  searchDiameter = player[playerCount]->hitbox.radius * 4.0f; // Double the player's hitbox diameter
  find_closest_surfaces_any_type(player[playerCount]->hitbox.center, testLevelSurfaces, testLevelSurfacesCount, closestSurfaces, &closestCount, searchDiameter);
  
  find_closest_surfaces(player[playerCount]->pos, testLevelFloor, testLevelFloorCount, closestFloors, &closestFloorsCount, SURFACE_FLOOR, searchDiameter);
  currFloor = find_closest_surface(player[playerCount]->hitbox.center, closestFloors, closestFloorsCount);
  nextFloor = closest_surface_below_raycast(player[playerCount]->hitbox.center, testLevelFloor, testLevelFloorCount);

  
  find_closest_surfaces(player[playerCount]->pos, testLevelWall, testLevelWallCount, closestWalls, &closestWallsCount, SURFACE_WALL, searchDiameter);
  currWall = find_closest_surface(player[playerCount]->hitbox.center, closestWalls, closestWallsCount);

  currSlope = find_closest_surface(player[playerCount]->hitbox.center, testLevelSlope, testLevelSlopeCount);
}

void player_surface_collider(int playerCount){

  bool hitFloor = false, hitWall = false, hitSlope = false;

  // Check collisions with floors
  for (int i = 0; i < closestFloorsCount; ++i) {
      if (check_sphere_surface_collision(player[playerCount]->hitbox, closestFloors[i])) {
          hitFloor = true;
          currFloor = closestFloors[i];
          break; // Stop after finding the first collision
      }
  }

  // Check collisions with walls
  for (int i = 0; i < closestWallsCount; ++i) {
      if (check_sphere_surface_collision(player[playerCount]->hitbox, closestWalls[i])) {
          hitWall = true;
          currWall = closestWalls[i];
          break; // Stop after finding the first collision
      }
  }

  // Check collisions with slopes
  if (check_sphere_surface_collision(player[playerCount]->hitbox, currSlope)) {
      hitSlope = true;
  }

  // Resolve collisions
  if (hitFloor) {
      player_to_floor(currFloor, playerCount);
      if (hitSlope) player_to_slope(currSlope, playerCount);
      if (hitWall) player_to_wall(currWall, playerCount);
  } else if (hitSlope) {
      player_to_slope(currSlope, playerCount);
      if (hitWall) player_to_wall(currWall, playerCount);
  } else if (hitWall) {
      player_to_wall(currWall, playerCount);
  }

  hitSlope = hitWall = hitFloor = false;
}


void player_update(void){
  float speedMultiplayer;
  for (int i = 0; i < numPlayers; ++i) {

    if(numPlayers > 2){
      speedMultiplayer = 1.2f;
    } else {
       speedMultiplayer = 1.1f;
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
    if (playerState[i] == PLAYER_IDLE || playerState[i] == PLAYER_WALK || playerState[i] == PLAYER_SLIDE)
    {
      sound_jump();
      playerState[i] = PLAYER_JUMP_START;
      if(!rumbleLong[i] && !rumbleShort[i] && !rumbleWave[i]){
        rumbleShort[i] = true;
      }
    }
  }

  // Player Attack Input
  if(btn[i].b) {
    sound_attack();
    playerState[i] = PLAYER_ATTACK_START;
    if(!rumbleLong[i] && !rumbleShort[i] && !rumbleWave[i]){
      rumbleShort[i] = true;
    }
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
    player[i]->rot.v[1] = t3d_lerp_angle(player[i]->rot.v[1], newAngle, 0.5f);
    player[i]->currSpeed = t3d_lerp(player[i]->currSpeed, speed * 0.2f, 0.2f);
    player[i]->currSpeed *= speedMultiplayer;

  } else if (speed > 0.1f && playerState[i] == PLAYER_JUMP) {
    newDir.v[0] /= speed;
    newDir.v[2] /= speed;
    player[i]->moveDir = newDir;

    float newAngle = atan2f((player[i]->moveDir.v[0]), (player[i]->moveDir.v[2]));
    player[i]->rot.v[1] = t3d_lerp_angle(player[i]->rot.v[1], newAngle, 0.7f);
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
  if(player[i]->isGrounded){
    if(playerState[i] != PLAYER_JUMP_START 
      && playerState[i] != PLAYER_JUMP 
      && playerState[i] != PLAYER_FALL 
      && playerState[i] != PLAYER_SLIDE
      && playerState[i] != PLAYER_ATTACK_START 
      && playerState[i] != PLAYER_ATTACK) {
        if(player[i]->currSpeed > 0.1f) {
          playerState[i] = PLAYER_WALK;
        } else {
          playerState[i] = PLAYER_IDLE;
        }
    }
  }

  get_batched_surfaces(i);

  // Check for collision with players then actors if in grounded asction state
  if(playerState[i] == PLAYER_IDLE || playerState[i] == PLAYER_WALK){
    if(numPlayers > 1){
      check_player_collisions(player, numPlayers);
    }

    player_surface_collider(i);
    
    check_actor_collisions(crates, numCrates, i);
    check_actor_collisions(balls, numBalls, i);

  }

  // do fall
  if(playerState[i] == PLAYER_FALL) {
    t3d_anim_update(&animFall[i], deltaTime);

    if(numPlayers > 1){
      check_player_collisions(player, numPlayers);
    }
    
    player_surface_collider(i);

    check_midair_actor_collisions(crates, numCrates, i);
    check_actor_collisions(balls, numBalls, i);

    if(!player[i]->isGrounded){
      if (player[i]->pos.v[1] > groundLevel) {
        // Slow fall while holding A
        if(btnheld[i].a){
          player[i]->vel.v[1] = t3d_lerp(player[i]->vel.v[1], GRAVITY, fallFixedTime);
          player[i]->pos.v[1] = t3d_lerp(player[i]->pos.v[1],player[i]->vel.v[1], fallFixedTime);
          player[i]->hitbox.center.v[1] = t3d_lerp(player[i]->hitbox.center.v[1],player[i]->pos.v[1], fallFixedTime);
        } else {
          player[i]->vel.v[1] = t3d_lerp(player[i]->vel.v[1], GRAVITY, jumpFixedTime);
          player[i]->pos.v[1] = t3d_lerp(player[i]->pos.v[1],player[i]->vel.v[1], jumpFixedTime);
          player[i]->hitbox.center.v[1] = t3d_lerp(player[i]->hitbox.center.v[1],player[i]->pos.v[1], jumpFixedTime);
        }
        player[i]->scale.v[1] -= 0.02f;
        if(player[i]->scale.v[1] < 0.3f){
          player[i]->scale.v[1] = 0.3f;
        }

      } else if (player[i]->pos.v[1] <= groundLevel) {
        player[i]->pos = playerStartPos;
        player[i]->vel.v[1] = 0.0f;
        player[i]->scale.v[1] = 1.0f;
        if(numPlayers > 2){
          player[i]->jumpForce = 650.0f;
        } else {
          player[i]->jumpForce = 600.0f;
        }
      }
    }
  }

  // do land
  while(playerState[i] == PLAYER_LAND){
    player[i]->scale.v[1] = 1.0f;
    playerState[i] = PLAYER_IDLE;
    if(!rumbleLong[i] && !rumbleShort[i] && !rumbleWave[i]){
        rumbleLong[i] = true;
      }
    break;
  }

  // do slide/slope interaction
  if(playerState[i] == PLAYER_SLIDE){
    player[i]->scale.v[1] = 1.0f;
    player[i]->cam.camPos.v[1] = player[i]->hitbox.center.v[1];
    player[i]->cam.camTarget.v[1] = player[i]->hitbox.center.v[1];
    if(!rumbleLong[i] && !rumbleShort[i] && !rumbleWave[i]){
      rumbleWave[i] = true;
    }
    playerState[i] = PLAYER_WALK;
  }


  //do attack
  if(playerState[i] == PLAYER_ATTACK_START){
    if(airAttackCount == 0){
      t3d_anim_set_playing(&animAttack[i], true);
      t3d_anim_set_time(&animAttack[i], 0.0f);
      player[i]->scale.v[1] = 1.0f;
      player[i]->currSpeed *= 0.5f;
      player[i]->projectile.pos = player[i]->hitbox.center;
      player[i]->projectile.speed = 80.0f;
      player[i]->projectile.isActive = true;
      playerState[i] = PLAYER_ATTACK;
    } else {
      playerState[i] = PLAYER_FALL;
    }
  }

  if(playerState[i] == PLAYER_ATTACK){
  
    t3d_anim_update(&animAttack[i], deltaTime);
    player[i]->currSpeed = 0;
    player[i]->projectile.pos.v[0] += player[i]->projectile.dir.v[0] * player[i]->projectile.speed * fixedTime;
    player[i]->projectile.pos.v[1] += player[i]->projectile.dir.v[1] * player[i]->projectile.speed * fixedTime;
    player[i]->projectile.pos.v[2] += player[i]->projectile.dir.v[2] * player[i]->projectile.speed * fixedTime;

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

    if(!animAttack[i].isPlaying){
      player[i]->projectile.hitbox.center = player[i]->hitbox.center;
      player[i]->projectile.speed = 0.0f;
      player[i]->projectile.isActive = false;
      if (player[i]->isGrounded == true) {
        playerState[i] = PLAYER_WALK;
      } else {
        airAttackCount++;
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
    player_surface_collider(i);

    Surface currSlope = find_closest_surface(player[i]->hitbox.center, testLevelSlope, testLevelSlopeCount);
    if (check_sphere_surface_collision(player[i]->hitbox, currSlope)){
      player[i]->pos.v[1] += player[i]->hitbox.radius * 2.5f;
    }
    Surface currFloor = find_closest_surface(player[i]->hitbox.center, testLevelFloor, testLevelFloorCount);
    if (check_sphere_surface_collision(player[i]->hitbox, currFloor)){
      player[i]->pos.v[1] += player[i]->hitbox.radius;
    }

    // Apply jump force modifier
    player[i]->vel.v[1] = player[i]->jumpForce + player[i]->pos.v[1];

    playerState[i] = PLAYER_JUMP;
  }

  if(playerState[i] == PLAYER_JUMP){

    t3d_anim_update(&animJump[i], jumpTime);
    player[i]->scale.v[1] += 0.02f;
    if(player[i]->scale.v[1] > 1.4f){
      player[i]->scale.v[1] = 1.4f;
    }

    if (!animJump[i].isPlaying){
      playerState[i] = PLAYER_FALL;
      t3d_anim_set_time(&animFall[i], player[i]->animBlend);
    }

    // Apply gravity
    player[i]->vel.v[1] = t3d_lerp(player[i]->vel.v[1], GRAVITY, fixedTime);

    // Update player position
    player[i]->pos.v[1] = t3d_lerp(player[i]->pos.v[1], player[i]->vel.v[1], fixedTime);

    // Update player bounding box
    t3d_vec3_lerp(&player[i]->hitbox.center, &player[i]->pos, &player[i]->hitbox.center, fixedTime);
    player[i]->hitbox.center.v[1] = player[i]->hitbox.center.v[1] + player[i]->hitbox.radius;

    // Check for collision with players then actors then floor
    if(numPlayers > 1){
      check_player_collisions(player, numPlayers);
    }

    player_surface_collider(i);

    check_midair_actor_collisions(crates, numCrates, i);
    check_actor_collisions(balls, numBalls, i);
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
    case PLAYER_SLIDE:
      player[i]->isGrounded = true;
      break;
  }

  if(player[i]->isGrounded) {
    if (player[i]->pos.v[1] < groundLevel) {
      player[i]->pos = playerStartPos;
    }
    
    if(player[i]->pos.v[1] > groundLevel){
      Surface currSlope = find_closest_surface(player[i]->hitbox.center, testLevelSlope, testLevelSlopeCount);
      if (!check_sphere_surface_collision(player[i]->hitbox, currSlope)){
        Surface currFloor = find_closest_surface(player[i]->hitbox.center, testLevelFloor, testLevelFloorCount);
        if (!check_sphere_surface_collision(player[i]->hitbox, currFloor)){
          for (int c = 0; c < numCrates; ++c) {
            int closestCrate = find_closest(player[i]->pos, crates, numCrates);
            if(!check_sphere_box_collision(player[i]->hitbox, crates[closestCrate]->hitbox.shape.aabb)){
              // Check if the player is outside bounds in the x and z directions
              if (player[i]->hitbox.center.v[0] >= crates[closestCrate]->hitbox.shape.aabb.max.v[0] ||
                  player[i]->hitbox.center.v[0] <= crates[closestCrate]->hitbox.shape.aabb.min.v[0] ||
                  player[i]->hitbox.center.v[2] >= crates[closestCrate]->hitbox.shape.aabb.max.v[2] ||
                  player[i]->hitbox.center.v[2] <= crates[closestCrate]->hitbox.shape.aabb.min.v[2]) {

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
    }
  }


  // Handle surface rotations
  float pitch = 0;
  //float roll = 0;
  if(lastSurface.type == SURFACE_FLOOR){
    pitch = 0;
    //roll = 0;
  } else {
    T3DVec3 lastSurfaceNormal = lastSurface.normal;
    t3d_vec3_norm(&lastSurfaceNormal);
    pitch = atan2f(lastSurfaceNormal.v[2], lastSurfaceNormal.v[1]);
    pitch = pitch * 180.0f / T3D_PI;
    pitch = clamp(pitch, 0.6f, -0.6f);
    //roll = atan2f(lastSurfaceNormal.v[1], lastSurfaceNormal.v[0]);
    //roll = roll * 180.0f / T3D_PI;
    //roll = clamp(roll, 0.3f, -0.3f);
  }
  
  if(!player[i]->isGrounded){
    player[i]->rot.v[0] = t3d_lerp_angle(player[i]->rot.v[0], 0, 0.6f);
    //player[i]->rot.v[2] = t3d_lerp_angle(player[i]->rot.v[2], 0, 0.6f);
  } else {
    player[i]->rot.v[0] = t3d_lerp_angle(player[i]->rot.v[0], pitch, 0.2f);
    //player[i]->rot.v[2] = t3d_lerp_angle(player[i]->rot.v[2], roll, 0.1f);
  }


  // update shadow
  player[i]->shadowPos.v[0] = player[i]->pos.v[0];
  player[i]->shadowPos.v[2] = player[i]->pos.v[2];
  player[i]->shadowRot = player[i]->rot;
  RaycastResult raySlope = closest_surface_below_raycast(player[i]->pos, testLevelSlope, testLevelSlopeCount);
  
  float dist_player_next_floor = distance_to_surface(player[i]->hitbox.center, currFloor);
  float dist_player_next_slope = distance_to_surface(player[i]->hitbox.center, currSlope);
  
  bool shadowOnSlope = false;

  if (dist_player_next_slope < dist_player_next_floor){
    shadowOnSlope = true;
  } else {
    shadowOnSlope = false;
  }


  if(!player[i]->isGrounded){
    if(shadowOnSlope){
      if(dist_player_next_slope > player[i]->hitbox.radius*2.0f){    
        player[i]->shadowPos.v[1] = t3d_lerp(player[i]->shadowPos.v[1], raySlope.posY, 0.7f);
      } else { 
        player[i]->shadowPos.v[1] = nextFloor.surf.center.v[1];
      }
    } else {
      player[i]->shadowPos.v[1] = t3d_lerp(player[i]->shadowPos.v[1], nextFloor.surf.center.v[1], 0.7f);
    }
  } else {
    player[i]->shadowPos.v[1] = player[i]->pos.v[1];
  }

  //reset projectile
  if(player[i]->projectile.speed == 0.0f){
    update_player_forward(&player[i]->forward, player[i]->rot.v[1]);
    player[i]->projectile.pos = player[i]->hitbox.center;
    player[i]->projectile.dir = player[i]->forward;
    player[i]->projectile.hitbox.center =  player[i]->projectile.pos;
    player[i]->projectile.hitbox.radius = 8.0f;
  }

  }

}