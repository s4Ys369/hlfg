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
      rdpq_set_prim_color(BLUE);
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
      player[i]->jumpForce = player[i]->pos.v[1] + 450.0f;
    } else {
      player[i]->jumpForce = player[i]->pos.v[1] + 400.0f;
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
    //player[playerCount]->vel = reflect_velocity(player[playerCount]->vel, currQuadNorm);
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
  playerState[playerCount] = PLAYER_LAND;
  resolve_sphere_surface_collision(&player[playerCount]->hitbox, &player[playerCount]->pos, &player[playerCount]->moveDir, &currFloor);
  if(player[playerCount]->isGrounded == true && player[playerCount]->pos.v[1] < currFloor.center.v[1]){
    player[playerCount]->pos.v[1] = currFloor.center.v[1];
  }
  lastFloor = currFloor;
  lastSurface = lastFloor;
  airAttackCount = 0;
}


void player_surface_collider(int playerCount){

  // Find all closest surface types
  Surface currWall = find_closest_surface(player[playerCount]->hitbox.center, testLevelWall, testLevelWallCount);
  Surface currFloor = find_closest_surface(player[playerCount]->hitbox.center, testLevelFloor, testLevelFloorCount);
  Surface nextFloor = closest_surface_below_raycast(player[playerCount]->hitbox.center, testLevelFloor, testLevelFloorCount);
  Surface currSlope = find_closest_surface(player[playerCount]->hitbox.center, testLevelSlope, testLevelSlopeCount);

  // Check collisions for all
  bool hitSlope = false;
  bool hitFloor = false;
  bool hitWall = false;
  if (check_sphere_surface_collision(player[playerCount]->hitbox, currSlope)){hitSlope = true;}
  if(player[playerCount]->isGrounded){
    if (check_sphere_surface_collision(player[playerCount]->hitbox, currFloor)){hitFloor = true;}
  } else {
    if (ray_intersects_surface(player[playerCount]->hitbox.center, down, currFloor, &intersectionY)){hitFloor = true;}
  }
  if (check_sphere_surface_collision(player[playerCount]->hitbox, currWall)){hitWall = true;}

  // Get distances
  float dist_player_to_slope = distance_to_surface(player[playerCount]->hitbox.center, currSlope);
  float dist_player_to_floor = distance_to_surface(player[playerCount]->hitbox.center, currFloor);
  float dist_player_to_lowest = fabsf(player[playerCount]->pos.v[1] - intersectionY);
  float dist_player_to_wall = distance_to_surface(player[playerCount]->hitbox.center, currWall);
  float dist_slope_to_floor = t3d_vec3_distance(&currSlope.center, &currFloor.center);
  float dist_slope_to_wall = t3d_vec3_distance(&currSlope.center, &currWall.center);
  float dist_wall_to_floor = t3d_vec3_distance(&currWall.center, &currFloor.center);

  // Determine the which collisions and in which order to handle
  if(player[playerCount]->isGrounded){
    if(hitSlope){
      if(hitFloor){
        if(dist_slope_to_floor >= player[playerCount]->hitbox.radius){
          if(dist_player_to_slope <= dist_player_to_floor){
            player_to_slope(currSlope, playerCount);
          } else {
            player_to_floor(currFloor, playerCount);
          }
        } else {
          if(dist_player_to_slope <= dist_player_to_floor){
            player_to_floor(currFloor, playerCount);
          } else {
            player_to_slope(currSlope, playerCount);
          }
        }
      } else if(hitWall){
        if(dist_slope_to_wall >= player[playerCount]->hitbox.radius){
          if(dist_player_to_slope <= dist_player_to_wall){
            player_to_slope(currSlope, playerCount);
          } else {
            player_to_wall(currWall, playerCount);
          }
        } else {
          if(dist_player_to_slope <= dist_player_to_wall){
            player_to_wall(currWall, playerCount);
          } else {
            player_to_slope(currSlope, playerCount);
          }
        }
      } else {
        player_to_slope(currSlope, playerCount);
      }
    }


    if (hitWall) {
      if (hitFloor) {
        if (dist_wall_to_floor <= player[playerCount]->hitbox.radius) {
          // Check which distance is greater to decide the collision handling
          if (dist_player_to_wall > dist_player_to_floor) {
            player_to_floor(currFloor, playerCount);
          } else {
            player_to_wall(currWall, playerCount);
          }
          // Adjust vertical position
          player[playerCount]->pos.v[1] = currFloor.center.v[1] + player[playerCount]->hitbox.radius * 1.5;
          } else {
            player_to_wall(currWall, playerCount);
          }
      } else {
          if (dist_player_to_wall <= player[playerCount]->hitbox.radius) {
            player_to_wall(currWall, playerCount);
          }
      }
    }

    if(hitFloor){
      if(hitSlope){
        if(hitWall){
          player_to_wall(currWall, playerCount);
          player_to_floor(currFloor, playerCount);
        } else {
          if(dist_player_to_slope <= dist_player_to_floor){
            player_to_slope(currSlope, playerCount);
          } else {
            player_to_floor(currFloor, playerCount);
          }
        }
      } else {
        player_to_floor(currFloor, playerCount);
      }
    }
  } else {
    // Check if there's a floor below and if it is close enough to collide with
    if(player[playerCount]->hitbox.center.v[1] < currFloor.center.v[1]){
      hitFloor = true;
    }
    if(player[playerCount]->hitbox.center.v[1] < nextFloor.center.v[1]){
      hitFloor = true;
    }
    if(player[playerCount]->hitbox.center.v[1] < 0){ // 0 should be lowest floor
      hitFloor = true;
    }

    if(hitSlope){
      if (dist_player_to_slope < player[playerCount]->hitbox.radius*2){
        player_to_slope(currSlope, playerCount);
      }
    }

    //if(hitWall){
    //  if(dist_player_to_wall < player[playerCount]->hitbox.radius*0.5f){
    //    player_to_wall(currWall, playerCount);
    //  }
    //}

    if(hitFloor){
      if(dist_player_to_lowest < player[playerCount]->hitbox.radius + player[playerCount]->currSpeed){
        player_to_floor(nextFloor, playerCount);
      }
      // ... otherwise
      if(hitSlope){
        if(hitWall){
          // ... if hitting both, check distances
          if(dist_player_to_slope > dist_player_to_wall){
            // ... if wall is closer and close enough to collide with
            if (dist_player_to_wall < player[playerCount]->hitbox.radius){
              player_to_wall(currWall, playerCount);
              player_to_floor(currFloor, playerCount);
            }
          } else {
            // ... otherwise, slope
            player_to_slope(currSlope, playerCount);
            player_to_floor(currFloor, playerCount);
          }
          
        } else {
          if(dist_player_to_slope < dist_player_to_floor){
            if (dist_player_to_slope < player[playerCount]->hitbox.radius*2){
              player_to_slope(currSlope, playerCount);
            } else {
              player_to_floor(currFloor, playerCount);
            }
          } else {
            if (dist_player_to_slope < player[playerCount]->hitbox.radius*2){
              player_to_slope(currSlope, playerCount);
            } else {
              player_to_floor(currFloor, playerCount);
            }
          }
        }
      }

      if(hitWall){
        if(dist_player_to_wall < dist_player_to_floor){
          if(dist_player_to_wall < 5.0f){
            player_to_wall(currWall, playerCount);
            player_to_floor(currFloor, playerCount);
          }
        } else {
          player_to_floor(currFloor, playerCount);
        }
      }

      if(dist_player_to_floor < dist_player_to_lowest){
        if(player[playerCount]->hitbox.center.v[1] > currFloor.center.v[1] + player[playerCount]->hitbox.radius){
          player_to_floor(currFloor, playerCount);
        }
      }
    }
  }

}

