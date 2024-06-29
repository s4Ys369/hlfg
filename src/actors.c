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
float ballVelY[MAX_BALLS];
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
    crates[i]->hitbox.shape.type = SHAPE_BOX;
    crates[i]->hitbox.shape.aabb = (AABB){{{crates[i]->pos.v[0] - 32.0f, crates[i]->pos.v[1], crates[i]->pos.v[2] - 32.0f}},
                                         {{crates[i]->pos.v[0] + 32.0f, crates[i]->pos.v[1] + 64.0f, crates[i]->pos.v[2] + 32.0f}}};
    crates[i]->isSafe = false;
    crates[i]->IsBouncy = true;

    // Create gfx call to draw crate
    rspq_block_begin();
      t3d_matrix_push(crateMatFP[i]);
      rdpq_set_prim_color(YELLOW);
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
    balls[i]->hitbox.shape.type = SHAPE_SPHERE;
    balls[i]->hitbox.shape.sphere.center = balls[i]->pos;
    balls[i]->hitbox.shape.sphere.radius = 16.0f;
    balls[i]->IsBouncy = true;

    ballBounced[i] = false;
    ballVelY[i] = 0.0f;
    ballBounceForce[i] = 150.0f;

    // Create gfx call to draw crate
    rspq_block_begin();
      t3d_matrix_push(ballMatFP[i]);
      rdpq_set_prim_color(ORANGE);
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

// Bouncing simulation
void balls_update(void){
  float bounceModifier = 0.8f; // Simulates energy loss
  float maxBounceHeight = 100.0f;

  for (int b = 0; b <= numBalls; ++b) {

    // Apply gravity every frame
    ballVelY[b] += GRAVITY * jumpTime;

    
    // Check for the ball is on or below floor
    if (balls[b]->hitbox.shape.sphere.center.v[1] <= FloorBox.max.v[1] + balls[b]->hitbox.shape.sphere.radius) {

      
      // If so set the ball to bouncing state
      ballBounced[b] = true;

      // Make sure the ball doesn't get stuck in the ground
      balls[b]->hitbox.shape.sphere.center.v[1] = FloorBox.max.v[1] + balls[b]->hitbox.shape.sphere.radius;
      
      // Apply the bounce to Y velocity
      ballBounceForce[b] = ballBounceForce[b] * bounceModifier;
      ballVelY[b] = ballBounceForce[b];

    } else {
      ballBounced[b] = false;
    }

    // Update hitbox, then position
    balls[b]->hitbox.shape.sphere.center.v[1] += ballVelY[b] * jumpTime;
    if (balls[b]->hitbox.shape.sphere.center.v[1] >= maxBounceHeight){
      ballBounced[b] = false;
    }
    balls[b]->pos = balls[b]->hitbox.shape.sphere.center;
    if (balls[b]->pos.v[1] < FloorBox.max.v[1] + balls[b]->hitbox.shape.sphere.radius) {
      balls[b]->pos.v[1] = FloorBox.max.v[1] + balls[b]->hitbox.shape.sphere.radius;
    }

    // Resolve all other collisions
    resolve_actor_to_actor_col(balls[b], balls, numBalls, b);
    resolve_actor_to_actor_col(balls[b], crates, numCrates, b);


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
    resolve_actor_to_actor_col(crates[c], balls, numBalls, c);

    crates[c]->hitbox.shape.aabb = (AABB){{{crates[c]->pos.v[0] - 32.0f, crates[c]->pos.v[1], crates[c]->pos.v[2] - 32.0f}},
                                         {{crates[c]->pos.v[0] + 32.0f, crates[c]->pos.v[1] + 64.0f, crates[c]->pos.v[2] + 32.0f}}};
  }

}


void actors_update(void){
  balls_update();
  crates_update();
}

