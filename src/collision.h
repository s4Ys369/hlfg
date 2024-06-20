#ifndef COLLISION_H
#define COLLISION_H

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <libdragon.h>
#include <t3d/t3d.h>
#include "../include/types.h"
#include "utils.h"

bool check_box_collision(AABB a, AABB b);
void resolve_box_collision(AABB aabb, T3DVec3 *pos);
bool check_sphere_collision(Sphere a, Sphere b);
bool check_sphere_box_collision(Sphere sphere, AABB box);
bool check_collisions(CollisionShape a, CollisionShape b);

#endif // COLLISION_H