float speed = 0;

// Handles rotation from input, applying speed to position, and limit player in bounds
void update_movement(int playerCount){

  // Transform input direction to camera's coordinate system
  T3DVec3 newDir = {{
    (float)joypad[playerCount].stick_x * 0.05f * player[playerCount]->cam.camResults.right.v[0] + -(float)joypad[playerCount].stick_y * 0.05f * player[playerCount]->cam.camResults.forward.v[0],
    0, // :.[
    (float)joypad[playerCount].stick_x * 0.05f * player[playerCount]->cam.camResults.right.v[2] + -(float)joypad[playerCount].stick_y * 0.05f * player[playerCount]->cam.camResults.forward.v[2]
  }};
  speed = sqrtf(t3d_vec3_len2(&newDir));

  // Calculate yaw rotation and speed
  if(speed > 0.1f && playerState[playerCount] != PLAYER_JUMP_START 
              && playerState[playerCount] != PLAYER_JUMP 
              && playerState[playerCount] != PLAYER_ATTACK_START 
              && playerState[playerCount] != PLAYER_ATTACK) {
    newDir.v[0] /= speed;
    newDir.v[2] /= speed;
    player[playerCount]->moveDir = newDir;

    float newAngle = atan2f(player[playerCount]->moveDir.v[0], player[playerCount]->moveDir.v[2]);
    player[playerCount]->rot.v[1] = t3d_lerp_angle(player[playerCount]->rot.v[1], newAngle, 0.5f);
    player[playerCount]->currSpeed = t3d_lerp(player[playerCount]->currSpeed, speed * 0.2f, 0.2f);
    player[playerCount]->currSpeed *= 1.1f;
  } else if (speed > 0.1f && playerState[playerCount] == PLAYER_JUMP) {
    newDir.v[0] /= speed;
    newDir.v[2] /= speed;
    player[playerCount]->moveDir = newDir;

    float newAngle = atan2f((player[playerCount]->moveDir.v[0]), (player[playerCount]->moveDir.v[2]));
    player[playerCount]->rot.v[1] = t3d_lerp_angle(player[playerCount]->rot.v[1], newAngle, 0.7f);
    player[playerCount]->currSpeed = t3d_lerp(player[playerCount]->currSpeed, speed * 0.6f, 0.6f);
    player[playerCount]->currSpeed *= 1.1f;
  } else {
    player[playerCount]->currSpeed *= 0.8f;
  }

  // Update position
  player[playerCount]->pos.v[0] += player[playerCount]->moveDir.v[0] * player[playerCount]->currSpeed;
  player[playerCount]->pos.v[2] += player[playerCount]->moveDir.v[2] * player[playerCount]->currSpeed;

  // Update player bounding box
  player[playerCount]->hitbox.center.v[0] = player[playerCount]->pos.v[0];
  player[playerCount]->hitbox.center.v[1] = player[playerCount]->pos.v[1] + player[playerCount]->hitbox.radius;
  player[playerCount]->hitbox.center.v[2] = player[playerCount]->pos.v[2];

  // Limit position inside of bounds
  if(player[playerCount]->pos.v[0] < FloorBox.min.v[0]) player[playerCount]->pos.v[0] = FloorBox.min.v[0];
  if(player[playerCount]->pos.v[0] >  FloorBox.max.v[0])player[playerCount]->pos.v[0] = FloorBox.max.v[0];
  if(player[playerCount]->pos.v[2] < FloorBox.min.v[2]) player[playerCount]->pos.v[2] = FloorBox.min.v[2];
  if(player[playerCount]->pos.v[2] >  FloorBox.max.v[2])player[playerCount]->pos.v[2] = FloorBox.max.v[2];

}

