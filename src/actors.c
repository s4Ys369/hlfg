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
#include "sound.h"
#include "utils.h"

// Crates
T3DMat4FP* crateMatFP[MAX_CRATES];
rspq_block_t *dplCrate[MAX_CRATES];
T3DModel *modelCrate;
Actor *crates[MAX_CRATES];
int numCrates;

// Balls
T3DMat4FP* ballMatFP[MAX_BALLS];
rspq_block_t *dplBall[MAX_BALLS];
T3DModel *modelBall;
Actor *balls[MAX_BALLS];
int numBalls;
bool ballBounced[MAX_BALLS];
float ballBounceForce[MAX_BALLS];

void check_ball_collisions(Actor *balls[], int numBalls) {
  for (int i = 0; i < numBalls; i++) {
    for (int j = i + 1; j < numBalls; j++) {
      if (check_sphere_collision(balls[i]->hitbox.shape.sphere, balls[j]->hitbox.shape.sphere)) {
        resolve_sphere_collision(balls[i]->hitbox.shape.sphere, &balls[j]->hitbox.shape.sphere.center);
        resolve_sphere_collision(balls[j]->hitbox.shape.sphere, &balls[i]->hitbox.shape.sphere.center);
        balls[i]->vel.v[0] = -balls[i]->vel.v[0];
        balls[i]->vel.v[2] = -balls[i]->vel.v[2];
        balls[j]->vel.v[0] = -balls[j]->vel.v[0];
        balls[j]->vel.v[2] = -balls[j]->vel.v[2];
      }
    }
  } 
}
void check_crates_collisions(Actor *crates[], int numCrates) {

  for (int i = 0; i < numCrates; i++) {
    for (int j = i + 1; j < numCrates; j++) {
      if (check_box_collision(crates[i]->hitbox.shape.aabb, crates[j]->hitbox.shape.aabb)) {
        resolve_box_collision_offset_xz(crates[j]->hitbox.shape.aabb, &crates[i]->pos, .2f);
        if(crates[j]->IsBouncy == true) {
          crates[j]->pos.v[0] += crates[i]->pos.v[0]  * fixedTime;
          crates[j]->pos.v[2] += crates[i]->pos.v[2] * fixedTime;
        }
      }
    }
  } 
}

void check_ball_crate_collisions(Actor *balls[], int numBalls, Actor *crates[], int numCrates){
  for (int i = 0; i < numBalls; i++) {
    for (int j = 0; j < numCrates; j++) {
      if (check_sphere_box_collision(balls[i]->hitbox.shape.sphere, crates[j]->hitbox.shape.aabb)) {
        resolve_box_collision_offset(crates[j]->hitbox.shape.aabb, &balls[i]->hitbox.shape.sphere.center, 0.2f);
        balls[i]->vel.v[0] = -balls[i]->vel.v[0];
        balls[i]->vel.v[2] = -balls[i]->vel.v[2];
        resolve_sphere_collision_xz(balls[i]->hitbox.shape.sphere, &crates[j]->pos);
      }
    }
  } 
}

/* Handles all actor to actor collisions
void resolve_actor_to_actor_col(Actor *origin, Actor **target, int targetCount, int originCount){

  // Set the closet actor to current actor 
  Actor *currActor;
  int closestActor = find_closest(origin->pos, target, targetCount);

  if (closestActor != -1 && closestActor != originCount){
    currActor = target[closestActor];

    if(origin[originCount].hitbox.shape.type == SHAPE_SPHERE) {
      // Handles if actor has a AABB hitbox
      if(currActor->hitbox.shape.type == SHAPE_BOX){
        check_ball_crate_collisions(origin, originCount, currActor, closestActor);
      }

      // Handles if actor has a Sphere hitbox
      if(currActor->hitbox.shape.type == SHAPE_SPHERE){
        if (check_sphere_collision(origin[originCount].hitbox.shape.sphere, currActor->hitbox.shape.sphere)) {

          resolve_sphere_collision(currActor->hitbox.shape.sphere, &origin[originCount].hitbox.shape.sphere.center);

          // If the actor is movable ie. bouncy, actor pushes actor
          if(currActor->IsBouncy == true){
            resolve_sphere_collision(origin[originCount].hitbox.shape.sphere, &currActor->hitbox.shape.sphere.center);
          }
        }
      }

      // More to be added
    }

    if(origin[originCount].hitbox.shape.type == SHAPE_BOX) {
      // Handles if actor has a AABB hitbox
      if(currActor->hitbox.shape.type == SHAPE_BOX){
        if (check_box_collision(origin[originCount].hitbox.shape.aabb, currActor->hitbox.shape.aabb)) {

          resolve_box_collision(currActor->hitbox.shape.aabb, &origin[originCount].pos, 0.02f);

          // If the actor is movable ie. bouncy, actor pushes actor
          if(currActor->IsBouncy == true){
            resolve_box_collision(origin[originCount].hitbox.shape.aabb, &currActor->pos, 0.02f);
          }
        }
      }

      // Handles if actor has a Sphere hitbox
      if(currActor->hitbox.shape.type == SHAPE_SPHERE){
        if (check_sphere_box_collision(currActor->hitbox.shape.sphere, origin[originCount].hitbox.shape.aabb)) {

          resolve_sphere_collision(currActor->hitbox.shape.sphere, &origin[originCount].pos);

          // If the actor is movable ie. bouncy, actor pushes actor
          if(currActor->IsBouncy == true){
            resolve_sphere_collision(origin[originCount].hitbox.shape.sphere, &currActor->pos);
          }
        }
      }

      // More to be added
    }

  }
}
*/

