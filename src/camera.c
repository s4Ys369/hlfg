#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>
#include "../include/types.h"
#include "camera.h"
#include "collision.h"
#include "input.h"
#include "map.h"
#include "player.h"
#include "utils.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

T3DViewport viewport;
T3DVec3 camPos;
T3DVec3 camTarget;
T3DVec3 camForward;
T3DVec3 camRight;
T3DVec3Pair camResults;
float camYaw;
int cam_mode;

void cam_init(void){
  viewport = t3d_viewport_create();
  camPos = (T3DVec3){{0, 45.0f, 80.0f}};
  camTarget = (T3DVec3){{0, 0,-10}};
  camForward = (T3DVec3){{0, 0, 0}};
  camRight = (T3DVec3){{0, 0, 0}};
  camYaw = 0.0f;
  cam_mode = 1;
}


// Function to rotate a vector around another vector (camTarget)
void rotate_camPos_around_camTarget(T3DVec3 *camPos, T3DVec3 camTarget, float angle, char axis) {
  // Step 1: Translate camPos to the origin relative to camTarget
  T3DVec3 translatedPos = {{
      camPos->v[0] - camTarget.v[0],
      camPos->v[1] - camTarget.v[1],
      camPos->v[2] - camTarget.v[2]
  }};

  // Step 2: Apply the rotation
  T3DVec3 rotatedPos;
  float rad = angle * M_PI / 180.0; // Convert angle to radians

  if (axis == 'x') {
      // Rotate around x-axis
      rotatedPos.v[0] = translatedPos.v[0];
      rotatedPos.v[1] = translatedPos.v[1] * cosf(rad) - translatedPos.v[2] * sinf(rad);
      rotatedPos.v[2] = translatedPos.v[1] * sinf(rad) + translatedPos.v[2] * cosf(rad);
  } else if (axis == 'y') {
      // Rotate around y-axis
      rotatedPos.v[0] = translatedPos.v[0] * cosf(rad) + translatedPos.v[2] * sinf(rad);
      rotatedPos.v[1] = translatedPos.v[1];
      rotatedPos.v[2] = -translatedPos.v[0] * sinf(rad) + translatedPos.v[2] * cosf(rad);
  } else if (axis == 'z') {
      // Rotate around z-axis
      rotatedPos.v[0] = translatedPos.v[0] * cosf(rad) - translatedPos.v[1] * sinf(rad);
      rotatedPos.v[1] = translatedPos.v[0] * sinf(rad) + translatedPos.v[1] * cosf(rad);
      rotatedPos.v[2] = translatedPos.v[2];
  } else {
      // Invalid axis
      return;
  }

  // Step 3: Translate the rotated position back
  camPos->v[0] = rotatedPos.v[0] + camTarget.v[0];
  camPos->v[1] = rotatedPos.v[1] + camTarget.v[1];
  camPos->v[2] = rotatedPos.v[2] + camTarget.v[2];
}

T3DVec3Pair get_cam_forward(T3DVec3 camTarget, T3DVec3 camPos, T3DVec3 *camForward, T3DVec3 *camRight){
  // Calculate the forward vector
  camForward->v[0] = camPos.v[0] - camTarget.v[0];
  camForward->v[1] = 0;
  camForward->v[2] = camPos.v[2] - camTarget.v[2];
  t3d_vec3_norm(camForward);

  // Calculate the right vector (make sure it points correctly)
  camRight->v[0] = camForward->v[2];
  camRight->v[1] = 0;
  camRight->v[2] = -camForward->v[0];
  t3d_vec3_norm(camRight);

  T3DVec3Pair result;
  result.forward = *camForward;
  result.right = *camRight;
  return result;
}

