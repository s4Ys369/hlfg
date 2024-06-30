#include <libdragon.h>
#include <t3d/t3d.h>
#include "../include/enums.h"
#include "../include/types.h"
#include "collision.h"
#include "utils.h"

// Check AABB to AABB
bool check_box_collision(AABB a, AABB b) {
    if (a.max.v[0] < b.min.v[0] || a.min.v[0] > b.max.v[0]) return false;
    if (a.max.v[1] < b.min.v[1] || a.min.v[1] > b.max.v[1]) return false;
    if (a.max.v[2] < b.min.v[2] || a.min.v[2] > b.max.v[2]) return false;
    return true;
}


// Move pos outside of AABB
void resolve_box_collision(AABB aabb, T3DVec3 *pos, float offset) {
  // Check if the point is inside the AABB
    if (pos->v[0] >= aabb.min.v[0] && pos->v[0] <= aabb.max.v[0] &&
        pos->v[1] >= aabb.min.v[1] && pos->v[1] <= aabb.max.v[1] &&
        pos->v[2] >= aabb.min.v[2] && pos->v[2] <= aabb.max.v[2]) {

        // Find the closest edge and move the point to it
        float dxMin = fabsf(pos->v[0] - aabb.min.v[0]);
        float dxMax = fabsf(pos->v[0] - aabb.max.v[0]);
        float dyMin = fabsf(pos->v[1] - aabb.min.v[1]);
        float dyMax = fabsf(pos->v[1] - aabb.max.v[1]);
        float dzMin = fabsf(pos->v[2] - aabb.min.v[2]);
        float dzMax = fabsf(pos->v[2] - aabb.max.v[2]);

        float minDist = fminf(fminf(dxMin, dxMax), fminf(dyMin, dyMax));
        minDist = fminf(minDist, fminf(dzMin, dzMax));

        if (minDist == dxMin) { pos->v[0] = aabb.min.v[0] - offset; return; }
        if (minDist == dxMax) { pos->v[0] = aabb.max.v[0] + offset; return; }
        if (minDist == dyMin) { pos->v[1] = aabb.min.v[1] - offset; return; }
        if (minDist == dyMax) { pos->v[1] = aabb.max.v[1] + offset; return; }
        if (minDist == dzMin) { pos->v[2] = aabb.min.v[2] - offset; return; }
        if (minDist == dzMax) { pos->v[2] = aabb.max.v[2] + offset; return; }
    }
}

// Move position outside AABB only along X and Z
void resolve_box_collision_xz(AABB aabb, T3DVec3 *pos, float offset) {
     // Calculate the dimensions of the AABB
    float width = aabb.max.v[0] - aabb.min.v[0];
    float depth = aabb.max.v[2] - aabb.min.v[2];

    // Calculate the offset as a fraction of the AABB's dimensions
    float offsetX = width * offset;
    float offsetZ = depth * offset;
    
    // Check if the point is inside the AABB
    if (pos->v[0] >= aabb.min.v[0] && pos->v[0] <= aabb.max.v[0] &&
        pos->v[1] >= aabb.min.v[1] && pos->v[1] <= aabb.max.v[1] &&
        pos->v[2] >= aabb.min.v[2] && pos->v[2] <= aabb.max.v[2]) {

        // Find the closest edge and move the point to it, only considering x and z
        float dxMin = fabsf(pos->v[0] - aabb.min.v[0]);
        float dxMax = fabsf(pos->v[0] - aabb.max.v[0]);
        float dzMin = fabsf(pos->v[2] - aabb.min.v[2]);
        float dzMax = fabsf(pos->v[2] - aabb.max.v[2]);

        float minDist = fminf(fminf(dxMin, dxMax), fminf(dzMin, dzMax));

        if (minDist == dxMin) { pos->v[0] = aabb.min.v[0] - offsetX; return; }
        if (minDist == dxMax) { pos->v[0] = aabb.max.v[0] + offsetX; return; }
        if (minDist == dzMin) { pos->v[2] = aabb.min.v[2] - offsetZ; return; }
        if (minDist == dzMax) { pos->v[2] = aabb.max.v[2] + offsetZ; return; }
    }
}


// Check for sphere to sphere
bool check_sphere_collision(Sphere a, Sphere b) {
    // Calculate the squared distance between centers
    float distanceSquared = t3d_vec3_distance(&a.center, &b.center);
    float radiusSquared = a.radius + b.radius;

    // Check collision
    float e = 1e-6f;
    if (distanceSquared <= (radiusSquared + e)) {
        return true; // Collision detected
    } else {
        return false; // No collision
    }
}

void resolve_sphere_collision(Sphere sphere, T3DVec3 *pos) {
    // Calculate the vector from the sphere's center to the point
    T3DVec3 direction;
    t3d_vec3_diff(&direction, pos, &sphere.center);

    // Normalize the direction vector
    t3d_vec3_norm(&direction);

    // Calculate the distance from the sphere's center to the position
    float distance = t3d_vec3_distance(&sphere.center, pos);

    // If the point is within the sphere, resolve the collision
    if (distance < sphere.radius) {
        // Calculate the target position on the surface of the sphere
        float targetDistance = sphere.radius + 1e-6f;
        pos->v[0] = sphere.center.v[0] + direction.v[0] * targetDistance;
        pos->v[1] = sphere.center.v[1] + direction.v[1] * targetDistance;
        pos->v[2] = sphere.center.v[2] + direction.v[2] * targetDistance;

        // Apply damping to smooth the movement
        pos->v[0] = sphere.center.v[0] + (pos->v[0] - sphere.center.v[0]);
        pos->v[1] = sphere.center.v[1] + (pos->v[1] - sphere.center.v[1]);
        pos->v[2] = sphere.center.v[2] + (pos->v[2] - sphere.center.v[2]);
    }
}