// Initialize crates
void crates_init(void){
  numCrates = (int)(random_float(1.0f,MAX_CRATES));

  for (int i = 0; i <= numCrates; ++i) {
    crateMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));

    float X = random_float(-400.0f, 400.0f);
    float Z = random_float(-400.0f, 400.0f);

    crates[i] = malloc(sizeof(Actor));

    crates[i]->pos = (T3DVec3){{X, groundLevel, Z}};
    crates[i]->moveDir = (T3DVec3){{0, 0, 0}};
    crates[i]->forward = (T3DVec3){{0, 0, 1}};
    crates[i]->vel = (T3DVec3){{0, 0, 0}};
    crates[i]->rot = (T3DVec3){{0, 0, 0}};
    crates[i]->hitbox.shape.type = SHAPE_BOX;
    crates[i]->hitbox.shape.aabb = (AABB){{{crates[i]->pos.v[0] - 32.0f, crates[i]->pos.v[1], crates[i]->pos.v[2] - 32.0f}},
                                         {{crates[i]->pos.v[0] + 32.0f, crates[i]->pos.v[1] + 64.0f, crates[i]->pos.v[2] + 32.0f}}};
    crates[i]->isSafe = RANDN(2);
    crates[i]->IsBouncy = RANDN(2);

    // Create gfx call to draw crate
    rspq_block_begin();
      t3d_matrix_push_pos(1);
      matCount++;
      t3d_matrix_set(crateMatFP[i], true);
      rdpq_set_prim_color(YELLOW);
      t3d_matrix_set(crateMatFP[i], true);
      t3d_model_draw(modelCrate);
      t3d_matrix_pop(1);
    dplCrate[i] = rspq_block_end();
    
  }

}

// Initialize crates
void balls_init(void){
  numBalls = (int)(random_float(1.0f,MAX_BALLS));

  for (int i = 0; i <= numBalls; ++i) {
   ballMatFP[i] = malloc_uncached(sizeof(T3DMat4FP));

    float X = random_float(-400.0f, 400.0f);
    float Z = random_float(-400.0f, 400.0f);

    balls[i] = malloc(sizeof(Actor));

    balls[i]->pos = (T3DVec3){{X, 32.0f, Z}};
    balls[i]->moveDir = (T3DVec3){{0, 0, 0}};
    balls[i]->forward = (T3DVec3){{0, 0, 1}};
    balls[i]->vel = (T3DVec3){{0, 0, 0}};
    balls[i]->rot = (T3DVec3){{0, 0, 0}};
    balls[i]->hitbox.shape.type = SHAPE_SPHERE;
    balls[i]->hitbox.shape.sphere.center = balls[i]->pos;
    balls[i]->hitbox.shape.sphere.radius = 16.0f;
    balls[i]->IsBouncy = true;

    ballBounced[i] = false;
    ballBounceForce[i] = 150.0f;

    // Create gfx call to draw crate
    rspq_block_begin();
      t3d_matrix_push_pos(1);
      matCount++;
      t3d_matrix_set(ballMatFP[i], true);
      rdpq_set_prim_color(ORANGE);
      t3d_matrix_set(ballMatFP[i], true);
      t3d_model_draw(modelBall);
      t3d_matrix_pop(1);
    dplBall[i] = rspq_block_end();

  }
}