void player_jump(int playerCount){

  // Player Jump Input
  if(btn[playerCount].a) {
    if (playerState[playerCount] == PLAYER_IDLE || playerState[playerCount] == PLAYER_WALK || playerState[playerCount] == PLAYER_SLIDE)
    {
      sound_jump();
      playerState[playerCount] = PLAYER_JUMP_START;
    }
  }

  // Enter Jump prep state
  if(playerState[playerCount] == PLAYER_JUMP_START) {

    t3d_anim_set_time(&animJump[playerCount], 0.0f);
    t3d_anim_set_playing(&animJump[playerCount], true);

    // Apply jump force modifier
    player[playerCount]->vel.v[1] = player[playerCount]->jumpForce;

    playerState[playerCount] = PLAYER_JUMP;
  }

  // Full Jump state
  if(playerState[playerCount] == PLAYER_JUMP){

    t3d_anim_update(&animJump[playerCount], jumpTime);
    player[playerCount]->scale.v[1] += 0.02f;
    if(player[playerCount]->scale.v[1] > 1.4f){
      player[playerCount]->scale.v[1] = 1.4f;
    }

    if (!animJump[playerCount].isPlaying){
      playerState[playerCount] = PLAYER_FALL;
      t3d_anim_set_time(&animFall[playerCount], player[playerCount]->animBlend);
    }

    // Apply gravity
    player[playerCount]->vel.v[1] = t3d_lerp(player[playerCount]->vel.v[1], GRAVITY, jumpFixedTime);

    // Update player position
    player[playerCount]->pos.v[1] = t3d_lerp(player[playerCount]->pos.v[1],player[playerCount]->vel.v[1], jumpFixedTime);

    // Update player bounding box
    player[playerCount]->hitbox.center.v[0] = player[playerCount]->pos.v[0];
    player[playerCount]->hitbox.center.v[1] = player[playerCount]->pos.v[1] + player[playerCount]->hitbox.radius;
    player[playerCount]->hitbox.center.v[2] = player[playerCount]->pos.v[2];

  }
}

