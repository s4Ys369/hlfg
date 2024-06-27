#include <libdragon.h>
#include <t3d/t3d.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "camera.h"
#include "collision.h"
#include "input.h"
#include "map.h"
#include "player.h"
#include "utils.h"

T3DVec3 lightDirVec;
uint8_t colorAmbient[4] = {0x69, 0x64, 0x5D, 0xFF};
uint8_t colorDir[4] = {0xFF, 0xAA, 0xAA, 0xFF};

// Handles camera, light, and viewports 
void cam_init(void){

  // init light direction
  lightDirVec = (T3DVec3){{1.0f, 1.0f, 1.0f}};
  t3d_vec3_norm(&lightDirVec);

  // init player camera
  for (int i = 0; i < numPlayers; ++i) {
    player[i].cam.camPos = (T3DVec3){{0, 45.0f, 80.0f}};
    player[i].cam.camTarget = (T3DVec3){{0, 0,-10}};
    player[i].cam.camForward = (T3DVec3){{0, 0, 0}};
    player[i].cam.camRight = (T3DVec3){{0, 0, 0}};
    player[i].cam.camYaw = 0.0f;
    player[i].cam.cam_mode = 1;
  }

  // create viewports
  if (numPlayers > 1) {
    if (numPlayers == 2) {
      player[0].cam.viewport = t3d_viewport_create();
      player[1].cam.viewport = t3d_viewport_create();
      t3d_viewport_set_area(&player[0].cam.viewport, 0,             0,               SCREEN_WIDTH,   SCREEN_HEIGHT/2);
      t3d_viewport_set_area(&player[1].cam.viewport, 0,             SCREEN_HEIGHT/2, SCREEN_WIDTH,   SCREEN_HEIGHT/2);
    } else if (numPlayers == 3) {
      player[0].cam.viewport = t3d_viewport_create();
      player[1].cam.viewport = t3d_viewport_create();
      player[2].cam.viewport = t3d_viewport_create();
      t3d_viewport_set_area(&player[0].cam.viewport, 0,              0,               SCREEN_WIDTH,     SCREEN_HEIGHT/2);
      t3d_viewport_set_area(&player[1].cam.viewport, 0,              SCREEN_HEIGHT/2, SCREEN_WIDTH/2,   SCREEN_HEIGHT/2-2);
      t3d_viewport_set_area(&player[2].cam.viewport, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2-2, SCREEN_HEIGHT/2-2);
    } else if (numPlayers == 4) {
      player[0].cam.viewport = t3d_viewport_create();
      player[1].cam.viewport = t3d_viewport_create();
      player[2].cam.viewport = t3d_viewport_create();
      player[3].cam.viewport = t3d_viewport_create();
      t3d_viewport_set_area(&player[0].cam.viewport, 0,              0,               SCREEN_WIDTH/2,   SCREEN_HEIGHT/2);
      t3d_viewport_set_area(&player[1].cam.viewport, SCREEN_WIDTH/2, 0,               SCREEN_WIDTH/2-2, SCREEN_HEIGHT/2);
      t3d_viewport_set_area(&player[2].cam.viewport, 0,              SCREEN_HEIGHT/2, SCREEN_WIDTH/2,   SCREEN_HEIGHT/2-2);
      t3d_viewport_set_area(&player[3].cam.viewport, SCREEN_WIDTH/2, SCREEN_HEIGHT/2, SCREEN_WIDTH/2-2, SCREEN_HEIGHT/2-2);
    }
  } else {
    player[0].cam.viewport = t3d_viewport_create();
    t3d_viewport_set_area(&player[0].cam.viewport,   0,               0,              SCREEN_WIDTH,      SCREEN_HEIGHT);
  }
}


// rotate camera position around camera target
void rotate_cam_around_target(T3DVec3 *camPos, T3DVec3 camTarget, float angle, char axis) {

  // Step 1: Translate camera position to the origin relative to camera target
  T3DVec3 translatedPos;
  t3d_vec3_diff(&translatedPos, camPos, &camTarget);

  // Step 2: Apply the rotation
  T3DVec3 rotatedPos;
  float rad = angle * T3D_PI / 180.0; // Convert angle to radians

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
  t3d_vec3_add(camPos, &rotatedPos, &camTarget);
}


// returns camera forward and camera right
T3DVec3Pair get_cam_results(T3DVec3 camTarget, T3DVec3 camPos, T3DVec3 *camForward, T3DVec3 *camRight){

  // Calculate camera forward
  camForward->v[0] = camPos.v[0] - camTarget.v[0];
  camForward->v[1] = 0;
  camForward->v[2] = camPos.v[2] - camTarget.v[2];
  t3d_vec3_norm(camForward);

  // Calculate camera right
  camRight->v[0] = camForward->v[2];
  camRight->v[1] = 0;
  camRight->v[2] = -camForward->v[0];
  t3d_vec3_norm(camRight);

  // Pair the results and return
  T3DVec3Pair result;
  result.forward = *camForward;
  result.right = *camRight;
  return result;
}