void cam_recenter(T3DVec3 *camTarget, T3DVec3 *camPos, T3DVec3 camForward, T3DVec3 *playerPos, T3DVec3 playerForward, float *camYaw){

  *camYaw = atan2f(playerForward.v[0], playerForward.v[2]);
  camForward.v[0] = sinf(*camYaw);
  camForward.v[1] = 0.0f;
  camForward.v[2] = cosf(*camYaw);

  camPos->v[0] = playerPos->v[0] - camForward.v[0] * 50.0f;
  camPos->v[1] = playerPos->v[1] + 30.0f;
  camPos->v[2] = playerPos->v[2] - camForward.v[2] * 50.0f;

  // Set camera target to be the player position
  *camTarget = *playerPos;
}

void top_down_view(T3DVec3 *camTarget, T3DVec3 *camPos, T3DVec3 camForward, T3DVec3 *playerPos){
  camPos->v[0] = playerPos->v[0] + camForward.v[0] * 5.0f;
  camPos->v[1] = playerPos->v[1] + 100.0f; // 100.0f is the height of the camera
  camPos->v[2] = playerPos->v[2];

  // Set camera target to be the player position
  *camTarget = *playerPos;
}

// Function to update the player's forward vector based on the yaw angle
void update_player_forward(T3DVec3 *playerForward, float playerYaw) {
  playerForward->v[0] = sinf(playerYaw);
  playerForward->v[1] = 0.0f;
  playerForward->v[2] = cosf(playerYaw);

  // Normalize the forward vector
  t3d_vec3_norm(playerForward);
}

// Function to follow the player with the camera with lagging rotation
void cam_follow_player_lag(T3DVec3 *camTarget, T3DVec3 *camPos, T3DVec3 *playerPos, float playerYaw, float *camYaw, float lagFactor) {
  // Interpolate the camera yaw towards the player yaw
  *camYaw = t3d_lerp_angle(*camYaw, playerYaw, lagFactor);

  // Calculate the camera's forward vector based on the interpolated yaw
  camForward.v[0] = sinf(*camYaw);
  camForward.v[1] = 0.0f;
  camForward.v[2] = cosf(*camYaw);

  // Set the camera position based on the player's position and the forward vector
  camPos->v[0] = playerPos->v[0] - camForward.v[0] * 50.0f; // 50.0f is the distance behind the player
  camPos->v[1] = playerPos->v[1] + 30.0f; // 30.0f is the height of the camera
  camPos->v[2] = playerPos->v[2] - camForward.v[2] * 50.0f;

  // Set the camera target to be the player position
  *camTarget = *playerPos;
}

void cam_update(void){
  camResults = get_cam_forward(camTarget, camPos, &camForward, &camRight);
  camTarget = playerPos;
  float angle = 90.0f;
  char axis;
    
  if(btn.z) {
    cam_mode = 0;
  }
  if(btn.c_down) {
    cam_mode = 1;
  }
  if(btn.c_left) {
    axis = 'y';
    cam_mode = 2;
    rotate_camPos_around_camTarget(&camPos, camTarget, -angle, axis);
  }
  if(btn.c_right) {
    axis = 'y';
    cam_mode = 2;
    rotate_camPos_around_camTarget(&camPos, camTarget, angle, axis);
  }
  if(btn.c_up) {
    cam_mode = 3;
  }

  switch (cam_mode) {
    case 0:
      update_player_forward(&playerForward, rotY);
      cam_recenter(&camTarget, &camPos, (T3DVec3)(camForward), &playerPos, playerForward, &camYaw);
      cam_mode = 1;
    case 1:
      update_player_forward(&playerForward, rotY);
      cam_follow_player_lag(&camTarget, &camPos, &playerPos, rotY, &camYaw, 0.02f);
      break;
    case 3:
      update_player_forward(&playerForward, rotY);
      top_down_view(&camTarget, &camPos, (T3DVec3)(camResults.forward), &playerPos);
      break;
  }

  resolve_box_collision(MapBox, &camPos);

  t3d_viewport_set_projection(&viewport, T3D_DEG_TO_RAD(85.0f), 10.0f, 150.0f);
  t3d_viewport_look_at(&viewport, &camPos, &camTarget, &(T3DVec3){{0,1,0}});
}