void player_attack(int playerCount){
  // Player Attack Input
  if(btn[playerCount].b) {
    sound_attack();
    playerState[playerCount] = PLAYER_ATTACK_START;

  }

  //do attack
  if(playerState[playerCount] == PLAYER_ATTACK_START){
    if(airAttackCount == 0){
      t3d_anim_set_playing(&animAttack[playerCount], true);
      t3d_anim_set_time(&animAttack[playerCount], 0.0f);
      player[playerCount]->scale.v[1] = 1.0f;
      player[playerCount]->currSpeed *= 0.5f;
      player[playerCount]->projectile.pos = player[playerCount]->hitbox.center;
      player[playerCount]->projectile.speed = 80.0f;
      player[playerCount]->projectile.isActive = true;
      playerState[playerCount] = PLAYER_ATTACK;
    } else {
      playerState[playerCount] = PLAYER_FALL;
    }
  }

  if(playerState[playerCount] == PLAYER_ATTACK){
  
    t3d_anim_update(&animAttack[playerCount], deltaTime);
    player[playerCount]->currSpeed = 0;
    player[playerCount]->projectile.pos.v[0] += player[playerCount]->projectile.dir.v[0] * player[playerCount]->projectile.speed * fixedTime;
    player[playerCount]->projectile.pos.v[1] += player[playerCount]->projectile.dir.v[1] * player[playerCount]->projectile.speed * fixedTime;
    player[playerCount]->projectile.pos.v[2] += player[playerCount]->projectile.dir.v[2] * player[playerCount]->projectile.speed * fixedTime;

    // Calculate the distance traveled by the projectile from its origin
    float distanceTraveled = t3d_vec3_distance(&player[playerCount]->projectile.pos, &player[playerCount]->hitbox.center);

    // Define the maximum distance the projectile can travel
    float EndPosMax = player[playerCount]->projectile.length;

    // Reverse direction if the maximum distance is reached
    if (distanceTraveled >= EndPosMax) {
      player[playerCount]->projectile.speed = 120.0f;
      player[playerCount]->projectile.dir.v[0] = -player[playerCount]->projectile.dir.v[0];
      player[playerCount]->projectile.dir.v[1] = -player[playerCount]->projectile.dir.v[1];
      player[playerCount]->projectile.dir.v[2] = -player[playerCount]->projectile.dir.v[2];
    }

    // Calculate the end position based on the projectiles's direction and length
    T3DVec3 EndPos;
    EndPos.v[0] = player[playerCount]->projectile.pos.v[0] + player[playerCount]->projectile.dir.v[0] * player[playerCount]->projectile.length;
    EndPos.v[1] = player[playerCount]->projectile.pos.v[1] + player[playerCount]->projectile.dir.v[1] * player[playerCount]->projectile.length;
    EndPos.v[2] = player[playerCount]->projectile.pos.v[2] + player[playerCount]->projectile.dir.v[2] * player[playerCount]->projectile.length;
    t3d_vec3_norm(&EndPos);
    


    // Scale hitbox up and down according to position
    if (distanceTraveled <= EndPosMax) { 
      player[playerCount]->projectile.hitbox.center = player[playerCount]->projectile.pos;
      if(numPlayers > 3){
        player[playerCount]->projectile.hitbox.radius += 2.5f;
      } else {
        player[playerCount]->projectile.hitbox.radius += 1.5f;
      }

      if(player[playerCount]->projectile.hitbox.radius > 20.0f){
        player[playerCount]->projectile.hitbox.radius = 20.0f;
      }
    }

    check_attack_collisions(crates, numCrates, playerCount);
    check_attack_collisions(balls, numBalls, playerCount);

    if(!animAttack[playerCount].isPlaying){
      player[playerCount]->projectile.hitbox.center = player[playerCount]->hitbox.center;
      player[playerCount]->projectile.speed = 0.0f;
      player[playerCount]->projectile.isActive = false;
      if (player[playerCount]->isGrounded == true) {
        playerState[playerCount] = PLAYER_WALK;
      } else {
        airAttackCount++;
        playerState[playerCount] = PLAYER_FALL;
      }
    }
  }

  //reset projectile
  if(player[playerCount]->projectile.speed == 0.0f){
    update_player_forward(&player[playerCount]->forward, player[playerCount]->rot.v[1]);
    player[playerCount]->projectile.pos = player[playerCount]->hitbox.center;
    player[playerCount]->projectile.dir = player[playerCount]->forward;
    player[playerCount]->projectile.hitbox.center =  player[playerCount]->projectile.pos;
    player[playerCount]->projectile.hitbox.radius = 8.0f;
  }
}