// move camera position behind player
void cam_recenter(T3DVec3 *camTarget, T3DVec3 *camPos, T3DVec3 *camForward, T3DVec3 *playerPos, T3DVec3 playerForward, float *camYaw){

  // Calculate the camera yaw based on player direction
  *camYaw = atan2f(playerForward.v[0], playerForward.v[2]);

  // Calculate the camera forward based on camera yaw
  camForward->v[0] = sinf(*camYaw);
  camForward->v[1] = 0.0f;
  camForward->v[2] = cosf(*camYaw);

  // Move camera behind player
  camPos->v[0] = playerPos->v[0] - camForward->v[0] * 50.0f;
  camPos->v[1] = playerPos->v[1] + 30.0f;
  camPos->v[2] = playerPos->v[2] - camForward->v[2] * 50.0f;

  // Set camera target to be the player position
  *camTarget = *playerPos;
}

// Top-Down or Bird's Eye view
void top_down_view(T3DVec3 *camTarget, T3DVec3 *camPos, T3DVec3 camForward, T3DVec3 *playerPos){

  // Set camera position above player
  camPos->v[0] = playerPos->v[0] + camForward.v[0] * 5.0f;
  camPos->v[1] = playerPos->v[1] + 100.0f; // 100.0f is the height of the camera
  camPos->v[2] = playerPos->v[2];

  // Set camera target to be the player position
  *camTarget = *playerPos;
}

// update the player's forward based on the player's yaw angle
void update_player_forward(T3DVec3 *playerForward, float playerYaw){

  // Calculate the player forward
  playerForward->v[0] = sinf(playerYaw);
  playerForward->v[1] = 0.0f;
  playerForward->v[2] = cosf(playerYaw);

  // Normalize the player forward
  t3d_vec3_norm(playerForward);
}

// follow the player with the camera with lagging rotation
void cam_follow_player_lag(T3DVec3 *camTarget, T3DVec3 *camPos, T3DVec3 *camForward, float *camYaw, T3DVec3 *playerPos, float playerYaw, float lagFactor){

  // Interpolate the camera yaw towards the player yaw
  *camYaw = t3d_lerp_angle(*camYaw, playerYaw, lagFactor);

  // Calculate the camera forward based on the interpolated yaw
  camForward->v[0] = sinf(*camYaw);
  camForward->v[1] = 0.0f;
  camForward->v[2] = cosf(*camYaw);

  // Set the camera position based on the player's position and the forward vector
  camPos->v[0] = playerPos->v[0] - camForward->v[0] * 50.0f; // 50.0f is the distance from the player
  camPos->v[1] = playerPos->v[1] + 30.0f;                    // 30.0f is the height of the camera
  camPos->v[2] = playerPos->v[2] - camForward->v[2] * 50.0f; // 50.0f is the distance from the player

  // Set the camera target to be the player position
  camTarget = playerPos;
}

// camera main loop
void cam_update(void){

  for (int i = 0; i < numPlayers; ++i) {
    
    // Update camera based on player
    player[i].cam.camResults = get_cam_results(player[i].cam.camTarget, player[i].cam.camPos, &player[i].cam.camForward, &player[i].cam.camRight);
    player[i].cam.camTarget = player[i].pos;
    float angle = 90.0f;
    char axis;
    
    // Handle camera inputs
    if(btn[i].z) {
      player[i].cam.cam_mode = CAM_RECENTER;
    }
    if(btn[i].c_down) {
      player[i].cam.cam_mode = CAM_FOLLOW;
    }
    if(btn[i].c_left) {
      axis = 'y';
      player[i].cam.cam_mode = CAM_ROTATE;
      rotate_cam_around_target(&player[i].cam.camPos, player[i].cam.camTarget, -angle, axis);
    }
    if(btn[i].c_right) {
      axis = 'y';
      player[i].cam.cam_mode = CAM_ROTATE;
      rotate_cam_around_target(&player[i].cam.camPos, player[i].cam.camTarget, angle, axis);
    }
    if(btn[i].c_up) {
      player[i].cam.cam_mode = CAM_TOP_DOWN;
    }

    // Update camera mode
    switch (player[i].cam.cam_mode) {
      case CAM_RECENTER:
        update_player_forward(&player[i].forward, player[i].yaw);
        cam_recenter(&player[i].cam.camTarget, &player[i].cam.camPos, &player[i].cam.camForward, &player[i].pos, player[i].forward, &player[i].cam.camYaw);
        player[i].cam.cam_mode = CAM_FOLLOW;
      case CAM_FOLLOW:
        update_player_forward(&player[i].forward, player[i].yaw);
        cam_follow_player_lag(&player[i].cam.camTarget, &player[i].cam.camPos, &player[i].cam.camForward, &player[i].cam.camYaw, &player[i].pos, player[i].yaw, 0.02f);
        break;
      case CAM_ROTATE:
        update_player_forward(&player[i].forward, player[i].yaw);
        player[i].cam.cam_mode = CAM_FOLLOW;
        break;
      case CAM_TOP_DOWN:
        update_player_forward(&player[i].forward, player[i].yaw);
        top_down_view(&player[i].cam.camTarget, &player[i].cam.camPos, player[i].cam.camForward, &player[i].pos);
        break;
    }

    // Resolve camera collisions
    resolve_box_collision(FloorBox, &player[i].cam.camPos, 2.0f);

  }
}