void actors_init(void){

  modelCrate = t3d_model_load("rom:/box.t3dm");
  crates_init();
  modelBall = t3d_model_load("rom:/sphere.t3dm");
  balls_init();

  // Check and resolve collisions for each actor
  for (int c = 0; c <= numCrates; ++c) {
    if (check_box_collision(crates[c]->hitbox.shape.aabb, FloorBox)) {
      resolve_box_collision_offset(FloorBox, &crates[c]->pos, 1.0f);
    }
    check_crates_collisions(crates, numCrates);
    crates[c]->hitbox.shape.aabb = (AABB){{{crates[c]->pos.v[0] - 32.0f, crates[c]->pos.v[1], crates[c]->pos.v[2] - 32.0f}},
                                         {{crates[c]->pos.v[0] + 32.0f, crates[c]->pos.v[1] + 64.0f, crates[c]->pos.v[2] + 32.0f}}};
  }

  for (int b = 0; b <= numBalls; ++b) {
    if (check_sphere_box_collision(balls[b]->hitbox.shape.sphere, FloorBox)) {
      resolve_box_collision_offset(FloorBox, &balls[b]->hitbox.shape.sphere.center, balls[b]->hitbox.shape.sphere.radius);
    }
    check_ball_collisions(balls, numBalls);
    balls[b]->pos = balls[b]->hitbox.shape.sphere.center;
  }

  check_ball_crate_collisions(balls, numBalls, crates, numCrates);

}


float dist = 0;
float minDist = 0;

// Bouncing simulation
void balls_update(void){
  float bounceModifier = 0.8f; // Simulates energy loss
  float maxBounceHeight = 100.0f;
  float playerBumpForce = 32.0f;
  float friction = 0.9f;
  float newPitch = 0.0f;
  float newYaw = 0.0f;
  float newRoll = 0.0f;

  for (int b = 0; b <= numBalls; ++b) {

    // Apply gravity every frame
    balls[b]->vel.v[1] += GRAVITY * jumpTime;

    
    // Check for the ball is on or below floor
    if (balls[b]->hitbox.shape.sphere.center.v[1] <= FloorBox.max.v[1] + balls[b]->hitbox.shape.sphere.radius) {

      
      // If so set the ball to bouncing state
      ballBounced[b] = true;

      // Make sure the ball doesn't get stuck in the ground
      balls[b]->hitbox.shape.sphere.center.v[1] = FloorBox.max.v[1] + balls[b]->hitbox.shape.sphere.radius;
      

    } else {
      ballBounced[b] = false;
    }

    if(ballBounced[b]){
      // Apply the bounce to Y velocity
      ballBounceForce[b] = ballBounceForce[b] * bounceModifier;
      balls[b]->vel.v[1] = ballBounceForce[b];
    } 

    // Update hitbox, then position
    if (balls[b]->hitbox.shape.sphere.center.v[1] >= maxBounceHeight){
      ballBounced[b] = false;
    }
    
    if (balls[b]->pos.v[1] < FloorBox.max.v[1] + balls[b]->hitbox.shape.sphere.radius) {
      balls[b]->pos.v[1] = FloorBox.max.v[1] + balls[b]->hitbox.shape.sphere.radius;
    }

    // Resolve all other collisions
    check_ball_collisions(balls, numBalls);

    // Check for the ball colliding with the player
    if(check_sphere_collision(balls[b]->hitbox.shape.sphere, player[0]->hitbox)){
      // Add player's current forward to the ball
      balls[b]->vel.v[0] += player[0]->forward.v[0] * player[0]->currSpeed;
      balls[b]->vel.v[2] += player[0]->forward.v[2] * player[0]->currSpeed;

      // then bounce it
      if (balls[b]->vel.v[1] > 5.0f) {
        sound_bounce();
      }
      ballBounceForce[b] = playerBumpForce * player[0]->currSpeed;
      ballBounced[b] = true;

    // Check for the ball colliding with the player's prjectile
    } else if(check_sphere_collision(balls[b]->hitbox.shape.sphere, player[0]->projectile.hitbox)){
      // Add player's current forward to the ball, with a little something
      balls[b]->vel.v[0] += player[0]->forward.v[0] * playerBumpForce;
      balls[b]->vel.v[2] += player[0]->forward.v[2] * playerBumpForce;

      // then bounce it
      if (balls[b]->vel.v[1] > 5.0f) {
        sound_bounce();
      }
      ballBounceForce[b] = playerBumpForce;
      ballBounced[b] = true;

    } else {

      // else add friction to X and Z if grounded
      if (balls[b]->hitbox.shape.sphere.center.v[1] <= FloorBox.max.v[1] + balls[b]->hitbox.shape.sphere.radius) {
        if (balls[b]->vel.v[1] > 5.0f) {
          sound_bounce();
        }
        balls[b]->vel.v[0] *= friction;
        balls[b]->vel.v[2] *= friction;
      }
    }

    // Update position based on velocity
    balls[b]->hitbox.shape.sphere.center.v[0] += balls[b]->vel.v[0] * jumpTime;
    balls[b]->hitbox.shape.sphere.center.v[1] += balls[b]->vel.v[1] * jumpTime;
    balls[b]->hitbox.shape.sphere.center.v[2] += balls[b]->vel.v[2] * jumpTime;
    balls[b]->pos = balls[b]->hitbox.shape.sphere.center;

    // Limit position inside of bounds
    if(balls[b]->pos.v[0] < FloorBox.min.v[0]){
      balls[b]->pos.v[0] = FloorBox.min.v[0];
      balls[b]->vel.v[0] = -balls[b]->vel.v[0];
    }
    if(balls[b]->pos.v[0] >  FloorBox.max.v[0]){
      balls[b]->pos.v[0] = FloorBox.max.v[0];
      balls[b]->vel.v[0] = -balls[b]->vel.v[0];
    }
    if(balls[b]->pos.v[2] < FloorBox.min.v[2]){
      balls[b]->pos.v[2] = FloorBox.min.v[2];
      balls[b]->vel.v[2] = -balls[b]->vel.v[2];
    }
    if(balls[b]->pos.v[2] >  FloorBox.max.v[2]){
      balls[b]->pos.v[2] = FloorBox.max.v[2];
      balls[b]->vel.v[2] = -balls[b]->vel.v[2];
    }

    // Calculate new pitch (rotation around x-axis based on move direction)
    newPitch = atan2f(-balls[b]->vel.v[1], balls[b]->vel.v[2]); // Assuming vel.v[1] is y-axis velocity
    balls[b]->rot.v[0] = t3d_lerp_angle(balls[b]->rot.v[0], newPitch, 0.1f);

    // Calculate new yaw (rotation around y-axis based on move direction)
    newYaw = atan2f(-balls[b]->vel.v[0], balls[b]->vel.v[2]); // Assuming vel.v[0] is x-axis velocity
    balls[b]->rot.v[1] = t3d_lerp_angle(balls[b]->rot.v[1], newYaw, 0.1f);

    // Calculate new roll (rotation around z-axis based on move direction)
    newRoll = atan2f(-balls[b]->vel.v[0], balls[b]->vel.v[1]); // Assuming vel.v[0] is x-axis velocity
    balls[b]->rot.v[2] = t3d_lerp_angle(balls[b]->rot.v[2], newRoll, 0.1f);
  }

}


