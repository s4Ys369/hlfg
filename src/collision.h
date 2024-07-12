#ifndef COLLISION_H
#define COLLISION_H

#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include "../include/config.h"
#include "../include/enums.h"
#include "../include/globals.h"
#include "../include/types.h"
#include "utils.h"

extern T3DVec3 center;
extern T3DVec3 norm;
extern T3DVec3 up;
extern T3DVec3 down;
extern T3DVec3 left;
extern T3DVec3 right;
extern T3DVec3 farther;
extern T3DVec3 nearer;

extern float intersectionY;

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
float point_plane_dist(T3DVec3 point, T3DVec3 planePoint, T3DVec3 planeNormal);
T3DVec3 project_point_on_plane(T3DVec3 point, T3DVec3 planePoint, T3DVec3 planeNormal);
T3DVec3 compute_quad_center(T3DQuad quad);
int point_in_quad(T3DVec3 point, T3DQuad quad);
float calc_dist_to_quad(T3DVec3 point, T3DQuad quad);
T3DVec3 reflect_velocity(T3DVec3 velocity, T3DVec3 normal);
void resolve_slope_collision(T3DVec3 position, T3DVec3 velocity, T3DQuad quad);
T3DVec3 get_quad_normal(T3DQuad quad);
T3DQuad get_closest_quad(T3DVec3 originPos, T3DModel* targetModel, int targetModelCount);
bool check_sphere_quad_collision(Sphere a, T3DQuad quad);
float calculate_plane_d(T3DVec3 planeNormal, T3DVec3 pointOnPlane);
void resolve_sphere_quad_collision(T3DVec3* sphereCenter, float sphereRadius, T3DVec3 planeNormal, float planeD);

//SURFACES
T3DVec3 calc_surface_center(Surface surf);
T3DVec3 calc_surface_norm(Surface surf);
float distance_to_surface(T3DVec3 position, Surface surf);
bool check_sphere_surface_collision(Sphere sphere, Surface surf);
bool check_box_surface_collision(AABB a, Surface surf);
Surface find_closest_surface(T3DVec3 position, Surface* surfaces, int numSurfaces);
void resolve_sphere_surface_collision(Sphere *sphere, T3DVec3 *position, T3DVec3 *direction, Surface *surf);
bool ray_intersects_surface(T3DVec3 rayOrigin, T3DVec3 rayDir, Surface surface, float* intersectionAngle);
RaycastResult closest_surface_below_raycast(T3DVec3 startPos, Surface* surfaces, int surfaceCount);
void find_closest_surfaces(T3DVec3 position, Surface* surfaces, int numSurfaces, Surface* closestSurfaces, int* closestCount, SURFACE_TYPE type, float range);

bool check_collisions(CollisionShape a, CollisionShape b);

#endif // COLLISION_H