void resolve_sphere_collision_xz(Sphere sphere, T3DVec3 *pos) {
    // Calculate the vector from the sphere's center to the point
    T3DVec3 direction;
    t3d_vec3_diff(&direction, pos, &sphere.center);

    // Normalize the direction vector
    t3d_vec3_norm(&direction);

    // Calculate the distance from the sphere's center to the position
    float distance = t3d_vec3_distance(&sphere.center, pos);

    // If the point is within the sphere, resolve the collision
    if (distance < sphere.radius) {
        // Calculate the target position on the surface of the sphere
        float targetDistance = sphere.radius + 1e-6f;
        pos->v[0] = sphere.center.v[0] + direction.v[0] * targetDistance;
        pos->v[2] = sphere.center.v[2] + direction.v[2] * targetDistance;

        // Apply damping to smooth the movement
        pos->v[0] = sphere.center.v[0] + (pos->v[0] - sphere.center.v[0]);
        pos->v[2] = sphere.center.v[2] + (pos->v[2] - sphere.center.v[2]);
    }
}

void resolve_sphere_collision_offset(Sphere sphere, T3DVec3 *pos, float damping) {
    // Calculate the vector from the sphere's center to the point
    T3DVec3 direction;
    t3d_vec3_diff(&direction, pos, &sphere.center);

    // Normalize the direction vector
    t3d_vec3_norm(&direction);

    // Calculate the distance from the sphere's center to the position
    float distance = t3d_vec3_distance(&sphere.center, pos);

    // If the point is within the sphere, resolve the collision
    if (distance < sphere.radius) {
        // Calculate the target position on the surface of the sphere
        float targetDistance = sphere.radius + 1e-6f;
        pos->v[0] = sphere.center.v[0] + direction.v[0] * targetDistance;
        pos->v[1] = sphere.center.v[1] + direction.v[1] * targetDistance;
        pos->v[2] = sphere.center.v[2] + direction.v[2] * targetDistance;

        // Apply damping to smooth the movement
        pos->v[0] = sphere.center.v[0] + (pos->v[0] - sphere.center.v[0]) * damping;
        pos->v[1] = sphere.center.v[1] + (pos->v[1] - sphere.center.v[1]) * damping;
        pos->v[2] = sphere.center.v[2] + (pos->v[2] - sphere.center.v[2]) * damping;
    }
}

void resolve_sphere_collision_offset_xz(Sphere sphere, T3DVec3 *pos, float damping) {
    // Calculate the vector from the sphere's center to the point
    T3DVec3 direction;
    t3d_vec3_diff(&direction, pos, &sphere.center);

    // Normalize the direction vector
    t3d_vec3_norm(&direction);

    // Calculate the distance from the sphere's center to the position
    float distance = t3d_vec3_distance(&sphere.center, pos);

    // If the point is within the sphere, resolve the collision
    if (distance < sphere.radius) {
        // Calculate the target position on the surface of the sphere
        float targetDistance = sphere.radius + 1e-6f;
        pos->v[0] = sphere.center.v[0] + direction.v[0] * targetDistance;
        pos->v[2] = sphere.center.v[2] + direction.v[2] * targetDistance;

        // Apply damping to smooth the movement
        pos->v[0] = sphere.center.v[0] + (pos->v[0] - sphere.center.v[0]) * damping;
        pos->v[2] = sphere.center.v[2] + (pos->v[2] - sphere.center.v[2]) * damping;
    }
}


// Check for sphere to AABB, use resolve_box_collision
bool check_sphere_box_collision(Sphere sphere, AABB box) {
    // Find the closest point on the AABB to the sphere's center
    float closestX = clamp(sphere.center.v[0], box.min.v[0], box.max.v[0]);
    float closestY = clamp(sphere.center.v[1], box.min.v[1], box.max.v[1]);
    float closestZ = clamp(sphere.center.v[2], box.min.v[2], box.max.v[2]);

    // Calculate the distance between the sphere's center and this closest point
    float distanceX = sphere.center.v[0] - closestX;
    float distanceY = sphere.center.v[1] - closestY;
    float distanceZ = sphere.center.v[2] - closestZ;

    // Calculate the squared distance and compare with squared radius
    float distanceSquared = (distanceX * distanceX) + (distanceY * distanceY) + (distanceZ * distanceZ);
    float radiusSquared = sphere.radius * sphere.radius;

    // If the squared distance is less than the squared radius, there is a collision
    float e = 1e-6f;
    return distanceSquared <= (radiusSquared + e);
}


// Catch all
bool check_collisions(CollisionShape a, CollisionShape b) {
    if (a.type == SHAPE_BOX && b.type == SHAPE_BOX) {
        return check_box_collision(a.aabb, b.aabb);
    }
    if (a.type == SHAPE_SPHERE && b.type == SHAPE_SPHERE) {
        return check_sphere_collision(a.sphere, b.sphere);
    }
    if (a.type != b.type) {
        if (a.type == SHAPE_SPHERE){
            return check_sphere_box_collision(a.sphere, b.aabb);
        } else {
            return check_sphere_box_collision(b.sphere, a.aabb);
        }
    }
    return false;
}