void crates_update(void){
  
  for (int c = 0; c <= numCrates; ++c) {

    crates[c]->pos.v[1] += GRAVITY * jumpTime;
    
    if (crates[c]->pos.v[1] < FloorBox.max.v[1] + crates[c]->hitbox.shape.aabb.min.v[1]) {
      crates[c]->pos.v[1] = FloorBox.max.v[1];
    }

    if(crates[c]->IsBouncy){
      check_crates_collisions(crates, numCrates);
    }
    // Limit position inside of bounds
    if(crates[c]->pos.v[0] < FloorBox.min.v[0]){
      crates[c]->pos.v[0] = FloorBox.min.v[0];
      crates[c]->vel.v[0] = -crates[c]->vel.v[0];
    }
    if(crates[c]->pos.v[0] >  FloorBox.max.v[0]){
      crates[c]->pos.v[0] = FloorBox.max.v[0];
      crates[c]->vel.v[0] = -crates[c]->vel.v[0];
    }
    if(crates[c]->pos.v[2] < FloorBox.min.v[2]){
      crates[c]->pos.v[2] = FloorBox.min.v[2];
      crates[c]->vel.v[2] = -crates[c]->vel.v[2];
    }
    if(crates[c]->pos.v[2] >  FloorBox.max.v[2]){
      crates[c]->pos.v[2] = FloorBox.max.v[2];
      crates[c]->vel.v[2] = -crates[c]->vel.v[2];
    }

    crates[c]->hitbox.shape.aabb = (AABB){{{crates[c]->pos.v[0] - 32.0f, crates[c]->pos.v[1], crates[c]->pos.v[2] - 32.0f}},
                                         {{crates[c]->pos.v[0] + 32.0f, crates[c]->pos.v[1] + 64.0f, crates[c]->pos.v[2] + 32.0f}}};
  }

}


void actors_update(void){
  balls_update();
  crates_update();
  check_ball_crate_collisions(balls, numBalls, crates, numCrates);
}