void player_idle_walk(int playerCount){

  // use blend based on speed for smooth transitions
  player[playerCount]->animBlend = player[playerCount]->currSpeed / 0.51f;
  if(player[playerCount]->animBlend > 1.0f)player[playerCount]->animBlend = 1.0f;

  // Update the animation and modify the skeleton, this will however NOT recalculate the matrices
  t3d_anim_update(&animIdle[playerCount], deltaTime);
  if (playerState[playerCount] == PLAYER_IDLE || playerState[playerCount] == PLAYER_WALK){
    t3d_anim_set_speed(&animWalk[playerCount], player[playerCount]->animBlend);
    t3d_anim_update(&animWalk[playerCount], deltaTime);
  }
  
  // do walk
  if(player[playerCount]->isGrounded && player[playerCount]->currSpeed > 0.1f){
    if(playerState[playerCount] != PLAYER_JUMP_START 
      && playerState[playerCount] != PLAYER_JUMP 
      && playerState[playerCount] != PLAYER_FALL 
      && playerState[playerCount] != PLAYER_SLIDE
      && playerState[playerCount] != PLAYER_ATTACK_START 
      && playerState[playerCount] != PLAYER_ATTACK) {

      playerState[playerCount] = PLAYER_WALK;
    }
  }


}

void player_fall(int playerCount){
  // do fall
  if(playerState[playerCount] == PLAYER_FALL) {
    t3d_anim_update(&animFall[playerCount], deltaTime);

    if(numPlayers > 1){
      check_player_collisions(player, numPlayers);
    }

    player_surface_collider(playerCount);
  
    check_actor_collisions(balls, numBalls, playerCount);
    check_midair_actor_collisions(crates, numCrates, playerCount);

    if(!player[playerCount]->isGrounded){
      if (player[playerCount]->pos.v[1] > groundLevel) {
        player[playerCount]->vel.v[1] = t3d_lerp(player[playerCount]->vel.v[1], GRAVITY, fallFixedTime);
        player[playerCount]->pos.v[1] = t3d_lerp(player[playerCount]->pos.v[1],player[playerCount]->vel.v[1], fallFixedTime);
        player[playerCount]->hitbox.center.v[1] = t3d_lerp(player[playerCount]->hitbox.center.v[1],player[playerCount]->pos.v[1], fallFixedTime);
        player[playerCount]->scale.v[1] -= 0.02f;
        if(player[playerCount]->scale.v[1] < 0.3f){
          player[playerCount]->scale.v[1] = 0.3f;
        }

      } else if (player[playerCount]->pos.v[1] <= groundLevel) {
        player[playerCount]->pos = playerStartPos;
        player[playerCount]->vel.v[1] = 0.0f;
        player[playerCount]->scale.v[1] = 1.0f;
        if(numPlayers > 2){
          player[playerCount]->jumpForce = player[playerCount]->pos.v[1] + 450.0f;
        } else {
          player[playerCount]->jumpForce = player[playerCount]->pos.v[1] + 400.0f;
        }
      }
    }
  }
}

