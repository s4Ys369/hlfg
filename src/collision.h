#ifndef COLLISION_H
#define COLLISION_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include "../include/types.h"
#include "utils.h"

bool check_box_collision(AABB a, AABB b);
void resolve_box_collision(AABB aabb, T3DVec3 *pos, float offset);
void resolve_box_collision_xz(AABB aabb, T3DVec3 *pos, float offset);
bool check_sphere_collision(Sphere a, Sphere b);
void resolve_sphere_collision(Sphere sphere, T3DVec3 *pos);
void resolve_sphere_collision_xz(Sphere sphere, T3DVec3 *pos);
void resolve_sphere_collision_offset(Sphere sphere, T3DVec3 *pos, float damping);
void resolve_sphere_collision_offset_xz(Sphere sphere, T3DVec3 *pos, float damping);
bool check_sphere_box_collision(Sphere sphere, AABB box);
bool check_collisions(CollisionShape a, CollisionShape b);

#endif // COLLISION_H