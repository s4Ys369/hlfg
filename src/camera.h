#ifndef CAMERA_H
#define CAMERA_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "collision.h"
#include "input.h"
#include "map.h"
#include "player.h"
#include "utils.h"

extern T3DVec3 lightDirVec;
extern uint8_t colorAmbient[4];
extern uint8_t colorDir[4];

void cam_init(void);
void rotate_cam_around_target(T3DVec3 *camPos, T3DVec3 camTarget, float angle, char axis);
T3DVec3Pair get_cam_results(T3DVec3 camTarget, T3DVec3 camPos, T3DVec3 *camForward, T3DVec3 *camRight);
void cam_recenter(T3DVec3 *camTarget, T3DVec3 *camPos, T3DVec3 *camForward, T3DVec3 *playerPos, T3DVec3 playerForward, float *camYaw);
void top_down_view(T3DVec3 *camTarget, T3DVec3 *camPos, T3DVec3 camForward, T3DVec3 *playerPos);
void update_player_forward(T3DVec3 *playerForward, float playerYaw);
void cam_follow_player_lag(T3DVec3 *camTarget, T3DVec3 *camPos, T3DVec3 *camForward, float *camYaw, T3DVec3 *playerPos, float playerYaw, float lagFactor);
void cam_update(void);

#endif // CAMERA_H