void player_land(int playerCount){
  // do land
  if(playerState[playerCount] == PLAYER_LAND){
    if(player[playerCount]->hitbox.center.v[1] < player[playerCount]->hitbox.radius){
      player[playerCount]->hitbox.center.v[1] = player[playerCount]->hitbox.radius*2.0f;
    }
    player[playerCount]->scale.v[1] = 1.0f;
    if(player[playerCount]->currSpeed > 0.5f){
      player[playerCount]->currSpeed = 0.5f;
    }
    playerState[playerCount] = PLAYER_IDLE;
  }

}


void player_slide(int playerCount){
  // do slide/slope interaction
  if(playerState[playerCount] == PLAYER_SLIDE){
    player[playerCount]->scale.v[1] = 1.0f;
    player[playerCount]->cam.camPos.v[1] = player[playerCount]->hitbox.center.v[1];
    player[playerCount]->cam.camTarget.v[1] = player[playerCount]->hitbox.center.v[1];
    playerState[playerCount] = PLAYER_WALK;
  
  }
}

// Handles OOB and the outcome of not landing on a box, but latter is mostly spaghetti
void w_t_f(int playerCount){

  if(player[playerCount]->isGrounded) {
    if (player[playerCount]->pos.v[1] < groundLevel) {
      player[playerCount]->pos = playerStartPos;
    }
    
    if(player[playerCount]->pos.v[1] > groundLevel){
      Surface currSlope = find_closest_surface(player[playerCount]->hitbox.center, testLevelSlope, testLevelSlopeCount);
      if (!check_sphere_surface_collision(player[playerCount]->hitbox, currSlope)){
        Surface currFloor = find_closest_surface(player[playerCount]->hitbox.center, testLevelFloor, testLevelFloorCount);
        if (!check_sphere_surface_collision(player[playerCount]->hitbox, currFloor)){
          for (int c = 0; c < numCrates; ++c) {
            int closestCrate = find_closest(player[playerCount]->pos, crates, numCrates);
            if(!check_sphere_box_collision(player[playerCount]->hitbox, crates[closestCrate]->hitbox.shape.aabb)){
              // Check if the player is outside bounds in the x and z directions
              if (player[playerCount]->hitbox.center.v[0] >= crates[closestCrate]->hitbox.shape.aabb.max.v[0] ||
                  player[playerCount]->hitbox.center.v[0] <= crates[closestCrate]->hitbox.shape.aabb.min.v[0] ||
                  player[playerCount]->hitbox.center.v[2] >= crates[closestCrate]->hitbox.shape.aabb.max.v[2] ||
                  player[playerCount]->hitbox.center.v[2] <= crates[closestCrate]->hitbox.shape.aabb.min.v[2]) {

                playerState[playerCount] = PLAYER_FALL;
              }
            } else {
              if (player[playerCount]->pos.v[1] < crates[closestCrate]->hitbox.shape.aabb.max.v[1]) {
                playerState[playerCount] = PLAYER_FALL;
              }
            }
          }
        }
      }
    }
  }
}

