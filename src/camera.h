#ifndef CAMERA_H
#define CAMERA_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>
#include "../include/types.h"
#include "collision.h"
#include "input.h"
#include "map.h"
#include "player.h"
#include "utils.h"

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

extern T3DViewport viewport;
extern T3DVec3 camPos;
extern T3DVec3 camTarget;
extern T3DVec3 camForward;
extern T3DVec3 camRight;
extern T3DVec3Pair camResults;
extern float camYaw;
extern int cam_mode;

void cam_init(void);
void rotate_camPos_around_camTarget(T3DVec3 *camPos, T3DVec3 camTarget, float angle, char axis);
T3DVec3Pair get_cam_forward(T3DVec3 camTarget, T3DVec3 camPos, T3DVec3 *camForward, T3DVec3 *camRight);
void cam_recenter(T3DVec3 *camTarget, T3DVec3 *camPos, T3DVec3 camForward, T3DVec3 *playerPos, T3DVec3 playerForward, float *camYaw);
void top_down_view(T3DVec3 *camTarget, T3DVec3 *camPos, T3DVec3 camForward, T3DVec3 *playerPos);
void update_player_forward(T3DVec3 *playerForward, float playerYaw);
void cam_follow_player_lag(T3DVec3 *camTarget, T3DVec3 *camPos, T3DVec3 *playerPos, float playerYaw, float *camYaw, float lagFactor);
void cam_update(void);

#endif // CAMERA_H