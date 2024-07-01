#ifndef COLLISION_H
#define COLLISION_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/types.h"
#include "utils.h"

// AABB
bool check_box_collision(AABB a, AABB b);
void calculate_collision_point(AABB a, AABB b, T3DVec3 *collision_point);
void resolve_box_collision(AABB aabb, T3DVec3 *pos);
void resolve_box_collision_xz(AABB aabb, T3DVec3 *pos);
void resolve_box_collision_offset(AABB aabb, T3DVec3 *pos, float offset);
void resolve_box_collision_offset_xz(AABB aabb, T3DVec3 *pos, float offset);

//Sphere
bool check_sphere_collision(Sphere a, Sphere b);
void resolve_sphere_collision(Sphere sphere, T3DVec3 *pos);
void resolve_sphere_collision_xz(Sphere sphere, T3DVec3 *pos);
void resolve_sphere_collision_offset(Sphere sphere, T3DVec3 *pos, float offset);
void resolve_sphere_collision_offset_xz(Sphere sphere, T3DVec3 *pos, float offset);
bool check_sphere_box_collision(Sphere sphere, AABB box);

// Quads
T3DVec3 reflect(T3DVec3 velocity, T3DVec3 normal);
T3DVec3 find_closest_quad_from_verts(T3DVec3 originPos, T3DModel* targetModel, int targetModelCount);

bool check_collisions(CollisionShape a, CollisionShape b);

#endif // COLLISION_H