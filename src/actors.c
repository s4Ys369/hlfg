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

// Handles all actor to actor collisions
void resolve_actor_to_actor_col(Actor *origin, Actor **target, int targetCount, int originCount){

  // Set the closet actor to current actor 
  Actor *currActor;
  int closestActor = find_closest(origin->pos, target, targetCount);

  if (closestActor != -1 && closestActor != originCount){
    currActor = target[closestActor];

    if(origin[originCount].hitbox.shape.type == SHAPE_SPHERE) {
      // Handles if actor has a AABB hitbox
      if(currActor->hitbox.shape.type == SHAPE_BOX){
        if (check_sphere_box_collision(origin[originCount].hitbox.shape.sphere, currActor->hitbox.shape.aabb)) {

          // Move model and hitbox separately to blend later
          resolve_box_collision(currActor->hitbox.shape.aabb, &origin[originCount].hitbox.shape.sphere.center, origin[originCount].hitbox.shape.sphere.radius);
          resolve_box_collision(currActor->hitbox.shape.aabb, &origin[originCount].pos, 0.02f);

          // If the actor is movable ie. bouncy, actor pushes actor
          if(currActor->IsBouncy == true){
            resolve_sphere_collision(origin[originCount].hitbox.shape.sphere, &currActor->pos);
          }
        }
      }

      // Handles if actor has a Sphere hitbox
      if(currActor->hitbox.shape.type == SHAPE_SPHERE){
        if (check_sphere_collision(origin[originCount].hitbox.shape.sphere, currActor->hitbox.shape.sphere)) {

          // Move model and hitbox separately to blend later
          resolve_sphere_collision(currActor->hitbox.shape.sphere, &origin[originCount].hitbox.shape.sphere.center);
          resolve_sphere_collision(currActor->hitbox.shape.sphere, &origin[originCount].pos);

          // If the actor is movable ie. bouncy, actor pushes actor
          if(currActor->IsBouncy == true){
            resolve_sphere_collision(origin[originCount].hitbox.shape.sphere, &currActor->pos);
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
    crates[i]->isSafe = false;
    crates[i]->IsBouncy = true;

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
      resolve_box_collision(FloorBox, &crates[c]->pos, 1.0f);
    }
    resolve_actor_to_actor_col(crates[c], balls, numBalls, c);
    resolve_actor_to_actor_col(crates[c], crates, numCrates, c);
    crates[c]->hitbox.shape.aabb = (AABB){{{crates[c]->pos.v[0] - 32.0f, crates[c]->pos.v[1], crates[c]->pos.v[2] - 32.0f}},
                                         {{crates[c]->pos.v[0] + 32.0f, crates[c]->pos.v[1] + 64.0f, crates[c]->pos.v[2] + 32.0f}}};
  }

  for (int b = 0; b <= numBalls; ++b) {
    if (check_sphere_box_collision(balls[b]->hitbox.shape.sphere, FloorBox)) {
      resolve_box_collision(FloorBox, &balls[b]->hitbox.shape.sphere.center, balls[b]->hitbox.shape.sphere.radius);
    }
    resolve_actor_to_actor_col(balls[b], balls, numBalls, b);
    resolve_actor_to_actor_col(balls[b], crates, numCrates, b);
    balls[b]->pos = balls[b]->hitbox.shape.sphere.center;
  }

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
    resolve_actor_to_actor_col(balls[b], balls, numBalls, b);
    resolve_actor_to_actor_col(balls[b], crates, numCrates, b);

    // Check for the ball colliding with the player
    if(check_sphere_collision(balls[b]->hitbox.shape.sphere, player[0]->hitbox)){
      // Add player's current forward to the ball
      balls[b]->vel.v[0] += player[0]->forward.v[0] * player[0]->currSpeed;
      balls[b]->vel.v[2] += player[0]->forward.v[2] * player[0]->currSpeed;

      // then bounce it
      ballBounceForce[b] = playerBumpForce * player[0]->currSpeed;
      ballBounced[b] = true;

    } else {

      // else add friction to X and Z if grounded
      if (balls[b]->hitbox.shape.sphere.center.v[1] <= FloorBox.max.v[1] + balls[b]->hitbox.shape.sphere.radius) {
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

    resolve_actor_to_actor_col(crates[c], crates, numCrates, c);

    // Checking this again causes a FPU error, to be fixed
    //resolve_actor_to_actor_col(crates[c], balls, numBalls, c);

    crates[c]->hitbox.shape.aabb = (AABB){{{crates[c]->pos.v[0] - 32.0f, crates[c]->pos.v[1], crates[c]->pos.v[2] - 32.0f}},
                                         {{crates[c]->pos.v[0] + 32.0f, crates[c]->pos.v[1] + 64.0f, crates[c]->pos.v[2] + 32.0f}}};
  }

}


void actors_update(void){
  balls_update();
  crates_update();
}