/* Handles rotating player's pitch around slopes
 Logic for roll is here, but not working ATM */
void update_player_rotations(int playerCount){

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
  
  if(!player[playerCount]->isGrounded){
    player[playerCount]->rot.v[0] = t3d_lerp_angle(player[playerCount]->rot.v[0], 0, 0.6f);
    //player[playerCount]->rot.v[2] = t3d_lerp_angle(player[playerCount]->rot.v[2], 0, 0.6f);
  } else {
    player[playerCount]->rot.v[0] = t3d_lerp_angle(player[playerCount]->rot.v[0], pitch, 0.2f);
    //player[playerCount]->rot.v[2] = t3d_lerp_angle(player[playerCount]->rot.v[2], roll, 0.1f);
  }
}

// Handles shadow raycasting and applying player rotations
void update_player_shadow(int playerCount){
  // update shadow
  player[playerCount]->shadowPos.v[0] = player[playerCount]->pos.v[0];
  player[playerCount]->shadowPos.v[2] = player[playerCount]->pos.v[2];

  Surface nextFloor = find_closest_surface(player[playerCount]->hitbox.center, testLevelFloor, testLevelFloorCount);
  Surface nextSlope = find_closest_surface(player[playerCount]->hitbox.center, testLevelSlope, testLevelSlopeCount);
  
  float dist_player_next_floor = distance_to_surface(player[playerCount]->hitbox.center, nextFloor);
  float dist_player_next_slope = distance_to_surface(player[playerCount]->hitbox.center, nextSlope);
  bool shadowOnSlope = false;

  if (dist_player_next_slope < dist_player_next_floor){
    shadowOnSlope = true;
  } else {
    shadowOnSlope = false;
  }

  if(!player[playerCount]->isGrounded){
    Surface rayFloor = closest_surface_below_raycast(player[playerCount]->pos, testLevelFloor, testLevelFloorCount);
    if(shadowOnSlope){
      if(dist_player_next_slope > player[playerCount]->hitbox.radius*2.0f){    
        player[playerCount]->shadowPos.v[1] = t3d_lerp(player[playerCount]->shadowPos.v[1], intersectionY, 0.8f);
      } else { 
        player[playerCount]->shadowPos.v[1] = intersectionY;
      }
    } else {
      if(dist_player_next_floor > player[playerCount]->hitbox.radius*1.5f){
        player[playerCount]->shadowPos.v[1] = t3d_lerp(player[playerCount]->shadowPos.v[1], rayFloor.center.v[1], 0.8f);
      } else {
        player[playerCount]->shadowPos.v[1] = nextFloor.center.v[1];
      }
    }
  } else {
    player[playerCount]->shadowRot = player[playerCount]->rot;
    player[playerCount]->shadowPos.v[1] = player[playerCount]->pos.v[1];
  }
}

void player_ground_collider(int playerCount){

  if(numPlayers > 1){
    check_player_collisions(player, numPlayers);
  };

  player_surface_collider(playerCount);

  check_actor_collisions(balls, numBalls, playerCount);
  check_actor_collisions(crates, numCrates, playerCount);

}

void player_air_collider(int playerCount){

  if(numPlayers > 1){
    check_player_collisions(player, numPlayers);
  }

  player_surface_collider(playerCount);
  
  check_actor_collisions(balls, numBalls, playerCount);
  check_midair_actor_collisions(crates, numCrates, playerCount);

}

void player_update(void){

  for (int i = 0; i < numPlayers; ++i) {

    update_movement(i);
    update_player_rotations(i);
    player_idle_walk(i);
    
    player_jump(i);
    player_attack(i);

    player_surface_collider(i);
    player_slide(i);

    player_fall(i);
    player_land(i);
    w_t_f(i);

    if(numPlayers <= 2){
      update_player_shadow(i);
    }

    // isGrounded collision sanity check
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

    if(player[i]->isGrounded){
      player_ground_collider(i);
    } else {
      player_air_collider(i);
    }


  }

}